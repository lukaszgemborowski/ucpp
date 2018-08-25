// disable standard "cout printer"
#define UCPP_TEST_DISABLE_STDIO

// this is "main" file
#define UCPP_TEST_MAIN
#include "ucpp/testing.h"
#include "ucpp/avr/usart.h"

// we'll print results on usart
ucpp::avr::usart<38400> usart0;

// simple printing function, we don't need more right now
namespace {
void print(const char *text)
{
    while (*text) {
        usart0.write_byte(*text);
        text++;
    }
}
}

struct usart0_printer
{
    // print test case name
    void start(const char *tc_name) const {
        print(tc_name);
        print("... ");
    }

    // print test result
    void stop(const test_results &res) const {
        if (res.success)
            print("PASSED\n\r");
        else
            print("FAILED\n\r");
    }
};

TEST_INIT;

int main() {
    usart0.init();

    // run all tests using usart0 printer
    test_run<usart0_printer>();
    return 0;
}