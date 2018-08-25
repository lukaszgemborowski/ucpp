#ifndef UCPP_BIT_H
#define UCPP_BIT_H

namespace ucpp
{
namespace bit
{

template<unsigned int B, typename T>
void set(T &value) {
    value = value | (1 << B);
}

}
}

#endif