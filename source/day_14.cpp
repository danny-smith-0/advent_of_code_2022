#include <advent_of_code.h>

std::vector<coords_t_vec> parse(strings_t input)
{
    std::vector<coords_t_vec> out;
    for (auto line : input)
    {
        coords_t_vec rock_path;
        strings_t coord_strs = aoc::substrings_to_strings(line, " ");
        for (auto coord_str : coord_strs)
        {
            if (coord_str == "->")
                continue;
            ints_t coord_ints = aoc::substrings_to_ints(coord_str, ",");
            coords_t coord(coord_ints[0], coord_ints[1]);
            rock_path.push_back(coord);
        }
    out.push_back(rock_path);
    }
    return out;
}

sll part1(std::vector<coords_t_vec> input)
{
    sll out = 0;
    return out;
}

sll part2(std::vector<coords_t_vec> input)
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
    std::vector<coords_t_vec> test_data_parsed = parse(test_data);
    std::vector<coords_t_vec> real_data_parsed = parse(real_data);

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
