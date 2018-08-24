#ifndef UCPP_STACK_H
#define UCPP_STACK_H

#include "cpp.h"

namespace ucpp
{

template<typename T, unsigned int N>
class stack
{
    using element_size = integral_constant<unsigned int, sizeof(T)>;
    using buffer_size = integral_constant<unsigned int, element_size::value * N>;

public:
    using value_type = T;
    using reference = const T&;
    using const_reference = const T&;
    using iterator = const T*;
    using const_iterator = const T*;
    using size_type = unsigned int;

    void push_back(const T& element) {
        char *ptr = &buffer_[top_ * element_size::value];
        T *tptr = new(ptr) T(element);
        top_ ++;
    }

    template<typename... Args>
    void emplace_back(Args... args) {
        char *ptr = &buffer_[top_ * element_size::value];
        new(ptr) T(args...);
        top_ ++;
    }

    void pop_back() {
        top_ --;
        T *ptr = reinterpret_cast<T *>(&buffer_[top_ * element_size::value]);
        ptr->~T();
    }

    reference back() {
        return *reinterpret_cast<T *>(&buffer_[(top_ - 1) * element_size::value]);
    }

    iterator begin() {
        return reinterpret_cast<T *>(&buffer_[0]);
    }

    iterator end() {
        return reinterpret_cast<T *>(&buffer_[top_ * element_size::value]);
    }

    size_type size() const {
        return top_;
    }

    constexpr size_type capacity() const {
        return N;
    }

private:
    char buffer_[buffer_size::value];
    unsigned int top_ = 0;
};

} // namespace ucpp

#endif
