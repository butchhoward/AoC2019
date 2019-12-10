#include "day07_test.h"
#include "day07_lib.h"
#include "test_runner.h"
#include "stream_helpers.h"

#include "int_code.h"




bool sample_thruster_amplifier_1()
{
    // Max thruster signal 43210 (from phase setting sequence 4,3,2,1,0):
    // 3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0

    int_code::Storage intcode = {3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0};

    auto t = day07lib::find_optimum_amplifier_setting(intcode);

    int_code::Storage expected_phase_settings = {4,3,2,1,0};

    return 43210 == t.first && expected_phase_settings == t.second;
}

bool sample_thruster_amplifier_2()
{
    // Max thruster signal 54321 (from phase setting sequence 0,1,2,3,4):
    // 3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0

    int_code::Storage intcode = {3,23,3,24,1002,24,10,24,1002,23,-1,23,101,5,23,23,1,24,23,23,4,23,99,0,0};

    auto t = day07lib::find_optimum_amplifier_setting(intcode);

    int_code::Storage expected_phase_settings = {0,1,2,3,4};

    return 54321 == t.first && expected_phase_settings == t.second;
}

bool sample_thruster_amplifier_3()
{
    // Max thruster signal 65210 (from phase setting sequence 1,0,4,3,2):
    // 3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0

    int_code::Storage intcode = {3,31,3,32,1002,32,10,32,1001,31,-2,31,1007,31,0,33,1002,33,7,33,1,33,31,31,1,32,31,31,4,31,99,0,0,0};

    auto t = day07lib::find_optimum_amplifier_setting(intcode);

    int_code::Storage expected_phase_settings = {1,0,4,3,2};

    return 65210 == t.first && expected_phase_settings == t.second;
}

bool sample_thruster_amplifier_test_correct_final()
{
    // Max thruster signal 43210 (from phase setting sequence 4,3,2,1,0):
    // 3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0

    int_code::Storage intcode = {3,15,3,16,1002,16,10,16,1,16,15,15,4,15,99,0,0};
    int_code::Storage expected_phase_settings = {4,3,2,1,0};

    int output = day07lib::run_amplifier_sequence(intcode, expected_phase_settings);

    return 43210 == output;
}

bool sample_amplifier_with_feedback_1()
{
    // Max thruster signal 139629729 (from phase setting sequence 9,8,7,6,5):
    // 3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5

    int_code::Storage intcode = {3,26,1001,26,-4,26,3,27,1002,27,2,27,1,27,26,27,4,27,1001,28,-1,28,1005,28,6,99,0,0,5};
    int_code::Storage expected_phase_settings = {9,8,7,6,5};

    int output = day07lib::run_amplifier_sequence_with_feedback(intcode, expected_phase_settings);

    return 139629729 == output;

}

bool sample_amplifier_with_feedback_2()
{
    // Max thruster signal 18216 (from phase setting sequence 9,7,8,5,6):
    /*
    3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,
    -5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,
    53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10    
    */

    int_code::Storage intcode = { 
        3,52,1001,52,-5,52,3,53,1,52,56,54,1007,54,5,55,1005,55,26,1001,54,
        -5,54,1105,1,12,1,53,54,53,1008,54,0,55,1001,55,1,55,2,53,55,53,4,
        53,1001,56,-1,56,1005,56,6,99,0,0,0,0,10    
    };

    int_code::Storage expected_phase_settings = {9,7,8,5,6};

    int output = day07lib::run_amplifier_sequence_with_feedback(intcode, expected_phase_settings);

    return 18216 == output;

}

bool day07_test()
{
   test_runner::Tests tests = {
        {"sample_thruster_amplifier_1", sample_thruster_amplifier_1}
        ,{"sample_thruster_amplifier_2", sample_thruster_amplifier_2}
        ,{"sample_thruster_amplifier_3", sample_thruster_amplifier_3}
        ,{"sample_thruster_amplifier_test_correct_final", sample_thruster_amplifier_test_correct_final}
        ,{"sample_amplifier_with_feedback_1", sample_amplifier_with_feedback_1}
        ,{"sample_amplifier_with_feedback_2",sample_amplifier_with_feedback_2}
        //,{"XXX", XXX_test}
    };

    return test_runner::run_tests(tests);
}
