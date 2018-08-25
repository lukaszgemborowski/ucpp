CXX="g++"
CXXFLAGS="-std=c++11"
FILES="tests/tests_array.cxx tests/tests_stack.cxx tests/local_main.cxx tests/tests_bitmap_allocator.cxx tests/tests_uninitialized_array.cxx"

set -e

$CXX $CXXFLAGS $FILES -Iinclude -o local_tests
./local_tests