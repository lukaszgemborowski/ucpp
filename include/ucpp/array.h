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

    array() : buffer_()
    {
    }

    constexpr unsigned int size() const {
        return N;
    }

    iterator begin() {
        return &buffer_[0];
    }

    iterator end() {
        return &buffer_[N];
    }

    reference at(size_type pos) {
        return buffer_[pos];
    }

    reference operator[](size_type pos) {
        return buffer_[pos];
    }

private:
    T buffer_[N];
};

}

#endif
