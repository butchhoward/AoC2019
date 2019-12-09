#ifndef INT_CODE_H
#define INT_CODE_H

#include <vector>

namespace int_code {

typedef std::vector<int> Storage;

Storage read_file(const std::string& filename);
void run_code( int_code::Storage& intcode, int_code::Storage& input, int_code::Storage& output );
void run_code( int_code::Storage& intcode);

typedef enum 
{
    initializing,
    running,
    blocking,
    halted,
    exception
} Status;

typedef struct State 
{
    State() :
        status(Status::initializing),
        pc(intcode.end())
    {
    }
    Status status;
    int_code::Storage intcode;
    int_code::Storage input; 
    int_code::Storage output;
    Storage::iterator pc;
} State;

int_code::Status  run_code( int_code::State& state );


}

#endif
