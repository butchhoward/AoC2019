#include "test_runner.h"

using namespace test_runner;

bool test_runner::run_tests( const test_runner::Tests& tests )
{
    if (tests.size() == 0)
    {
        return false;
    }
    
    bool result(true);

    for (auto t : tests)
    {
        if ( t.test() )
        {
            std::cout << "PASSED: ";
        }
        else {
            result = false;
            std::cout << "FAILED: ";
        }
        std::cout << t.description << std::endl;
    }

    return result;
    
}
