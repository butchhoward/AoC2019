#include  "stream_helpers.h"

std::ostream & operator <<(std::ostream &os, std::vector<int>& intcode)
{
    for ( auto m : intcode)
    {
        os << m << "," ;
    }
    return os;
}
