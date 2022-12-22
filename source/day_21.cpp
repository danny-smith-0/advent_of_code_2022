#include <advent_of_code.h>
#include <limits>
#include <chrono>

// Using time point and system_clock
std::chrono::time_point<std::chrono::system_clock> start, end;

enum my_operations : int
{
    addition,
    subtraction,
    multiplication,
    division,
    whoops
};

struct Monkey
{
    std::string name;
    sll num = -999;
    std::string m1;
    std::string m2;
    my_operations my_opr;
    void do_math(std::map<std::string, Monkey>& monkeys)
    {
        if (num != -999)
            return;
        sll num1 = monkeys[m1].num;
        sll num2 = monkeys[m2].num;
        if (num1 == -999 || num2 == -999)
            return;
        switch (my_opr)
        {
            case my_operations::addition:       num = num1 + num2; break;
            case my_operations::subtraction:    num = num1 - num2; break;
            case my_operations::multiplication: num = num1 * num2; break;
            case my_operations::division:       num = num1 / num2; break;
            default: break;
        }
    }
};

std::map<std::string, Monkey> parse(strings_t input)
{
    std::map<std::string, Monkey> monkeys;
    for (auto line : input)
    {
        strings_t parsed_line = aoc::substrings_to_strings(line, ":");
        parsed_line[1] = std::string(parsed_line[1].begin() + 1, parsed_line[1].end());
        Monkey monkey;
        monkey.name = parsed_line[0];
        if (parsed_line[1].size() > 8)
        {
            strings_t operation_line = aoc::substrings_to_strings(parsed_line[1], " ");
            monkey.m1 = operation_line[0];
            monkey.m2 = operation_line[2];
            switch(*operation_line[1].c_str())
            {
                case '+': monkey.my_opr = my_operations::addition; break;
                case '-': monkey.my_opr = my_operations::subtraction; break;
                case '*': monkey.my_opr = my_operations::multiplication; break;
                case '/': monkey.my_opr = my_operations::division; break;
                default: monkey.my_opr = my_operations::whoops; break;
            }
        }
        else
            monkey.num = std::stoi(parsed_line[1]);

        monkeys.insert(std::pair<std::string, Monkey>(monkey.name, monkey));
    }
    return monkeys;
}

sll part1(std::map<std::string, Monkey> monkeys)
{
    while (monkeys["root"].num == -999)
    {
        for (auto& [name, monkey] : monkeys)
            monkey.do_math(monkeys);
    }
    sll out = monkeys["root"].num;
    return out;
}

sll part2(std::map<std::string, Monkey> orig_monkeys)
{
    double last_elapsed_seconds_print = 0;

    sll min_val = 0; //LLONG_MIN;
    sll max_val = LLONG_MAX;

    std::cout << "searching from " << min_val << " to " << max_val << "\n";
    for (sll ii = min_val; ii < max_val; ++ii)
    {
        // std::cout << ii << "\n";
        std::chrono::time_point<std::chrono::system_clock> start_itr = std::chrono::system_clock::now();

        if (ii == -999)
            continue;  // It really better not be this, or it screws stuff up

        std::map<std::string, Monkey> monkeys = orig_monkeys;
        monkeys["humn"].num = ii;
        while (monkeys["root"].num == -999)
        {
            end = std::chrono::system_clock::now();
            std::chrono::duration<double> elapsed_seconds = end - start_itr;
            if (elapsed_seconds.count() > 4)
            {
                std::cout << "breaking on " << ii << ", ";
                break;
            }

            for (auto& [name, monkey] : monkeys)
            {
                if (name == "root")
                {
                    sll num1 = monkeys[monkeys["root"].m1].num;
                    sll num2 = monkeys[monkeys["root"].m2].num;
                    if (num1 != -999 && num2 != -999)
                    {
                        if (num1 == num2)
                        {
                            monkeys["root"].num = ii;
                            end = std::chrono::system_clock::now();
                            std::chrono::duration<double> elapsed_seconds = end - start;
                            std::cout << "\nAnswer: " << ii << "\nAnswer: " << ii << "\ntotal time at end of part2 call (test or real): " << elapsed_seconds.count() / 60 << " minutes\n\n";
                            return ii;
                        }
                        else
                        {
                            monkeys["root"].num = 5;
                            break;
                        }
                    }

                }
                else
                    monkey.do_math(monkeys);
            }
        }

        end = std::chrono::system_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        if (elapsed_seconds.count() > last_elapsed_seconds_print)
        {
            std::stringstream ss;
            ss << "\n" << ii << ": " << elapsed_seconds.count() / 60. << " min, ";
            last_elapsed_seconds_print += 5 * 60;
            std::cout << ss.str();
        }
    }
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "\n\ntotal time at end of part2 call (test or real): " << elapsed_seconds.count() / 60 << " minutes\n\n";

    std::cout << "\nWhoops! You didn't find a result!\n\n";
    return -111;
}

int main ()
{
    std::string day_string = "21";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");
    std::map<std::string, Monkey> test_data_parsed = parse(test_data);
    std::map<std::string, Monkey> real_data_parsed = parse(real_data);

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_data_parsed);
    sll expected_test_result_1 = 152;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_data_parsed);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    start = std::chrono::system_clock::now();
    // sll results_test_2 = part2(test_data_parsed);
    // sll expected_test_result_2 = 301;
    // if (aoc::results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_data_parsed);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
