#ifndef FILTER_H
#define FILTER_H

#include "IQ.h"
#include <vector>

class filter
{
public:
    filter(int filter_len);
    void mov_av(std::vector<IQ>& signal, std::vector<float>& filtered_sig, int n);
//    void mov_av2(std::vector<IQ>& signal, std::vector<float>& filtered_sig, int n);


private:
    int len;
};

#endif // FILTER_H
