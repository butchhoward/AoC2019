#ifndef DAY07_LIB_H
#define DAY07_LIB_H

#include "int_code.h"

namespace day07lib {


std::pair<int, Storage> find_optimum_amplifier_setting(const Storage& intcode);
int run_amplifier_sequence(const Storage& intcode, const Storage& phasesettings);


}

#endif
