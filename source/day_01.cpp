#include <advent_of_code.h>

ints_t_2d parse(strings_t input)
{
    ints_t_2d out;
    ints_t elf;
    for (auto line : input)
    {
        if (line.empty())
        {
            out.push_back(elf);
            elf.clear();
        }
        else
        {
            int calories = std::stoi(line);
            elf.push_back(calories);
        }
    }
    if (!elf.empty())
        out.push_back(elf);

    return out;
}

sll part1(ints_t_2d input)
{
    sll max_calories_by_an_elf = 0;
    for (auto elf : input)
    {
        sll elfs_calories = 0;
        for (auto food : elf)
            elfs_calories += food;
        max_calories_by_an_elf = std::max(max_calories_by_an_elf, elfs_calories);
    }
    return max_calories_by_an_elf;
}

bool bigger_to_smaller(int i,int j) { return i > j; }

ull part2(ints_t_2d input)
{
    ints_t elf_calories;
    for (auto elf : input)
    {
        int this_elfs_calories = 0;
        for (auto food : elf)
            this_elfs_calories += food;
        elf_calories.push_back(this_elfs_calories);
    }
    std::sort(elf_calories.begin(), elf_calories.end(), bigger_to_smaller);

    ull answer = elf_calories.at(0) + elf_calories.at(1) + elf_calories.at(2);
    return answer;
}

int main ()
{
    std::string day_string = "01";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");
    ints_t_2d test      = parse(test_data);
    ints_t_2d real      = parse(real_data);

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test);
    sll expected_test_result_1 = 24000;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test);
    sll expected_test_result_2 = 45000;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
