#include "ucpp/testing.h"
#include "ucpp/bitmap_allocator.h"

TEST_INIT;

int main() {
    test_run();
    return 0;
}

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
