#ifndef UCPP_UNINITIALIZED_ARRAY_H
#define UCPP_UNINITIALIZED_ARRAY_H

#include "cpp.h"

namespace ucpp
{
template<typename T, unsigned int N>
class uninitialized_array
{
    using element_size = integral_constant<unsigned int, sizeof(T)>;
    using buffer_size = integral_constant<unsigned int, N>;

public:
    using value_type = T;
    using reference = const T&;
    using const_reference = const T&;
    using iterator = const T*;
    using const_iterator = const T*;
    using size_type = unsigned int;

    constexpr size_type size() const { return N; }
    reference operator[](size_type i)
    {
        return at(i);
    }

    reference at(size_type i)
    {
        return *reinterpret_cast<T *>(&buffer_[i * element_size::value]);
    }

    template<typename... Args>
    reference construct(size_type i, Args&&... args)
    {
        char *ptr = &buffer_[i * element_size::value];
        T *tptr = new(ptr) T(args...);
        return *tptr;
    }

    void destruct(size_type i)
    {
        char *ptr = &buffer_[i * element_size::value];
        reinterpret_cast<T *>(ptr)->~T();
    }

private:
    char buffer_[buffer_size::value];
};
}

#endif
