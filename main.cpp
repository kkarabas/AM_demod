#include <iostream>
#include <fstream>
#include <vector>
#include "IQ.h"
#include "wav.h"
#include "filter.h"

int readDataBlock(std::fstream &fs, std::vector<IQ> &signal, const int block_iq_len, const int filter_len)
{
    if (fs.eof())
        return 0;

    long cur_pos = fs.tellp();
    int iq_to_read = block_iq_len + filter_len;

    if (cur_pos != 0){
        fs.seekg (-(filter_len/2 - 1 ) * sizeof (IQ), std::ios_base::cur);
        cur_pos = fs.tellp();
    }

    fs.seekg (0, fs.end);
    long len_max = fs.tellg();

    fs.seekg (cur_pos, fs.beg);

    long remain = len_max - cur_pos;

    if (remain / sizeof (IQ) < filter_len)
        return 0;

    if(iq_to_read * sizeof (IQ) > remain)
        iq_to_read = remain / sizeof (IQ);

    fs.read((char*)signal.data(), iq_to_read * sizeof (IQ));

    return iq_to_read;
}


int main()
{
    const int BUFF_SIZE = 1024; // количество отсчетов
    const int filter_len = 101; // нечетное
    const int Fs = 32000;
    const int bps = sizeof (float)*8;
    const std::string wav_file {"/home/karabas/CPP/AM_test/am_sound.wav"};

    std::vector<IQ> signal (BUFF_SIZE + (filter_len -1));
    std::vector<float> demod_signal(BUFF_SIZE);

    std::fstream fin("/home/karabas/CPP/AM_test/am_sound.dat") ;
    if (!fin) {
        std::cout << "Can't open file" << std::endl ;
        exit(1) ;
    }

    fin.seekg (0, fin.end);
    long data_len = fin.tellg();
    data_len = data_len/sizeof (IQ) - (filter_len-1);
    fin.seekg (0, fin.beg);

    std::vector<float> output_signal;
    output_signal.reserve(data_len * sizeof (float));

    filter filt(filter_len);

    int n;
    while ( (n = readDataBlock(fin, signal, BUFF_SIZE, filter_len)) != 0) {
        filt.mov_av(signal, demod_signal, n);
        for(auto elem: demod_signal) output_signal.emplace_back((float)elem);
    }

    wav wav_ctrl(wav_file, output_signal.size() , 12000, bps);
    if(bps == 32 || bps == 24)
        wav_ctrl.normilize(output_signal);
    wav_ctrl.writeDataBlock( (char*)output_signal.data(), output_signal.size() * sizeof (float) );

    return 0;
}
