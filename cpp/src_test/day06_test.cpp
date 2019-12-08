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


bool day06_test()
{
   test_runner::Tests tests = {
        {"count_one_direct_orbit", count_one_direct_orbit}
        ,{"count_two_direct_orbits", count_two_direct_orbits}
        ,{"with_one_direct_and_one_indect_count_3_direct_orbits", with_one_direct_and_one_indect_count_3_direct_orbits}
        ,{"check_sample_data", check_sample_data}
    };

    return test_runner::run_tests(tests);
}
