#include "int_code.h"

#include <fstream>
#include <functional>
#include <map>

#include "stream_helpers.h"

using namespace int_code;

typedef enum {
    HALT = 99,
    ADD = 1,
    MUL = 2,
    INP = 3,
    OUT = 4,
    JTRUE = 5,
    JFALSE = 6,
    LESS = 7,
    EQUAL = 8
} Opcode;

typedef enum {
    POSITION = 0,
    IMMEDIATE = 1
} Mode;

typedef std::function<Storage::iterator(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)> Operation;
typedef std::map<int,Operation> Dispatch;

typedef std::function<int_code::Status(int_code::State& state)> StatefulOperation;

typedef std::map<int,StatefulOperation> StatefulDispatch;

static int get_value_from_param(Storage& intcode, int modes, int index, int param_value)
{
    int value(0);

    for (int m = 0; m < index; m++)
    {
        modes /= 10;
    }
    modes %= 10;

    if (modes == Mode::POSITION)
    {
        value = intcode.at(param_value);
    }
    else
    {
        value = param_value;
    }

    return value;
}

static int get_opcode(int code)
{
    return code % 100;
}

static int get_modes(int code)
{
    return code / 100;
}

Storage::iterator add(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)modes;
    (void)input;
    (void)output;
    auto a = get_value_from_param(intcode, modes, 0, *(PC+1));
    auto b = get_value_from_param(intcode, modes, 1, *(PC+2));
    auto d = *(PC+3);
    intcode.at(d) = a + b;

    return PC + 4;
}

int_code::Status add_stateful(int_code::State& state)
{
    state.pc = add(state.pc, get_modes(*state.pc), state.intcode, state.input, state.output);

    return state.status;
}

Storage::iterator mul(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)input;
    (void)output;
    auto a = get_value_from_param(intcode, modes, 0, *(PC+1));
    auto b = get_value_from_param(intcode, modes, 1, *(PC+2));
    auto d = *(PC+3);
    intcode.at(d) = a * b;
    return PC + 4;    
}

int_code::Status mul_stateful(int_code::State& state)
{
    state.pc = mul(state.pc, get_modes(*state.pc), state.intcode, state.input, state.output);

    return state.status;
}

Storage::iterator inp(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)modes;
    (void)output;

    int a(0);
    if (input.empty())
    {
        std::cerr << "Attempt to read empty input queue PC = " << PC - intcode.begin() << std::endl;
        PC = intcode.end();
        return PC;
    }

    a = input.front();
    input.erase(input.begin());

    intcode.at(*(PC+1)) = a;

    return PC + 2;    
}

int_code::Status inp_stateful(int_code::State& state)
{
    if (state.input.empty())
    {
        state.status = Status::blocking;
        return state.status;
    }

    state.pc = inp(state.pc, get_modes(*state.pc), state.intcode, state.input, state.output);

    return state.status;
}

Storage::iterator out(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)input;

    int a = get_value_from_param(intcode, modes, 0, *(PC+1));
    output.push_back(a);
    return PC + 2;    
}

int_code::Status out_stateful(int_code::State& state)
{
    state.pc = out(state.pc, get_modes(*state.pc), state.intcode, state.input, state.output);

    return state.status;
}

Storage::iterator halt(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)PC;
    (void)modes;
    (void)input;
    (void)output;
    return intcode.end();  
}

int_code::Status halt_stateful(int_code::State& state)
{
    state.pc = halt(state.pc, get_modes(*state.pc), state.intcode, state.input, state.output);

    return state.status;
}

Storage::iterator less(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)input;
    (void)output;

    int a = get_value_from_param(intcode, modes, 0, *(PC+1));
    int b = get_value_from_param(intcode, modes, 1, *(PC+2));
    intcode.at(*(PC+3)) = a < b ? 1 : 0;

    return PC+4;
}

int_code::Status less_stateful(int_code::State& state)
{
    state.pc = less(state.pc, get_modes(*state.pc), state.intcode, state.input, state.output);

    return state.status;
}

Storage::iterator equal(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)input;
    (void)output;

    int a = get_value_from_param(intcode, modes, 0, *(PC+1));
    int b = get_value_from_param(intcode, modes, 1, *(PC+2));
    intcode.at(*(PC+3)) = a == b ? 1 : 0;

    return PC+4;
}

