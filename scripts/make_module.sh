#!/usr/bin/env bash

# assume running from cpp folder
# ../scripts/make_module day05
# creates library, src_test, src files for day05 with skeleton files


MODULE=$1
MODULEUP=${MODULE^^}

read -r -d '' LIB_HEADER <<-EOT
#ifndef ${MODULEUP}_LIB_H
#define ${MODULEUP}_LIB_H

int ${MODULE}_lib_function();

#endif
EOT

read -r -d '' LIB_CPP <<-EOT
#include "${MODULE}_lib.h"

int ${MODULE}_lib_function()
{
    return -1;
}
EOT

read -r -d '' SRC_HEADER <<-EOT
#ifndef ${MODULEUP}_H
#define ${MODULEUP}_H

#include <vector>

int ${MODULE}_function();

#endif
EOT

read -r -d '' SRC_CPP <<-EOT
#include "${MODULE}.h"
#include "${MODULE}_lib.h"

int ${MODULE}_function()
{
    return -1;
}
EOT

read -r -d '' TEST_HEADER <<-EOT
#ifndef ${MODULEUP}_TEST_H
#define ${MODULEUP}_TEST_H

bool ${MODULE}_test();

#endif
EOT

read -r -d '' TEST_CPP <<-EOT
#include "${MODULE}_test.h"
#include "${MODULE}_lib.h"
#include "test_runner.h"


bool ${MODULE}_test()
{
   test_runner::Tests tests = {
        //{"YYY Test", YYY_test}
        //,{"XXX", XXX_test}
    };

    return test_runner::run_tests(tests);
}
EOT

echo "${LIB_HEADER}" > ./library/${MODULE}_lib.h
echo "${LIB_CPP}" > ./library/${MODULE}_lib.cpp
echo "${SRC_HEADER}" > ./src/${MODULE}.h
echo "${SRC_CPP}" > ./src/${MODULE}.cpp
echo "${TEST_HEADER}" > ./src_test/${MODULE}_test.h
echo "${TEST_CPP}" > ./src_test/${MODULE}_test.cpp
