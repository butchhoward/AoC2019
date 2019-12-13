#!/usr/bin/env bash

# assume running from cpp folder
# ./scripts/make_module day05
# creates library, src_test, src files for day05 with skeleton files


MODULE=$1
MODULEUP=${MODULE^^}

read -r -d '' LIB_HEADER <<-EOT
#ifndef ${MODULEUP}_LIB_H
#define ${MODULEUP}_LIB_H

namespace ${MODULE}lib {

int ${MODULE}_lib_function();

}
#endif
EOT

read -r -d '' LIB_CPP <<-EOT
#include "${MODULE}_lib.h"

int ${MODULE}lib::${MODULE}_lib_function()
{
    return -1;
}
EOT

read -r -d '' SRC_HEADER <<-EOT
#ifndef ${MODULEUP}_H
#define ${MODULEUP}_H

#include <string>

int ${MODULE}(const std::string& filename);



#endif
EOT

read -r -d '' SRC_CPP <<-EOT
#include "${MODULE}.h"
#include "${MODULE}_lib.h"

int ${MODULE}(const std::string& filename)
{
    (void)filename;

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

bool ${MODULE}_test_XXX()
{
    return false;
}

bool ${MODULE}_test()
{
   test_runner::Tests tests = {
        {"XXX Test", ${MODULE}_test_XXX}
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


INCLUDE_MARKER="//MAKEMODULE INCLUDE MARKER. DO NOT DELETE"
LIST_MARKER="//MAKEMODULE LIST MARKER. DO NOT DELETE"

INCLUDE_ITEM="\#include \"${MODULE}_test\.h\""
LIST_ITEM=",{\"${MODULE}_test\", ${MODULE}_test}"

# the goofiness with the $ and \\\n is to get a newline in the replacement text
sed -E -i '' -e "s~${INCLUDE_MARKER}~${INCLUDE_ITEM}"$'\\\n'"&~g" ./src_test/test_main.cpp
sed -E -i '' -e "s~${LIST_MARKER}~${LIST_ITEM}"$'\\\n'"        &~g"  ./src_test/test_main.cpp
