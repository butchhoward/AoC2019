#ifndef DAY06_LIB_H
#define DAY06_LIB_H

#include "stream_helpers.h"

#include <string>
#include <vector>
#include <map>

namespace day06lib {

typedef struct OrbitItem
{
    std::string name;
    std::string orbiting;
    std::vector<std::string> orbitals;
} OrbitItem;

typedef std::map<std::string, day06lib::OrbitItem> Universe;

std::ostream & operator <<(std::ostream &os, day06lib::OrbitItem& orbititem);
std::ostream & operator <<(std::ostream &os, day06lib::Universe& universe);

void add_to_universe(day06lib::Universe &universe, std::string orbited, std::string orbiter);
day06lib::Universe read_file(const std::string& filename);

int count_orbits(const day06lib::Universe& universe);
int minimum_transfers_between(const day06lib::Universe& universe, const std::string& source, const std::string& destination);
bool item_reachable_from(const day06lib::Universe& universe, const std::string& com, const std::string& destination);

std::pair<std::string, int> find_common_orbiting_node(const day06lib::Universe& universe, const std::string& source, const std::string& destination);
int count_transfers_outbound(const day06lib::Universe& universe, const std::string& source, const std::string& destination);

}

#endif
