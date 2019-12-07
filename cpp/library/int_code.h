#ifndef INT_CODE_H
#define INT_CODE_H

#include <vector>
typedef std::vector<int> Storage;

void run_code( std::vector<int>& intcode, Storage& input, Storage& output );
void run_code( std::vector<int>& intcode);

#endif
