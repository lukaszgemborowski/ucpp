#ifndef UCPP_STACK_H
#define UCPP_STACK_H

#include "uninitialized_array.h"

namespace ucpp
{

template<typename T, unsigned int N>
class stack
{
public:
    using value_type = T;
    using reference = const T&;
    using const_reference = const T&;
    using iterator = const T*;
    using const_iterator = const T*;
    using size_type = unsigned int;

    void push_back(const T& element) {
        buffer_.construct(top_, element);
        top_ ++;
    }

    template<typename... Args>
    void emplace_back(Args... args) {
        buffer_.construct(top_, args...);
        top_ ++;
    }

    void pop_back() {
        top_ --;
        buffer_.destruct(top_);
    }

    reference back() {
        return buffer_.at(top_ - 1);
    }

    iterator begin() {
        return &buffer_[0];
    }

    iterator end() {
        return &buffer_[top_];
    }

    size_type size() const {
        return top_;
    }

    constexpr size_type capacity() const {
        return N;
    }

private:
    uninitialized_array<T, N> buffer_;
    unsigned int top_ = 0;
};

} // namespace ucpp

#endif
