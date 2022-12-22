#include <advent_of_code.h>

std::string first_string;
bool set = true;

enum my_operations : int
{
    addition,
    subtraction,
    multiplication,
    division,
    whoops
};

char get_opr_char(int my_opr)
{
    switch(my_opr)
    {
        case my_operations::addition: return '+';
        case my_operations::subtraction: return '-';
        case my_operations::multiplication: return '*';
        case my_operations::division: return '/';
        default: return 'X';
    }
}

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

    std::string print()
    {
        std::stringstream ss;
        ss << name << ": ";

        if (num == -999)
            ss << m1 << " " << get_opr_char(my_opr) << " " << m2;
        else
            ss << num;
        return ss.str();
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
        {
            monkey.num = std::stoi(parsed_line[1]);
        }

        if (set)
        {
            first_string = monkey.name;
            set = false;
        }
        monkeys.insert(std::pair<std::string, Monkey>(monkey.name, monkey));
    }
    return monkeys;
}

sll part1(std::map<std::string, Monkey> monkeys)
{
    sll round = 1;
    while (monkeys["root"].num == -999)
    {
        ++round;
        // std::cout << "Round " << round << "\n";
        std::string pause_name = "drzm";
        for (auto& [name, monkey] : monkeys)
        {
            if (name == pause_name)
                sll a = 1;
            monkey.do_math(monkeys);
            // std::cout << monkey.print() << "\n";
        }
        // std::cout << "\n";
    }
    // sll out = monkeys["root"].num;
    sll out = monkeys[first_string].num;
    // first_string
    return out;
}

sll part2(std::map<std::string, Monkey> monkeys)
{
    sll out = 0;
    return out;
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
    sll results_test_2 = part2(test_data_parsed);
    sll expected_test_result_2 = -1;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_data_parsed);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
