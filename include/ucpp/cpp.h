#ifndef UCPP_CPP_H
#define UCPP_CPP_H

namespace ucpp
{

template<class T, T v>
struct integral_constant {
    static constexpr T value = v;
    typedef T value_type;
    typedef integral_constant type;
    constexpr operator value_type() const noexcept { return value; }
};

} // namespace cpp

#endif
