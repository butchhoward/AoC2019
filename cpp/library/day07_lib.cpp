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

#include <experimental/optional>
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
        int_code::Storage output;
        int_code::Storage input = {phasesettings[amp], amp_signal};
        int_code::Storage amplifier_program = intcode;
        int_code::run_code(amplifier_program, input, output);
        if (output.size() != 1)
        {
            std::cerr << "thruster amp error amp=" << amp << " phase settings =" << phasesettings << std::endl;
            return 0;
        }

        amp_signal = output[0];
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
