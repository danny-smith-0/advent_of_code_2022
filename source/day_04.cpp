#include <advent_of_code.h>

// Ended up a touch more complex than necessary because I expected part 2 to need the expanded ranges, rather than just the bookends

ints_t_3d parse(strings_t input)
{
    ints_t_3d out;
    for (auto line : input)
    {
        strings_t range_strings = aoc::substrings_to_strings(line, ",");
        ints_t range1 = aoc::substrings_to_ints(range_strings.at(0), "-");
        ints_t range2 = aoc::substrings_to_ints(range_strings.at(1), "-");
        ints_t_2d range_pair;
        range_pair.push_back(aoc::matlab_colon(range1.at(0), range1.at(1)));
        range_pair.push_back(aoc::matlab_colon(range2.at(0), range2.at(1)));
        out.push_back(range_pair);
    }
    return out;
}

sll part1(ints_t_3d input)
{
    sll out = 0;
    for (auto range_pair : input)
    {
        ints_t r1 = range_pair.at(0);
        ints_t r2 = range_pair.at(1);
        if (r1.size() == r2.size() && r1.front() == r2.front())
            ++out;
        else if (r1.size() > r2.size() && r1.front() <= r2.front() && r1.back() >= r2.back())
            ++out;
        else if (r2.size() > r1.size() && r2.front() <= r1.front() && r2.back() >= r1.back())
            ++out;
    }
    return out;
}

sll part2(ints_t_3d input)
{
    sll out = 0;
    for (auto range_pair : input)
    {
        ints_t r1 = range_pair.at(0);
        ints_t r2 = range_pair.at(1);
        if ((r2.front() <= r1.front() && r1.front() <= r2.back()) || (r2.front() <= r1.back() && r1.back() <= r2.back()))
            ++out;
        else if ((r1.front() <= r2.front() && r2.front() <= r1.back()) || (r1.front() <= r2.back() && r2.back() <= r1.back()))
            ++out;
    }
    return out;
}

int main ()
{
    std::string day_string = "04";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");
    ints_t_3d test_data_parsed = parse(test_data);
    ints_t_3d real_data_parsed = parse(real_data);

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_data_parsed);
    sll expected_test_result_1 = 2;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_data_parsed);
        sll answer = 485;
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test_data_parsed);
    sll expected_test_result_2 = 4;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_data_parsed);
        sll answer = 857;
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
