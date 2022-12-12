#include <advent_of_code.h>

int part1(strings_t input)
{
    int out = 0;
    return out;
}

int part2(strings_t input)
{
    int out = 0;
    return out;
}

int main ()
{
    std::string day_string = "12";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");

    std::cout << "\nPart 1\n\n";
    int results_test_1 = part1(test_data);
    int expected_test_result_1 = 31;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        int results_real_1 = part1(real_data);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    int results_test_2 = part2(test_data);
    int expected_test_result_2 = -1;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        int results_real_2 = part2(real_data);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
