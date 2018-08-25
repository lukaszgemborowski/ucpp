#ifndef UCPP_TESTING_H
#define UCPP_TESTING_H

#include <stddef.h>

struct test_results
{
    test_results() : current_check(0), success(true) {}
    int current_check;
    bool success;
};

#if !defined(UCPP_TEST_DISABLE_STDIO) && defined(UCPP_TEST_MAIN)
#include <iostream>
struct iostream_handler
{
    void start(const char *tc_name) const {
        std::cout << tc_name << "... ";
    }

    void stop(const test_results &res) const {
        if (res.success)
            std::cout << "PASSED" << std::endl;
        else
            std::cout << "FAILED" << std::endl;
    }
};
#endif

struct base_test_case;
extern base_test_case *root_test;

struct base_test_case {
    test_results results;
    base_test_case *next;
    base_test_case() : next(NULL) {
        next = root_test;
        root_test = this;
    }

    virtual void run() = 0;
    virtual const char* name() const = 0;
};

#define TEST_CASE(tc_name) \
    struct tc_name##_test_case : public base_test_case { \
        void run(); \
        const char* name() const { return #tc_name; } \
    }; \
    tc_name##_test_case tc_name##_test_case_instance; \
    void tc_name##_test_case::run()


#define CHECK(expr) \
    results.current_check ++; \
    if (!(expr)) { \
        results.success = false; \
        return; }

#if defined(UCPP_TEST_MAIN)
#define TEST_INIT \
    base_test_case *root_test = NULL;

#ifndef UCPP_TEST_DISABLE_STDIO
template<typename ResultHandler = iostream_handler>
#else
template<typename ResultHandler>
#endif
void test_run(ResultHandler handler = ResultHandler())
{
    base_test_case *current = root_test;

    while (current) {
        handler.start(current->name());
        current->run();
        handler.stop(current->results);

        current = current->next;
    }
}
#endif

#endif
