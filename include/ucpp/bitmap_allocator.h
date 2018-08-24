#ifndef UCPP_BITMAP_ALLOCATOR_H
#define UCPP_BITMAP_ALLOCATOR_H

#include "uninitialized_array.h"
#include "array.h"

namespace ucpp
{

template<typename T, unsigned int N>
class bitmap_allocator
{
public:
    using reference = T &;
    using pointer = T *;

    template<typename... Args>
    reference allocate(Args&&... args)
    {
        auto index = find_and_mark();
        allocated_ ++;
        return pool_.construct(index, args...);
    }

    constexpr auto allocated_count() const
    {
        return allocated_;
    }

    constexpr auto capacity() const
    {
        return N;
    }

    constexpr auto space_available() const
    {
        return allocated_count() < capacity();
    }

private:
    unsigned int find_and_mark()
    {
        unsigned int index = 0;
        for (auto byte : bits_) {
            if (byte == 0xff) {
                index ++;
                continue;
            }

            unsigned int bit_index = 0;
            while (byte & 1) {
                byte = byte >> 1;
                bit_index ++;
            }

            bits_[index] = bits_[index] | (1 << bit_index);
            return (index * 8) + bit_index;
        }

        return 0;
    }

private:
    uninitialized_array<T, N> pool_;
    array<char, N/8> bits_;
    unsigned int allocated_ = 0; 
};

}

#endif