#include "gtest/gtest.h"
#include "am_mod.h"
#include "filter.h"
#include "IQ.h"
#include <vector>
#include <math.h>
#include <iostream>

TEST(DemodKnownSignal, OneTone) {
    int sig_len = 4096;
    float sig_freq = 1000.0;
    float Fs = 3000.0;
    float sig_ampl = 10000;
    std::vector<float> signal(sig_len);
    float time = 0.0;
    for (int i = 0; i < sig_len; i++){
        signal[i] = cos(2 * M_PI * sig_freq * time);
        time += 1/Fs;
    }

    float m = 1;
    float phi0 = 0;

    am_mod mod_signal(signal, sig_ampl, m, phi0);

    int filter_len = 101;
    filter filt(filter_len);
    std::vector<float> demod_signal(sig_len - (filter_len - 1));

    filt.mov_av(mod_signal.getSignal(), demod_signal, sig_len);

    float diff;
    float max_err = 0.0;
    for (int i = 0; i < sig_len - (filter_len - 1); i++){
        diff = demod_signal[i]/sig_ampl - signal[i+filter_len/2];
        //std::cout << diff << std::endl;         	
        if(diff < 0) 
        	diff *= -1;
        if(diff > max_err)  
        	max_err = diff;
        EXPECT_TRUE(diff < sig_ampl * 0.05);
    }
    std::cout << "max error = " << max_err*100 << " %" << std::endl;
}

TEST(DemodKnownSignal, FilterLen) {
    int sig_len = 4096;
    float sig_freq = 1000.0;
    float Fs = 3000.0;
    float sig_ampl = 10000;
    std::vector<float> signal(sig_len);
    float time = 0.0;
    for (int i = 0; i < sig_len; i++){
        signal[i] = cos(2 * M_PI * sig_freq * time);
        time += 1/Fs;
    }

    float m = 1;
    float phi0 = 0;

    am_mod mod_signal(signal, sig_ampl, m, phi0);

    int filter_len = 11;
    filter filt(filter_len);
    std::vector<float> demod_signal(sig_len - (filter_len - 1));

    filt.mov_av(mod_signal.getSignal(), demod_signal, sig_len);

    float diff;
    float max_err = 0.0;
    for (int i = 0; i < sig_len - (filter_len - 1); i++){
        diff = demod_signal[i]/sig_ampl - signal[i+filter_len/2];
        //std::cout << diff << std::endl;         	
        if(diff < 0) 
        	diff *= -1;
        if(diff > max_err)  
        	max_err = diff;
        EXPECT_TRUE(diff < 0.05);
    }
    std::cout << "max error = " << max_err*100 << " %" << std::endl;
}
