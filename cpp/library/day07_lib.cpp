#include "day07_lib.h"

#include "stream_helpers.h"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

#include <iostream>
#include <iomanip>
#include <ios>
#include <sstream>

#include <optional>
#include <experimental/set>
#include <numeric>
#include <iterator>
#include <limits>

using namespace day07lib;

int day07lib::run_amplifier_sequence(const int_code::Storage& intcode, const int_code::Storage& phasesettings)
{
    int amp_signal = 0;
    for (int amp = 0; amp < 5; amp++)
    {
        int_code::State computer(intcode);
        computer.input = {phasesettings[amp], amp_signal};

        int_code::run_code(computer);
        if (computer.output.size() != 1)
        {
            std::cerr << "thruster amp error amp=" << amp << " phase settings =" << phasesettings << std::endl;
            return 0;
        }

        amp_signal = computer.output[0];
    }

    return amp_signal;

}

int day07lib::run_amplifier_sequence_with_feedback(const int_code::Storage& intcode, const int_code::Storage& phasesettings)
{
    int_code::State computers[5] = {
        {intcode}, 
        {intcode}, 
        {intcode}, 
        {intcode}, 
        {intcode}
    };

    int amp_signal = 0;
    int cycles(0);

    bool feedback_cylce_is_running(true);
    while(feedback_cylce_is_running)
    {
        for (int amp = 0; amp < 5; amp++)
        {
            if (cycles == 0)
            {
                computers[amp].input.push_back(phasesettings[amp]);
            }
            computers[amp].input.push_back(amp_signal);

            int_code::run_code(computers[amp]);
            if (computers[amp].output.size() != 1)
            {
                std::cerr << "feedback amp error amp=" << amp 
                        << " cycle=" << cycles 
                        << " phase settings =" << phasesettings 
                        << " state : " << computers[amp]
                        << std::endl;
                return 0;
            }

            amp_signal = computers[amp].output[0];
            computers[amp].output.clear();
        }

        if (computers[4].status == int_code::Status::halted)
        {
            feedback_cylce_is_running = false;
        }

        ++cycles;
    }

    return amp_signal;
}


std::pair<int, int_code::Storage> day07lib::find_optimum_amplifier_setting(const int_code::Storage& intcode)
{

    int_code::Storage phasesettings = {0,1,2,3,4};

    int thruster_signal = 0;
    int_code::Storage phasesettings_max;

    do
    {
        auto amp_sequence_output = day07lib::run_amplifier_sequence(intcode, phasesettings);

        if (amp_sequence_output > thruster_signal)
        {
            thruster_signal = amp_sequence_output;
            phasesettings_max = phasesettings;
        }

    } while (std::next_permutation(phasesettings.begin(), phasesettings.end()));

    return std::make_pair(thruster_signal, phasesettings_max);    
}

std::pair<int, int_code::Storage> day07lib::find_optimum_amplifier_setting_with_feedback(const int_code::Storage& intcode)
{

    int_code::Storage phasesettings = {5,6,7,8,9};

    int thruster_signal = 0;
    int_code::Storage phasesettings_max;

    do
    {
        auto amp_sequence_output = day07lib::run_amplifier_sequence_with_feedback(intcode, phasesettings);

        if (amp_sequence_output > thruster_signal)
        {
            thruster_signal = amp_sequence_output;
            phasesettings_max = phasesettings;
        }

    } while (std::next_permutation(phasesettings.begin(), phasesettings.end()));

    return std::make_pair(thruster_signal, phasesettings_max);    
}
