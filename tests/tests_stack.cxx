#include "ucpp/testing.h"
#include "ucpp/stack.h"

TEST_CASE(empty_stack_default_init)
{
    ucpp::stack<int, 10> stack;

    CHECK(stack.size() == 0);
    CHECK(stack.capacity() == 10);
}

TEST_CASE(push_back_one_value)
{
    struct copy_constructible {
        copy_constructible() = delete;
        explicit copy_constructible(int v) : value(v) {}
        copy_constructible(const copy_constructible &o) : value(o.value) {}
//<<<<<<< HEAD
//=======
//        void operator=(const copy_constructible &) {}
//>>>>>>> c439a17... more tests for stack

        int value;
    };
    ucpp::stack<copy_constructible, 10> stack;
    stack.push_back(copy_constructible(42));

    CHECK(stack.size() == 1);
    CHECK(stack.back().value == 42);
}

TEST_CASE(emplace_back_one_value)
{
    struct non_copyable {
        non_copyable() = delete;
        explicit non_copyable(int v) : value(v) {}
        non_copyable(const non_copyable &) = delete;
        void operator=(const non_copyable &) = delete;

        int value;
    };
    ucpp::stack<non_copyable, 10> stack;
    stack.emplace_back(42);

    CHECK(stack.size() == 1);
    CHECK(stack.back().value == 42);
}

TEST_CASE(push_and_pop)
{
    ucpp::stack<int, 10> stack;
    stack.emplace_back(42);
    stack.emplace_back(43);
    stack.emplace_back(44);

    CHECK(stack.size() == 3);
    CHECK(stack.back() == 44);
}
