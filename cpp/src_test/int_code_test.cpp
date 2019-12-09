
#include "int_code_test.h"
#include "int_code.h"
#include "test_runner.h"

#include "stream_helpers.h"

#include <iostream>

static bool test_run(std::vector<int>& v, const std::vector<int>& r, Storage& input, Storage& output)
{
    run_code(v, input, output);
    std::vector<int>::const_iterator a, b;
    for (  a = v.begin(), b = r.begin(); a != v.end(); a++, b++)
    {
        if ( *a != *b )
        {
            return false;
        }
    }
    return true;
}
static bool test_run(std::vector<int>& v, const std::vector<int>& r)
{
    Storage input;
    Storage output;
    return test_run(v, r, input, output);
}


bool intcode_outputs_the_input()
{        
    Storage v = {3,0,4,0,99};
    Storage r = {77,0,4,0,99};
    Storage input = {77};
    Storage output;
    
    bool t = test_run( v, r, input, output );
    bool d = (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 77);

    return t && d;
}

bool intcode_outputs_the_two_inputs()
{        
    Storage v = {3,0,4,0,3,0,4,0,99};
    Storage r = {76,0,4,0,3,0,4,0,99};
    Storage input = {77,76};
    Storage output;
    
    bool t = test_run( v, r, input, output );
    bool d = (input.size() == 0) &&
            (output.size() == 2) &&
            (output.at(0) == 77) && 
            (output.at(1) == 76);
        
    return t && d;
}

bool intcode_consumes_the_input()
{        
    Storage v = {3,3,99,0};
    Storage r = {3,3,99,77};
    Storage input = {77};
    Storage output;
    
    bool t = test_run( v, r, input, output );
    bool d = (input.size() == 0) &&
            (output.size() == 0);

    return t && d;
}

bool intcode_outputs_an_indirect_value()
{        
    Storage v = {4,3,99,77};
    Storage r = v;
    Storage input;
    Storage output;
    
    bool t = test_run( v, r, input, output );
    bool d = (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 77);

    return t && d;
}

bool intcode_outputs_a_direct_value()
{        
    Storage v = {1 * 100 + 4,2,99};
    Storage r = v;
    Storage input;
    Storage output;
    
    bool t = test_run( v, r, input, output );
    bool d = (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 2);

    return t && d;
}

bool add_two_direct_values()
{
    std::vector<int> v = {1101,2,3,0,99};
    std::vector<int> r = {5,2,3,0,99};
    return test_run( v, r );
}

bool mul_two_direct_values()
{
    std::vector<int> v = {1102,3,7,0,99};
    std::vector<int> r = {21,3,7,0,99};
    return test_run( v, r );
}

bool position_mode_input_equals_8()
{
    Storage v = {3,9,8,9,10,9,4,9,99,-1,8};
    Storage input = {8};
    Storage output;
    
    run_code( v, input, output );
    return (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 1);
}

bool position_mode_less_8()
{
    Storage v = {3,9,7,9,10,9,4,9,99,-1,8};
    Storage input = {5};
    Storage output;
    
    run_code( v, input, output );
    return (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 1);
}

bool immediate_mode_input_equals_8()
{
    Storage v = {3,3,1108,-1,8,3,4,3,99};
    Storage input = {8};
    Storage output;
    
    run_code( v, input, output );
    return (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 1);
}

bool immediate_mode_less_8()
{
    
    Storage v = {3,3,1107,-1,8,3,4,3,99};
    Storage input = {5};
    Storage output;
    
    run_code( v, input, output );
    return (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 1);    
}

bool jump_output_1_when_input_nonzero()
{
    Storage v = {3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9};
    Storage input = {5};
    Storage output;
    
    run_code( v, input, output );
    return (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 1);    
}

bool jump_output_0_when_input_zero()
{
    Storage v = {3,12,6,12,15,1,13,14,13,4,13,99,-1,0,1,9};
    Storage input = {0};
    Storage output;
    
    run_code( v, input, output );
    return (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 0);    
}


bool if_input_above_8_output_1001()
{
    Storage v = {3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99};
    Storage input = {9};
    Storage output;
    
    run_code( v, input, output );
    return (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 1001);    
}

