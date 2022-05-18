#include "wav.h"
#include <fstream>
#include <iostream>
#include <algorithm>

wav::wav(const std::string& file, long dataSize, int samplerate, int bps ):
    filename(file)
{
    wavHeader.RIFF[0] = 'R' ; wavHeader.RIFF[1] = 'I' ; wavHeader.RIFF[2] = 'F' ; wavHeader.RIFF[3] = 'F' ;
    wavHeader.WAVE[0] = 'W'; wavHeader.WAVE[1] = 'A' ; wavHeader.WAVE[2] = 'V' ; wavHeader.WAVE[3] = 'E' ;
    wavHeader.fmt[0] = 'f' ;  wavHeader.fmt[1] = 'm' ;  wavHeader.fmt[2] = 't' ;  wavHeader.fmt[3] = ' ' ;
    wavHeader.Subchunk2ID[0] = 'd' ; wavHeader.Subchunk2ID[1] = 'a' ; wavHeader.Subchunk2ID[2] = 't' ; wavHeader.Subchunk2ID[3] = 'a' ;
    wavHeader.Subchunk1Size = 16 ; //объем данных равен размеру стандартного формата WAV (16 байт)
    wavHeader.AudioFormat = 1 ;    //1 (0x0001) 	PCM/uncompressed
    wavHeader.NumOfChan = 1 ;	   //1 - mono
    wavHeader.SamplesPerSec = samplerate ; // sample rate
    wavHeader.bitsPerSample = bps ;     //8, 16, 24 или 32
    wavHeader.blockAlign = wavHeader.bitsPerSample / 8 * wavHeader.NumOfChan ; //BlockAlign = BitsPerSample / 8 * NumChannels
    wavHeader.bytesPerSec = wavHeader.SamplesPerSec * wavHeader.blockAlign ; //AvgBytesPerSec = SampleRate * BlockAlign
    wavHeader.Subchunk2Size = dataSize * wavHeader.blockAlign  ;

    wavHeader.ChunkSize = sizeof(WAV_HEADER) - 8 + wavHeader.Subchunk2Size;

    size_t headerSize = sizeof(WAV_HEADER);

    std::ofstream wavfile(filename, std::ios_base::trunc) ;
    if (!wavfile) {
        std::cerr << "Can't open file" << std::endl;
        exit(1) ;
    }
    wavfile.write( (char*)&wavHeader , headerSize );
    wavfile.close();
}

void wav::writeDataBlock(char* data, long dataLen)
{
    std::ofstream wavfile(filename, std::ios_base::app) ;
    if (!wavfile) {
        std::cerr << "Can't open file" << std::endl;
        exit(1) ;
    }
    wavfile.write(data, dataLen);
    wavfile.close();
}

void wav::normilize(std::vector<float> &data)
{
    float max_val = *std::max_element(data.begin(), data.end());
    float min_val = *std::min_element(data.begin(), data.end());
    if (min_val < 0)
        min_val *= -1;
    if (max_val < 0)
        max_val *= -1;
    float norm_coef = 1.0/std::max(min_val,max_val);

    for(auto el: data){
        el *= norm_coef;
    }
}
