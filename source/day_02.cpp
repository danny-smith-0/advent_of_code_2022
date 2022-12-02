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

enum output : int
{
    win = 6,
    lose = 0,
    draw = 3
};

enum input : int
{
    rock = 1,
    paper = 2,
    scissors =3

};

output rock_paper_scissors(int first, int second)
{
    output first_output = output::draw;

    switch (first)
    {
        case input::rock:
            switch (second)
            {
                case input::rock: first_output = output::draw; break;
                case input::paper: first_output = output::lose; break;
                case input::scissors: first_output = output::win; break;
                default: break;
            }
            break;
        case input::paper:
            switch (second)
            {
                case input::rock: first_output = output::win; break;
                case input::paper: first_output = output::draw; break;
                case input::scissors: first_output = output::lose; break;
                default: break;
            }
            break;
        case input::scissors:
            switch (second)
            {
                case input::rock: first_output = output::lose; break;
                case input::paper: first_output = output::win; break;
                case input::scissors: first_output = output::draw; break;
                default: break;
            }
            break;
        default:
            break;
    }
    return first_output;
}

input reverse_rock_paper_scissors(int first, int desired_result_for_2nd)
{
    input what_to_throw = input::rock;

    switch (first)
    {
        case input::rock:
            switch (desired_result_for_2nd)
            {
                case output::win: what_to_throw = input::paper; break;
                case output::lose: what_to_throw = input::scissors; break;
                case output::draw: what_to_throw = input::rock; break;
                default: break;
            }
            break;
        case input::paper:
            switch (desired_result_for_2nd)
            {
                case output::win: what_to_throw = input::scissors; break;
                case output::lose: what_to_throw = input::rock; break;
                case output::draw: what_to_throw = input::paper; break;
                default: break;
            }
            break;
        case input::scissors:
            switch (desired_result_for_2nd)
            {
                case output::win: what_to_throw = input::rock; break;
                case output::lose: what_to_throw = input::paper; break;
                case output::draw: what_to_throw = input::scissors; break;
                default: break;
            }
            break;
        default:
            break;
    }
    return what_to_throw;
}

input parse_throw_part1(char letter)
{
    if (letter == 'A' || letter == 'X') return input::rock;
    else if (letter == 'B' || letter == 'Y') return input::paper;
    else if (letter == 'C' || letter == 'Z') return input::scissors;
    else
    {
        std::cout << "whoops " << letter;
        return input::rock;
    }
}

output parse_desired_result_part2(char letter)
{
    if (letter == 'X') return output::lose;
    else if (letter == 'Y') return output::draw;
    else if (letter == 'Z') return output::win;
    else
    {
        std::cout << "whoops " << letter;
        return output::draw;
    }
}

sll part1(strings_t input)
{
    sll out = 0;
    for (auto line : input)
    {
        int elf_throw = parse_throw_part1(line[0]);
        int my_throw = parse_throw_part1(line[2]);
        int result = rock_paper_scissors(my_throw, elf_throw);

        out += my_throw + result;
    }
    return out;
}

sll part2(strings_t input)
{
    sll out = 0;
    for (auto line : input)
    {
        int elf_throw = parse_throw_part1(line[0]);
        int my_result = parse_desired_result_part2(line[2]);
        int my_throw = reverse_rock_paper_scissors(elf_throw, my_result);

        out += my_throw + my_result;
    }
    return out;
}

int main ()
{
    std::string day_string = "02";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");
    ints_t_2d test      = parse(get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt"));
    ints_t_2d real      = parse(get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt"));

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_data);
    sll expected_test_result_1 = 15;
    if (results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_data);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test_data);
    sll expected_test_result_2 = 12;
    if (results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_data);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
