#include <advent_of_code.h>

ints_t_2d parse(strings_t input)
{
    ints_t_2d out;// = strings_of_digits_to_ints(input);
    for (auto line : input)
    {
        // for (auto my_char : line) {}
    }
    return out;
}

sll part1(strings_t input)
{
    sll out = 0;
    return out;
}

sll part2(strings_t input)
{
    sll out = 0;
    return out;
}

int main ()
{
    std::string day_string = "01";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");
    ints_t_2d test_data_parsed = parse(test_data);
    ints_t_2d real_data_parsed = parse(real_data);

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_data);
    sll expected_test_result_1 = -1;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_data);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test_data);
    sll expected_test_result_2 = -1;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_data);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
