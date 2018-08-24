#include "ucpp/testing.h"
#include "ucpp/stack.h"

TEST_INIT;

int main() {
    test_run();
    return 0;
}

TEST_CASE(empty_stack_default_init)
{
    ucpp::stack<int, 10> stack;

    CHECK(stack.size() == 0);
    CHECK(stack.capacity() == 10);
}

TEST_CASE(push_one_value)
{
    struct copy_constructible {
        copy_constructible() = delete;
        explicit copy_constructible(int v) : value(v) {}
        copy_constructible(const copy_constructible &) {}

        int value;
    };
    ucpp::stack<copy_constructible, 10> stack;
    stack.push_back(copy_constructible(42));

    CHECK(stack.size() == 1);
    CHECK(stack.back().value == 42);
}
