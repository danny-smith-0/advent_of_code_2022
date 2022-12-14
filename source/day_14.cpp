#include <advent_of_code.h>

coords_t_vec parse(strings_t input)
{
    coords_t_vec out;
    for (auto line : input)
    {
        // for (auto my_char : line) {}
    }
    return out;
}

sll part1(coords_t_vec input)
{
    sll out = 0;
    return out;
}

sll part2(coords_t_vec input)
{
    sll out = 0;
    return out;
}

int main ()
{
    std::string day_string = "14";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");
    coords_t_vec test_data_parsed = parse(test_data);
    coords_t_vec real_data_parsed = parse(real_data);

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_data_parsed);
    sll expected_test_result_1 = -1;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_data_parsed);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test_data_parsed);
    sll expected_test_result_2 = -1;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_data_parsed);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
