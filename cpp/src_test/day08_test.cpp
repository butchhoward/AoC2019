#include "day08_test.h"
#include "day08_lib.h"
#include "test_runner.h"

bool day08_test_XXX()
{
    return true;
}

bool day08_test()
{
   test_runner::Tests tests = {
        {"XXX Test", day08_test_XXX}
        //,{"XXX", XXX_test}
    };

    return test_runner::run_tests(tests);
}
