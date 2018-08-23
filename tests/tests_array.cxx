#include "ucpp/testing.h"
#include "ucpp/array.h"

TEST_INIT;

int main() {
    test_run();
    return 0;
}

TEST_CASE(default_initialized_array)
{
    const int default_value = 42;
    constexpr int size = 5;
    struct test_struct {
        const int value = default_value;

        test_struct() = default;

        // unsure no copies
        test_struct(const test_struct &) = delete;
        void operator=(const test_struct &) = delete;
    };

    ucpp::array<test_struct, size> arr;

    CHECK(size == arr.size());

    // test range for loop over elements
    for (auto &el : arr) {
        CHECK(el.value == default_value);
    }

    // test at() and operator[]
    for (int i = 0; i < size; i ++) {
        CHECK(arr.at(i).value == default_value);
        CHECK(arr[i].value == default_value);
    }
}


