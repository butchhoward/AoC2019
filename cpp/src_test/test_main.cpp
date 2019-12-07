#include "int_code_test.h"

#include <string>
#include <functional>
#include <vector>
#include <iostream>

#include "day02_test.h"
#include "day03_test.h"
#include "day05_test.h"


typedef struct Test
{
    std::string description;
    std::function<bool()> test;
} Test;

typedef std::vector<Test> Tests;

int main()
{
    Tests tests = {
        {"int_code_unit_test",      int_code_unit_test},
        {"day02_test",              day02_test},
        {"day03_test",              day03_test},
        {"day05_test",              day05_test}
    };

    for (auto t : tests)
    {
        if ( t.test() )
        {
            std::cout << "PASSED: ";
        }
        else {
            std::cout << "FAILED: ";
        }
        std::cout << t.description << std::endl;
    }

    return 0;
}
