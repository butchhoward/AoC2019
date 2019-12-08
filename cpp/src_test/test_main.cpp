#include "test_runner.h"

#include "int_code_test.h"
#include "day02_test.h"
#include "day03_test.h"
#include "day05_test.h"
#include "day06_test.h"
//MAKEMODULE INCLUDE MARKER. DO NOT DELETE

int main()
{
    test_runner::Tests tests = {
        {"int_code_unit_test",      int_code_unit_test}
        ,{"day02_test",              day02_test}
        ,{"day03_test",              day03_test}
        ,{"day05_test",              day05_test}
        ,{"day06_test", day06_test}
        //MAKEMODULE LIST MARKER. DO NOT DELETE
    };

    return test_runner::run_tests(tests) ? 0 : 1;
}
