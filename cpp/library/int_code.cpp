#include "int_code.h"

void run_code( std::vector<int>& intcode )
{
    for(std::vector<int>::size_type i = 0; i < intcode.size();)
    {
        switch (intcode.at(i))
        {
            case 1:
            {
                auto a = intcode.at(intcode.at(i+1));
                auto b = intcode.at(intcode.at(i+2));
                auto d = intcode.at(i+3);
                //std::cout << "add " << a << " " << b << " " << d << std::endl;
                intcode.at(d) = a + b;
                i += 4;
            }
                break;
            case 2:
            {
                auto a = intcode.at(intcode.at(i+1));
                auto b = intcode.at(intcode.at(i+2));
                auto d = intcode.at(i+3);
                //std::cout << "mul " << a << " " << b << " " << d << std::endl;
                intcode.at(d) = a * b;
                i += 4;
            }
                break;
            default:
                return;
        }
    }
}
