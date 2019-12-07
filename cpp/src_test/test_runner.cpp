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
            std::cout << "PASSED: " << t.description << std::endl;
        }
        else {
            result = false;
            std::cerr << "FAILED: " << t.description << std::endl;
        }
    }

    return result;
    
}
