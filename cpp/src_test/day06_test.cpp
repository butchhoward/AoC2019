#include "day06_test.h"
#include "day06_lib.h"
#include "test_runner.h"


bool day06_test()
{
   test_runner::Tests tests = {
        //{"YYY Test", YYY_test}
        //,{"XXX", XXX_test}
    };

    return test_runner::run_tests(tests);
}
