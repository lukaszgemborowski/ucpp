#ifndef UCPP_BIT_H
#define UCPP_BIT_H

namespace ucpp
{
namespace bit
{

namespace detail {
template<unsigned int B, typename T>
constexpr T set(T value) {
    return value | (1 << B);
}
}

template<typename T>
constexpr void set(T &) {}

template<unsigned int B, unsigned int... Bs, typename T>
constexpr void set(T &value) {
    value = detail::set<B>(value);
    set<Bs...>(value);
}

}
}

#endif
