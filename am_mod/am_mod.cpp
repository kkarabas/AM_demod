#include "am_mod.h"
#include <math.h>

am_mod::am_mod(std::vector<float>&signal, float amp, float m, float phi0)
{
    mod_signal.resize(signal.size());
    float tmp;
    for(int i = 0; i < signal.size(); i++){
        tmp = amp * (1 + m * signal[i]);
        mod_signal[i].re = uint32_t (tmp * cos(phi0));
        mod_signal[i].im = uint32_t (tmp * sin(phi0));
    }
}

const std::vector<IQ>& am_mod::getSignal()
{
    return mod_signal;
}
