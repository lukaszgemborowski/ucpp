#include "ucpp/testing.h"
#include "ucpp/bit.h"

TEST_CASE(bit_set)
{
    unsigned int foo = 0xA0;
    ucpp::bit::set<3>(foo);
    CHECK(foo == 0xA8);
}

TEST_CASE(bit_set_multiple)
{
    unsigned int foo = 0xA0;
    ucpp::bit::set<0, 1>(foo);
    CHECK(foo == 0xA3);
}

TEST_CASE(bit_clear)
{
    unsigned int foo = 0xA1;
    ucpp::bit::clear<0>(foo);
    CHECK(foo == 0xa0);
}

TEST_CASE(bit_clear_multiple)
{
    unsigned int foo = 0xA3;
    ucpp::bit::clear<0, 1>(foo);
    CHECK(foo == 0xA0);
}
