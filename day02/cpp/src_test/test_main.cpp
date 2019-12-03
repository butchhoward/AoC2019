#include <iostream>

auto calculate_fuel(const int mass)
{
    return  (mass /3) - 2;
}

int main()
{
    // For a mass of 12, divide by 3 and round down to get 4, then subtract 2 to get 2.
    // For a mass of 14, dividing by 3 and rounding down still yields 4, so the fuel required is also 2.
    // For a mass of 1969, the fuel required is 654.
    // For a mass of 100756, the fuel required is 33583.

    if ( calculate_fuel(12) != 2)
    {
        std::cout << "Failed: 12 == 2 :" << calculate_fuel(12) << std::endl;
    }
    if ( calculate_fuel(14) != 2)
    {
        std::cout << "Failed: 14 == 2 :" << calculate_fuel(14) << std::endl;
    }
    if ( calculate_fuel(1969) != 654)
    {
        std::cout << "Failed: 1969 == 654 :" << calculate_fuel(1969) << std::endl;
    }
    if ( calculate_fuel(100756) != 33583)
    {
        std::cout << "Failed: 100756 == 33583 :" << calculate_fuel(100756) << std::endl;
    }
    return 0;
}