int_code::Status equal_stateful(int_code::State& state)
{
    state.pc = equal(state.pc, get_modes(*state.pc), state.intcode, state.input, state.output);

    return state.status;
}

Storage::iterator jump_if_true(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)input;
    (void)output;

    int a = get_value_from_param(intcode, modes, 0, *(PC+1));
    if (a)
    {
        int b = get_value_from_param(intcode, modes, 1, *(PC+2));
        PC = intcode.begin() + b;
    }
    else
    {
        PC+=3;
    }

    return PC;
}

int_code::Status jump_if_true_stateful(int_code::State& state)
{
    state.pc = jump_if_true(state.pc, get_modes(*state.pc), state.intcode, state.input, state.output);

    return state.status;
}

Storage::iterator jump_if_false(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)input;
    (void)output;

    int a = get_value_from_param(intcode, modes, 0, *(PC+1));
    if (a == 0)
    {
        int b = get_value_from_param(intcode, modes, 1, *(PC+2));
        PC = intcode.begin() + b;
    }
    else
    {
        PC+=3;
    }

    return PC;
}

int_code::Status jump_if_false_stateful(int_code::State& state)
{
    state.pc = jump_if_false(state.pc, get_modes(*state.pc), state.intcode, state.input, state.output);

    return state.status;
}

Storage int_code::read_file(const std::string& filename)
{
    Storage intcode;
    
    std::ifstream datafile(filename);
    if(!datafile)
    {
        std::cout << "Error opening input file" << std::endl;
        return intcode;
    }

    for (;;)
    {
        int code = 0;
        datafile >> code;
        if (datafile.eof())
        {
            break;
        }
        intcode.push_back(code);
        char comma = ',';
        datafile >> comma;
        if (datafile.eof())
        {
            break;
        }
    }


    return intcode;
}


void int_code::run_code( int_code::Storage& intcode, int_code::Storage& input, int_code::Storage& output )
{
    Dispatch dispatch;
    dispatch[ADD] = add;
    dispatch[MUL] = mul;
    dispatch[INP] = inp;
    dispatch[OUT] = out;
    dispatch[JTRUE] = jump_if_true;
    dispatch[JFALSE] = jump_if_false;
    dispatch[LESS] = less;
    dispatch[EQUAL] = equal;
    dispatch[HALT] = halt;

    for(Storage::iterator PC = intcode.begin(); PC != intcode.end();)
    {
        int opcode = get_opcode(*PC);
        int modes = get_modes(*PC);

        Dispatch::iterator opit = dispatch.find(opcode);
        if (opit == dispatch.end())
        {
            std::cerr << "invalid opcode (" << *PC << ") at " << PC - intcode.begin() << std::endl;
            return;
        }
        PC = dispatch[opcode](PC, modes, intcode, input, output);
    }
}

void int_code::run_code( int_code::Storage& intcode)
{
    Storage input;
    Storage output;
    run_code(intcode, input, output);
}

int_code::Status int_code::run_code( int_code::State& state )
{
    StatefulDispatch dispatch;
    dispatch[ADD] = add_stateful;
    dispatch[MUL] = mul_stateful;
    dispatch[INP] = inp_stateful;
    dispatch[OUT] = out_stateful;
    dispatch[JTRUE] = jump_if_true_stateful;
    dispatch[JFALSE] = jump_if_false_stateful;
    dispatch[LESS] = less_stateful;
    dispatch[EQUAL] = equal_stateful;
    dispatch[HALT] = halt_stateful;

    if (state.status == Status::initializing )
    {
        state.pc = state.intcode.begin();
        state.status = Status::running;
    }

    for(; state.pc != state.intcode.end() && state.status == running; )
    {
        auto opcode = get_opcode(*state.pc);
        StatefulDispatch::iterator opit = dispatch.find( opcode );
        if (opit == dispatch.end())
        {
            std::cerr << "invalid opcode (" << *state.pc << ") at " << state.pc - state.intcode.begin() << std::endl;
            state.status = Status::exception;
            break;
        }

        state.status = dispatch[opcode](state);
        if (state.pc == state.intcode.end())
        {
            state.status = Status::halted;
        }
    }
    return state.status;
}