bool if_input_below_8_output_999()
{
    Storage v = {3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99};
    Storage input = {5};
    Storage output;
    
    run_code( v, input, output );
    return (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 999);    
}

bool if_input_equal_8_output_1000()
{
    Storage v = {3,21,1008,21,8,20,1005,20,22,107,8,21,20,1006,20,31,1106,0,36,98,0,0,1002,21,125,20,4,20,1105,1,46,104,999,1105,1,46,1101,1000,1,20,4,20,1105,1,46,98,99};
    Storage input = {8};
    Storage output;
    
    run_code( v, input, output );
    return (input.size() == 0) &&
            (output.size() == 1) &&
            (output.at(0) == 1000);    
}

bool int_code_unit_test()
{
    // 1,0,0,0,99 becomes 2,0,0,0,99 (1 + 1 = 2).
    // 2,3,0,3,99 becomes 2,3,0,6,99 (3 * 2 = 6).
    // 2,4,4,5,99,0 becomes 2,4,4,5,99,9801 (99 * 99 = 9801).
    //1,1,1,4,99,5,6,0,99 becomes 30,1,1,4,2,5,6,0,99.


    {
        std::vector<int> v = {1,9,10,3,2,3,11,0,99,30,40,50};
        std::vector<int> r = {3500,9,10,70,2,3,11,0,99,30,40,50};
        if (!test_run( v, r ))
        {
            std::cerr << " Fail 1 " << std::endl 
                      << "Expected: " << r << std::endl 
                      << "  Actual: " << v << std::endl;
            return false;
        }
    }
    {
        std::vector<int> v = {1,0,0,0,99};
        std::vector<int> r = {2,0,0,0,99};
        if (!test_run( v, r ))
        {
            std::cerr << " Fail 2 " << std::endl 
                      << "Expected: " << r << std::endl 
                      << "  Actual: " << v << std::endl;
            return false;
        }
    }
    {
        std::vector<int> v = {2,3,0,3,99};
        std::vector<int> r = {2,3,0,6,99};
        if (!test_run( v, r ))
        {
            std::cerr << " Fail 3 " << std::endl 
                      << "Expected: " << r << std::endl 
                      << "  Actual: " << v << std::endl;
            return false;
        }
    }
    {
        std::vector<int> v = {2,4,4,5,99,0};
        std::vector<int> r = {2,4,4,5,99,9801};
        if (!test_run( v, r ))
        {
            std::cerr << " Fail 4 " << std::endl 
                      << "Expected: " << r << std::endl 
                      << "  Actual: " << v << std::endl;
            return false;
        }
    }
    {
        std::vector<int> v = {1,1,1,4,99,5,6,0,99};
        std::vector<int> r = {30,1,1,4,2,5,6,0,99};
        if (!test_run( v, r ))
        {
            std::cerr << " Fail 5 " << std::endl 
                      << "Expected: " << r << std::endl 
                      << "  Actual: " << v << std::endl;
            return false;
        }
    }


    test_runner::Tests tests = {
        {"intcode_outputs_the_input",      intcode_outputs_the_input}
        ,{"intcode_consumes_the_input",              intcode_consumes_the_input}
        ,{"intcode_outputs_an_indirect_value",              intcode_outputs_an_indirect_value}
        ,{"intcode_outputs_a_direct_value", intcode_outputs_a_direct_value}
        ,{"intcode_outputs_the_two_inputs", intcode_outputs_the_two_inputs}

        ,{"add_two_direct_values", add_two_direct_values}
        ,{"mul_two_direct_values", mul_two_direct_values}

        ,{"position_mode_input_equals_8", position_mode_input_equals_8}
        ,{"position_mode_less_8", position_mode_less_8}
        ,{"immediate_mode_input_equals_8", immediate_mode_input_equals_8}
        ,{"immediate_mode_less_8", immediate_mode_less_8}

        ,{"jump_output_1_when_input_nonzero", jump_output_1_when_input_nonzero}
        ,{"jump_output_0_when_input_zero", jump_output_0_when_input_zero}

        ,{"if_input_equal_8_output_1000", if_input_equal_8_output_1000}
        ,{"if_input_below_8_output_999",if_input_below_8_output_999}
        ,{"if_input_above_8_output_1001", if_input_above_8_output_1001}
    };

    return test_runner::run_tests(tests);

}
