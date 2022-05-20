#include "filter.h"
#include <math.h>
#include <iostream>

filter::filter(int filter_len):
    len(filter_len)
{

}

void filter::mov_av(const std::vector<IQ>& signal, std::vector<float>& filtered_sig, int n)
{
    float aver_signal = 0.0;
    // 1 значение скользящего среднего
    for (int i = 0; i < len; i++){
        aver_signal += 1.0/float(len) * sqrt( float(signal[i].re)*float(signal[i].re) + float(signal[i].im)*float(signal[i].im) );
    }

    filtered_sig[0] = sqrt(float(signal[len/2].re)*float(signal[len/2].re) + float(signal[len/2].im)*float(signal[len/2].im)) - aver_signal;

    for(int i = 1; i < n - (len - 1) ; i++){
        aver_signal = aver_signal - 1.0/float(len) * sqrt( float(signal[i-1].re)*float(signal[i-1].re) + float(signal[i-1].im)*float(signal[i-1].im) )
                                  + 1.0/float(len) * sqrt( float(signal[len - 1 + i].re)*float(signal[len - 1 + i].re) + float(signal[len - 1 + i].im)*float(signal[len - 1 + i].im) ) ;
        filtered_sig[i] = sqrt( float(signal[len/2 + i].re)*float(signal[len/2 + i].re) + float(signal[len/2 + i].im)*float(signal[len/2 + i].im) ) - aver_signal;
    }
}

/*
void filter::mov_av2(std::vector<IQ>& signal, std::vector<float>& filtered_sig, int n)
{
    float aver_signal = 0.0;
    filtered_sig[0] = sqrt( float(signal[0].re)*float(signal[0].re)
                           +float(signal[0].im)*float(signal[0].im) )  - aver_signal;

    for ( int i = 1 ; i < n ; i++ ){
        filtered_sig[i] = sqrt( float(signal[i].re)*float(signal[i].re)
                               +float(signal[i].im)*float(signal[i].im) );
        aver_signal =  (1.0-1.0/(float)len) * aver_signal + filtered_sig [i] / (float)len ;
        filtered_sig [i] = filtered_sig [i] - aver_signal ;
        //std::cout << "aver = " << aver_signal << std::endl;
       // std::cout << "filtered_sig [i] = " << filtered_sig [i] << std::endl;
    }

}
*/
