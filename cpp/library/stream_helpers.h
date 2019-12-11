#ifndef STREAM_HELPERS_H
#define STREAM_HELPERS_H

#include <iostream>
#include <vector>

std::ostream & operator <<(std::ostream &os, std::vector<int>& intcode);
std::ostream & operator <<(std::ostream &os, const std::vector<int>& intcode);
std::ostream & operator <<(std::ostream &os, std::vector<std::string>& ss);
std::ostream & operator <<(std::ostream &os, const std::vector<std::string>& ss);

#endif
