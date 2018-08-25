#include "ucpp/testing.h"
#include "ucpp/bitmap_allocator.h"

TEST_CASE(allocate_one_object)
{
    struct T {
        bool initialized = true;
    };

    ucpp::bitmap_allocator<T, 1> alloc;

    CHECK(alloc.space_available());

    auto &obj = alloc.allocate();

    CHECK(obj.initialized == true);
    CHECK(alloc.space_available() == false);
}

TEST_CASE(bitmap_allocator_unique_addresses)
{
    constexpr auto number = 20;
    int* addrs[number];
    ucpp::bitmap_allocator<int, number> alloc;

    for (int i = 0; i < number; i ++) {
        addrs[i] = &alloc.allocate(i);

        for (int j = 0; j < i; j ++) {
            CHECK(addrs[j] != addrs[i]);
        }
    }

    CHECK(alloc.space_available() == false);
}