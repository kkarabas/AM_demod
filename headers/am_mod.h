#ifndef AM_MOD_H
#define AM_MOD_H

#include <vector>
#include "IQ.h"

class am_mod
{
public:
    am_mod(std::vector<float>&signal, float amp, float m, float phi0);
    const std::vector<IQ>& getSignal();

private:
    std::vector<IQ> mod_signal;
};

#endif // AM_MOD_H
