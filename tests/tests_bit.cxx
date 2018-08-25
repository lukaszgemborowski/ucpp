#include "ucpp/testing.h"
#include "ucpp/bit.h"

TEST_CASE(bit_set)
{
    unsigned int foo = 0xA0;
    ucpp::bit::set<3>(foo);
    CHECK(foo == 0xA8);
}