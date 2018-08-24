#ifndef UCPP_ARRAY_H
#define UCPP_ARRAY_H

namespace ucpp
{

template<typename T, unsigned int N>
class array
{
public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = const T*;
    using const_iterator = const T*;
    using size_type = unsigned int;

    constexpr unsigned int size() {
        return N;
    }

    constexpr iterator begin() {
        return &buffer_[0];
    }

    constexpr iterator end() {
        return &buffer_[N];
    }

    constexpr reference at(size_type pos) {
        return buffer_[pos];
    }

    constexpr reference operator[](size_type pos) {
        return buffer_[pos];
    }

private:
    T buffer_[N];
};

}

#endif
