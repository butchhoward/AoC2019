#ifndef INT_CODE_H
#define INT_CODE_H

#include <vector>

namespace int_code {

typedef std::vector<int> Storage;

Storage read_file(const std::string& filename);
void run_code( int_code::Storage& intcode, int_code::Storage& input, int_code::Storage& output );
void run_code( int_code::Storage& intcode);

}

#endif
