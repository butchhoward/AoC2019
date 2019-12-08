#include "day01.h"
#include "day02.h"
#include "day03.h"
#include "day04.h"
#include "day05.h"

#include <iostream>
#include <string>
#include <sstream>

int main(int argc, char *argv[])
{
    if (argc < 3)
    {
        std::cout << "Need a day and a file name" << std::endl;
        std::exit(1);
    }

    int day(0);
    std::istringstream stream(argv[1]);
    stream >> day;
    std::string datafile(argv[2]);
    //std::cout << day << std::endl << datafile << std::endl;

    switch (day) {
    case 1:
        day01(datafile);
        break;
    case 2:
        day02(datafile);
        break;
    case 3:
        day03(datafile);
        break;
    case 4:
        day04(datafile);
        break;
    case 5:
        day05(datafile);
        break;
    }

    return 0;
}
