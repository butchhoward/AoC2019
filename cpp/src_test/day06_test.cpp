#include "day06_test.h"
#include "day06_lib.h"
#include "test_runner.h"


bool count_one_direct_orbit()
{
    day06lib::Universe universe;

    day06lib::add_to_universe(universe, "", "COM");
    day06lib::add_to_universe(universe, "COM", "FRED");

    return 1 == day06lib::count_orbits(universe);
}

bool count_two_direct_orbits()
{
    day06lib::Universe universe;

    day06lib::add_to_universe(universe, "", "COM");
    day06lib::add_to_universe(universe, "COM", "FRED");
    day06lib::add_to_universe(universe, "COM", "GEORGE");

    return 2 == day06lib::count_orbits(universe);
}

bool with_one_direct_and_one_indect_count_3_direct_orbits()
{
    day06lib::Universe universe;

    day06lib::add_to_universe(universe, "", "COM");
    day06lib::add_to_universe(universe, "COM", "LILLY");
    day06lib::add_to_universe(universe, "LILLY", "HARRY");

    return 3 == day06lib::count_orbits(universe);
}

bool check_sample_data()
{
    day06lib::Universe universe;

    day06lib::add_to_universe(universe, "COM","B");
    day06lib::add_to_universe(universe, "B","C");
    day06lib::add_to_universe(universe, "C","D");
    day06lib::add_to_universe(universe, "D","E");
    day06lib::add_to_universe(universe, "E","F");
    day06lib::add_to_universe(universe, "B","G");
    day06lib::add_to_universe(universe, "G","H");
    day06lib::add_to_universe(universe, "D","I");
    day06lib::add_to_universe(universe, "E","J");
    day06lib::add_to_universe(universe, "J","K");
    day06lib::add_to_universe(universe, "K","L");

    return 42 == day06lib::count_orbits(universe);
}

bool one_transfer_direct()
{
    day06lib::Universe universe;

    day06lib::add_to_universe(universe, "", "COM");
    day06lib::add_to_universe(universe, "COM", "FRED");

    return 1 == day06lib::minimum_transfers_between(universe, "FRED", "COM");
}

bool finds_item_when_within_subgraph()
{
    day06lib::Universe universe;

    day06lib::add_to_universe(universe, "", "COM");
    day06lib::add_to_universe(universe, "COM", "FRED");

    return true == day06lib::item_reachable_from(universe, "COM", "FRED");
}

bool does_not_find_item_when_not_within_subgraph()
{
    day06lib::Universe universe;

    //com->fred->george->ear
    //       
    day06lib::add_to_universe(universe, "", "COM");
    day06lib::add_to_universe(universe, "COM", "FRED");
    day06lib::add_to_universe(universe, "FRED", "GEORGE");
    day06lib::add_to_universe(universe, "GEORGE", "EAR");

    return false == day06lib::item_reachable_from(universe, "GEORGE", "FRED");
}


bool does_not_find_item_when_not_within_subgraph_deeper_and_branchy()
{
    day06lib::Universe universe;

    //      /->A
    //com->fred->george->ear
    //       \->B
    day06lib::add_to_universe(universe, "", "COM");
    day06lib::add_to_universe(universe, "COM", "FRED");
    day06lib::add_to_universe(universe, "FRED", "A");
    day06lib::add_to_universe(universe, "FRED", "B");
    day06lib::add_to_universe(universe, "FRED", "GEORGE");
    day06lib::add_to_universe(universe, "GEORGE", "EAR");

    return false == day06lib::item_reachable_from(universe, "GEORGE", "FRED");
}


bool finds_nearest_common_root()
{
    day06lib::Universe universe;

    //      /->A
    //com->fred->george->ear
    //       \->B
    day06lib::add_to_universe(universe, "", "COM");
    day06lib::add_to_universe(universe, "COM", "FRED");
    day06lib::add_to_universe(universe, "FRED", "A");
    day06lib::add_to_universe(universe, "FRED", "B");
    day06lib::add_to_universe(universe, "FRED", "GEORGE");
    day06lib::add_to_universe(universe, "GEORGE", "EAR");

    auto common = day06lib::find_common_orbiting_node(universe, "A", "B");
    return common.first == "FRED" && common.second == 0;
}


