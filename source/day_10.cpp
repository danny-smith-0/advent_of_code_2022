#include <advent_of_code.h>

std::string bump_cycle_and_do_the_things(sll reg_val, sll& cycle_num, std::vector<sll>& signal_strength, std::string& screen, bool print_part2_steps = false)
{
    ++cycle_num;
    if (cycle_num > 0 && (cycle_num - 20) % 40 == 0)
    {
        sll value = cycle_num * reg_val;
        // std::cout << cycle_num << " * " << reg_val << " = " << value << "\n";
        signal_strength.push_back(value);
    }

    sll draw_position = (cycle_num - 1) % 40;
    if (print_part2_steps) { std::cout << "During cycle " << cycle_num << ": CRT draws pixel in position " << draw_position << "\n"; }
    std::string str;
    if (reg_val == draw_position - 1 || reg_val == draw_position || reg_val == draw_position + 1)
        str = "#";
    else
        str = ".";

    if (cycle_num > 1 && (cycle_num % 40 == 0))
        str.append("\n");

    screen.append(str);
    if (print_part2_steps) { std::cout << "Current CRT row:\n" << screen << "\n"; }
    return str;
}

sll day10(strings_t input)
{
    sll reg_val = 1;
    std::vector<sll> signal_strength;

    sll cycle_num = 0;

    std::string screen;
    bool print_part2_steps = false;
    for (sll ii = 0; ii < static_cast<sll>(input.size()); ++ii)
    {
        if (input[ii] == "noop")
        {
            if (print_part2_steps) { std::cout << "Start cycle  " << cycle_num + 1 << ": begin executing noop\n"; }
            bump_cycle_and_do_the_things(reg_val, cycle_num, signal_strength, screen);
            if (print_part2_steps) { std::cout << "End of cycle " << cycle_num << ": finish executing noop\n\n"; }
        }
        else
        {
            if (print_part2_steps) { std::cout << "Start cycle  " << cycle_num + 1 << ": begin executing " << input[ii] << "\n"; }
            bump_cycle_and_do_the_things(reg_val, cycle_num, signal_strength, screen);
            if (print_part2_steps) { std::cout << std::endl; }
            bump_cycle_and_do_the_things(reg_val, cycle_num, signal_strength, screen);

            strings_t line_parsed = aoc::substrings_to_strings(input[ii], " ");
            reg_val += std::stoi(line_parsed[1]);
            if (print_part2_steps) { std::cout << "End of cycle " << cycle_num << ": finish executing " << input[ii] << " (Register X is now " << reg_val << ")\n\n"; }
        }
    }

    sll total_signal_strength = 0;
    for (auto addend : signal_strength)
        total_signal_strength += addend;

    std::cout << screen << "\n";

    return total_signal_strength;
}

int main ()
{
    std::string day_string = "10";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");

    sll results_test_1 = day10(test_data);
    sll expected_test_result_1 = 13140;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = day10(real_data);
        sll solved = 14820;
        std::cout << "Part 1 result is " << results_real_1 << std::endl;
    }

    return 0;
}

/*
Real:
###..####.####.#..#.####.####.#..#..##..
#..#....#.#....#.#..#....#....#..#.#..#.
#..#...#..###..##...###..###..####.#..#.
###...#...#....#.#..#....#....#..#.####.
#.#..#....#....#.#..#....#....#..#.#..#.
#..#.####.####.#..#.####.#....#..#.#..#.

Test:
##..##..##..##..##..##..##..##..##..##..
###...###...###...###...###...###...###.
####....####....####....####....####....
#####.....#####.....#####.....#####.....
######......######......######......####
#######.......#######.......#######.....
*/
