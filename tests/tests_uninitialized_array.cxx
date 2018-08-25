#include "ucpp/testing.h"
#include "ucpp/uninitialized_array.h"

TEST_CASE(construct_uninitialized_array)
{
    static int count = 0;
    struct default_constructible {
        default_constructible() {
            count ++;
        }
    };

    ucpp::uninitialized_array<default_constructible, 10> arr;
    CHECK(count == 0);
}

TEST_CASE(construct_and_destruct_one_element)
{
    static int count = 0;
    struct default_constructible {
        default_constructible() {
            count ++;
        }
        ~default_constructible() {
            count --;
        }
    };

    ucpp::uninitialized_array<default_constructible, 10> arr;
    CHECK(count == 0);

    arr.construct(0);
    CHECK(count == 1);

    arr.destruct(0);
    CHECK(count == 0);
}

TEST_CASE(uninitialized_array_check_ownership)
{
     ucpp::uninitialized_array<int, 2> arr;
     int out_of_array = 0;

     arr.construct(0);
     arr.construct(1);

     CHECK(arr.own(arr[0]));
     CHECK(arr.own(arr[1]));
     CHECK(arr.own(out_of_array) == false);
}
