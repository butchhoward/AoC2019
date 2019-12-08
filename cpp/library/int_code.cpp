#include "int_code.h"
#include <functional>
#include <map>

#include "stream_helpers.h"

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

    a = input.back();
    input.pop_back();

    intcode.at(*(PC+1)) = a;

    return PC + 2;    
}

Storage::iterator out(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)input;

    int a = get_value_from_param(intcode, modes, 0, *(PC+1));
    output.push_back(a);
    return PC + 2;    
}

Storage::iterator halt(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)PC;
    (void)modes;
    (void)input;
    (void)output;
    return intcode.end();  
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

Storage::iterator equal(Storage::iterator PC, int modes, Storage& intcode, Storage& input, Storage& output)
{
    (void)input;
    (void)output;

    int a = get_value_from_param(intcode, modes, 0, *(PC+1));
    int b = get_value_from_param(intcode, modes, 1, *(PC+2));
    intcode.at(*(PC+3)) = a == b ? 1 : 0;

    return PC+4;
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

void run_code( Storage& intcode, Storage& input, Storage& output )
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
        int opcode = *PC % 100;
        int modes = *PC / 100;
        Dispatch::iterator opit = dispatch.find(opcode);
        if (opit == dispatch.end())
        {
            std::cerr << "invalid opcode (" << *PC << ") at " << PC - intcode.begin() << std::endl;
            return;
        }
        PC = dispatch[opcode](PC, modes, intcode, input, output);
    }
}

void run_code( Storage& intcode)
{
    Storage input;
    Storage output;
    run_code(intcode, input, output);
}
