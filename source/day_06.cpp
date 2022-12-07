#include <advent_of_code.h>

int day06(std::string signal, int len_unique)
{
    int out = 0;
    for (int ii = len_unique; ii < static_cast<int>(signal.size()); ++ii)
    {
        std::string substr(signal.begin() + ii - len_unique, signal.begin() + ii);
        aoc::unique_sorted_string(substr);
        // If the substring isn't shorter, each char is unique
        if (substr.length() == len_unique)
        {
            out = ii;
            break;
        }
    }
    return out;
}

int part1(std::string signal)
{
    return day06(signal, 4);
}

int part2(std::string signal)
{
    return day06(signal, 14);
}

int main ()
{
    std::string day_string = "06";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");

    std::cout << "\nPart 1\n\n";
    int results_test_1a = part1(test_data[0]); int expected_test_result_1a = 7;
    int results_test_1b = part1(test_data[1]); int expected_test_result_1b = 5;
    int results_test_1c = part1(test_data[2]); int expected_test_result_1c = 6;
    int results_test_1d = part1(test_data[3]); int expected_test_result_1d = 10;
    int results_test_1e = part1(test_data[4]); int expected_test_result_1e = 11;

    bool test_passed = aoc::results(results_test_1a, expected_test_result_1a)
        && aoc::results(results_test_1b, expected_test_result_1b)
        && aoc::results(results_test_1c, expected_test_result_1c)
        && aoc::results(results_test_1d, expected_test_result_1d)
        && aoc::results(results_test_1e, expected_test_result_1e);

    if (test_passed)
    {
        int results_real_1 = part1(real_data[0]);
        int solved = 1702;
        std::cout << "Real result is " << results_real_1 << (results_real_1 == solved ? ". Gold star!" : "") << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    int results_test_2a = part2(test_data[0]); int expected_test_result_2a = 19;
    int results_test_2b = part2(test_data[1]); int expected_test_result_2b = 23;
    int results_test_2c = part2(test_data[2]); int expected_test_result_2c = 23;
    int results_test_2d = part2(test_data[3]); int expected_test_result_2d = 29;
    int results_test_2e = part2(test_data[4]); int expected_test_result_2e = 26;

    bool test_passed_2 = aoc::results(results_test_2a, expected_test_result_2a)
        && aoc::results(results_test_2b, expected_test_result_2b)
        && aoc::results(results_test_2c, expected_test_result_2c)
        && aoc::results(results_test_2d, expected_test_result_2d)
        && aoc::results(results_test_2e, expected_test_result_2e);

    if (test_passed_2)
    {
        int results_real_2 = part2(real_data[0]);
        int solved = 3559;
        std::cout << "Real result is " << results_real_2 << (results_real_2 == solved ? ". Gold star!" : "") << "\n\nFinished" << std::endl;
    }

    return 0;
}
