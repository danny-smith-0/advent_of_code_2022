#include <advent_of_code.h>

int score_letter(char input)
{
    int score;
    if (input > 'Z')
        // lowercase
        score = input - 'a' + 1;
    else
        //uppercase
        score = input - 'A' + 27;
    return score;
}

int part1(strings_t input)
{
    int total_score = 0;
    for (auto rucksack : input)
    {
        size_t compartment_size = rucksack.size() / 2;
        std::string c1(rucksack.begin(), rucksack.begin() + compartment_size);
        std::string c2(rucksack.begin() + compartment_size, rucksack.end());
        aoc::unique_sorted_string(c1);
        aoc::unique_sorted_string(c2);
        char same_item = '0';
        for (auto item1 : c1)
        {
            for (auto item2 : c2)
            {
                if (item1 == item2)
                {
                    same_item = item1;
                    break;
                }

            }
            if (same_item != '0')
                break;
        }
        total_score += score_letter(same_item);
    }
    return total_score;
}

int part2(strings_t input)
{
    int total_score = 0;
    size_t groups_of_three = input.size() / 3;
    for (int ii = 1; ii <= groups_of_three; ++ii)
    {
        std::string elf1 = input.at(3 * ii - 3);
        std::string elf2 = input.at(3 * ii - 2);
        std::string elf3 = input.at(3 * ii - 1);
        aoc::unique_sorted_string(elf1);
        aoc::unique_sorted_string(elf2);
        aoc::unique_sorted_string(elf3);
        char same_item = '0';
        for (auto item1 : elf1)
        {
            for (auto item2 : elf2)
            {
                if (item1 == item2)
                {
                    for (auto item3 : elf3)
                    {
                        if (item1 == item3)
                        {
                            same_item = item1;
                            break;
                        }
                    }
                }
                if (same_item != '0')
                    break;
            }
            if (same_item != '0')
                break;
        }
        total_score += score_letter(same_item);
    }
    return total_score;
}

int main ()
{
    std::string day_string = "03";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");

    std::cout << "\nPart 1\n\n";
    int results_test_1 = part1(test_data);
    int expected_test_result_1 = 157;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        int results_real_1 = part1(real_data);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    int results_test_2 = part2(test_data);
    int expected_test_result_2 = 70;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        int results_real_2 = part2(real_data);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
