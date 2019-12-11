#include  "stream_helpers.h"

std::ostream & operator <<(std::ostream &os, std::vector<int>& intcode)
{
    for ( auto m : intcode)
    {
        os << m << "," ;
    }
    return os;
}

std::ostream & operator <<(std::ostream &os, const std::vector<int>& intcode)
{
    for ( auto m : intcode)
    {
        os << m << "," ;
    }
    return os;
}

std::ostream & operator <<(std::ostream &os, std::vector<std::string>& ss)
{
    for ( auto s : ss)
    {
        os << s << "," ;
    }
    return os;
}

std::ostream & operator <<(std::ostream &os, const std::vector<std::string>& ss)
{
    for ( auto s : ss)
    {
        os << s << "," ;
    }
    return os;
}
