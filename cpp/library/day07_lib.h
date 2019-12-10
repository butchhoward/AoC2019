#ifndef DAY07_LIB_H
#define DAY07_LIB_H

#include "int_code.h"

namespace day07lib {


std::pair<int, int_code::Storage> find_optimum_amplifier_setting(const int_code::Storage& intcode);

int run_amplifier_sequence(const int_code::Storage& intcode, const int_code::Storage& phasesettings);
int run_amplifier_sequence_with_feedback(const int_code::Storage& intcode, const int_code::Storage& phasesettings);

}

#endif
