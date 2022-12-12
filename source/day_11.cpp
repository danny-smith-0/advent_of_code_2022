#include <advent_of_code.h>
#include <functional>

struct Monkey
{
    ints_t items;
    std::function<int(int)> func;
    int test_divisor = -1;
    int monkey_index_if_true = -1;
    int monkey_index_if_false = -1;
    int total_inspections = 0;

    std::vector<std::pair<int, int>> take_a_turn(bool part1 = true)
    {
        std::vector<std::pair<int, int>> result;
        while (!items.empty())
        {
            result.push_back(throw_item(part1));
            ++total_inspections;
        }
        return result;
    }

    std::pair<int, int> throw_item(bool part1 = true)
    {
        int item = items[0];
        items.erase(items.begin());
        item = func(item);
        if (part1 == true)
            item = item / 3;
        if (item % test_divisor == 0)
            return std::pair<int, int>(monkey_index_if_true, item);
        else
            return std::pair<int, int>(monkey_index_if_false, item);
    }

    Monkey(ints_t intial_items, strings_t operation, int test_divisor_in, int true_monkey, int false_monkey)
    : items(intial_items), test_divisor(test_divisor_in), monkey_index_if_true(true_monkey), monkey_index_if_false(false_monkey)
    {
        if (operation[1] == "*")
        {
            if(operation[2] == "old")
                func = [](int old){ return old * old; };
            else
            {
                int nn = std::stoi(operation[2]);
                func = [nn](int old){return old * nn; };
            }
        }
        else if (operation[1] == "+")
        {
            int nn = std::stoi(operation[2]);
            func = [nn](int old){return old + nn; };
        }
        else
            std::cout << "whoops\n";
    }

};

std::vector<Monkey> parse(strings_t input)
{
    std::vector<Monkey> monkeys;
    for (int monkey_start_line = 0; monkey_start_line < static_cast<int>(input.size()); monkey_start_line += 7)
    {
        strings_t parsed_line;
        parsed_line = aoc::substrings_to_strings(input[monkey_start_line + 1], ":");
        ints_t starting_items = aoc::substrings_to_ints(parsed_line[1], ",");

        parsed_line = aoc::substrings_to_strings(input[monkey_start_line + 2], "=");
        strings_t operation = aoc::substrings_to_strings(parsed_line[1], " ");

        parsed_line = aoc::substrings_to_strings(input[monkey_start_line + 3], "y");  // The last letter in "by"
        int test_divisor = std::stoi(parsed_line[1]);

        parsed_line = aoc::substrings_to_strings(input[monkey_start_line + 4], "y");  // The last letter in "monkey"
        int true_monkey = std::stoi(parsed_line[1]);

        parsed_line = aoc::substrings_to_strings(input[monkey_start_line + 5], "y");  // The last letter in "monkey"
        int false_monkey = std::stoi(parsed_line[1]);

        monkeys.push_back(Monkey(starting_items, operation, test_divisor, true_monkey, false_monkey));
    }
    return monkeys;
}

int part1(std::vector<Monkey> monkeys)
{
    for (int ii = 0; ii < 20; ++ii)
    {
        for (auto& monkey : monkeys)
        {
            std::vector<std::pair<int, int>> items_thrown = monkey.take_a_turn();
            for (auto this_throw : items_thrown)
            {
                monkeys[this_throw.first].items.push_back(this_throw.second);
            }
        }
        int round = ii + 1;
        if (round == 1 || round == 20)
        {
            std::cout << "round " << round << "\n";
            for (auto& monkey : monkeys)
            {
                std::cout << "Monkey " << round << ": ";
                for (auto item : monkey.items)
                    std::cout << item << ",";
                std::cout << " (items inspected: " << monkey.total_inspections << ")\n";
            }
            std::cout << "\n";
        }
    }
    int out = 0;
    return out;
}

int part2(std::vector<Monkey> monkeys)
{
    for (int ii = 0; ii < 10000; ++ii)
    {
        for (auto& monkey : monkeys)
        {
            bool part1 = false;
            std::vector<std::pair<int, int>> items_thrown = monkey.take_a_turn(part1);
            for (auto this_throw : items_thrown)
            {
                monkeys[this_throw.first].items.push_back(this_throw.second);
            }
        }
        int round = ii + 1;
        if (round == 1 || round == 20 || round % 1000 == 0)
        {
            std::cout << "round " << round << "\n";
            for (auto& monkey : monkeys)
            {
                std::cout << "Monkey " << round << ": items inspected: " << monkey.total_inspections << "\n";
            }
            std::cout << "\n";
        }
    }
    int out = 0;
    return out;
}

int main ()
{
    std::string day_string = "11";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");
    std::vector<Monkey> test_data_parsed = parse(test_data);
    std::vector<Monkey> real_data_parsed = parse(real_data);

    std::cout << "\nPart 1\n\n";
    part1(test_data_parsed);
    int results_test_1 = 10605;
    // int results_real_1 = part1(real_data_parsed);
    int solved = 55216;

    std::cout << "\nPart 2\n\n";
    int results_test_2 = part2(test_data_parsed);
    int expected_test_result_2 = -1;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        int results_real_2 = part2(real_data_parsed);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}