#ifndef TEST_RUNNER_H
#define TEST_RUNNER_H

#include <string>
#include <functional>
#include <vector>
#include <iostream>

namespace test_runner {

typedef std::function<bool()> test_function;
typedef struct Test
{
    std::string description;
    test_function test;
} Test;

typedef std::vector<Test> Tests;

bool run_tests( const test_runner::Tests& tests);

}


#endif