bool finds_nearest_common_root_sample_data()
{
    day06lib::Universe universe;


    //                           YOU
    //                          /
    //         G - H       J - K - L
    //        /           /
    // COM - B - C - D - E - F
    //                \
    //                 I - SAN

    day06lib::add_to_universe(universe, "COM","B");
    day06lib::add_to_universe(universe, "B","C");
    day06lib::add_to_universe(universe, "C","D");
    day06lib::add_to_universe(universe, "D","E");
    day06lib::add_to_universe(universe, "E","F");
    day06lib::add_to_universe(universe, "B","G");
    day06lib::add_to_universe(universe, "G","H");
    day06lib::add_to_universe(universe, "D","I");
    day06lib::add_to_universe(universe, "E","J");
    day06lib::add_to_universe(universe, "J","K");
    day06lib::add_to_universe(universe, "K","L");

    day06lib::add_to_universe(universe, "K","YOU");
    day06lib::add_to_universe(universe, "I","SAN");

    auto common = day06lib::find_common_orbiting_node(universe, "YOU", "SAN");
    return common.first == "D" && common.second == 3;
}

bool count_transfers_from_common_root_sample_data()
{
    day06lib::Universe universe;


    //                           YOU
    //                          /
    //         G - H       J - K - L
    //        /           /
    // COM - B - C - D - E - F
    //                \
    //                 I - SAN

    day06lib::add_to_universe(universe, "COM","B");
    day06lib::add_to_universe(universe, "B","C");
    day06lib::add_to_universe(universe, "C","D");
    day06lib::add_to_universe(universe, "D","E");
    day06lib::add_to_universe(universe, "E","F");
    day06lib::add_to_universe(universe, "B","G");
    day06lib::add_to_universe(universe, "G","H");
    day06lib::add_to_universe(universe, "D","I");
    day06lib::add_to_universe(universe, "E","J");
    day06lib::add_to_universe(universe, "J","K");
    day06lib::add_to_universe(universe, "K","L");

    day06lib::add_to_universe(universe, "K","YOU");
    day06lib::add_to_universe(universe, "I","SAN");

    return 1 == day06lib::count_transfers_outbound(universe, "D", "SAN");
    
}

bool mininum_transfers_sample_data()
{
    day06lib::Universe universe;

    day06lib::add_to_universe(universe, "COM","B");
    day06lib::add_to_universe(universe, "B","C");
    day06lib::add_to_universe(universe, "C","D");
    day06lib::add_to_universe(universe, "D","E");
    day06lib::add_to_universe(universe, "E","F");
    day06lib::add_to_universe(universe, "B","G");
    day06lib::add_to_universe(universe, "G","H");
    day06lib::add_to_universe(universe, "D","I");
    day06lib::add_to_universe(universe, "E","J");
    day06lib::add_to_universe(universe, "J","K");
    day06lib::add_to_universe(universe, "K","L");

    day06lib::add_to_universe(universe, "K","YOU");
    day06lib::add_to_universe(universe, "I","SAN");

    return 4 == day06lib::minimum_transfers_between(universe, "YOU", "SAN");
}



bool day06_test()
{
   test_runner::Tests tests = {
        {"count_one_direct_orbit", count_one_direct_orbit}
        ,{"count_two_direct_orbits", count_two_direct_orbits}
        ,{"with_one_direct_and_one_indect_count_3_direct_orbits", with_one_direct_and_one_indect_count_3_direct_orbits}
        ,{"check_sample_data", check_sample_data}
        ,{"one_transfer_direct", one_transfer_direct}
        ,{"finds_item_when_within_subgraph", finds_item_when_within_subgraph}
        ,{"does_not_find_item_when_not_within_subgraph",does_not_find_item_when_not_within_subgraph}
        ,{"does_not_find_item_when_not_within_subgraph_deeper_and_branchy",does_not_find_item_when_not_within_subgraph_deeper_and_branchy}
        ,{"finds_nearest_common_root", finds_nearest_common_root}
        ,{"finds_nearest_common_root_sample_data",finds_nearest_common_root_sample_data}
        ,{"mininum_transfers_sample_data", mininum_transfers_sample_data}
    };

    return test_runner::run_tests(tests);
}
