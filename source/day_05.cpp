#include <advent_of_code.h>
#include <stack>

void visualize(std::vector<std::stack<char>> stacks);

std::vector<std::stack<char>> parse1(strings_t inputs)
{
    size_t empty_line_index = 0;
    for (size_t ii = 0; ii < inputs.size(); ++ii)
    {
        if (inputs[ii] == "")
            empty_line_index = ii;
            break;
    }

    //Initialize the correct number of empty stacks
    auto bottom_row = inputs[empty_line_index - 2];
    double chars_per_column = 4;  // e.g. "[A] "
    // round up because trailing char(s) might be missing
    int num_stacks = static_cast<int>(std::ceil(static_cast<double>(bottom_row.size()) / chars_per_column));

    std::vector<std::stack<char>> out;
    for (int jj = 0; jj < num_stacks; ++jj)
        out.push_back(std::stack<char>());

    // Populate the stacks
    for (int ii = empty_line_index - 2; ii >= 0 ; --ii)
    {
        for (int jj = 0; jj < num_stacks; ++jj)
        {
            size_t char_index = static_cast<size_t>(1 + chars_per_column * jj);
            if (char_index > inputs[ii].size() - 1)
                break;

            char my_char = inputs[ii][char_index];
            if (my_char != ' ')
                out[jj].push(my_char);
        }
    }
    return out;
}

ints_t_2d parse2(strings_t input)
{
    ints_t_2d instructions;
    bool found_the_empty_line = false;
    for (auto line : input)
    {
        if (!found_the_empty_line)
        {
            if (line == "")
                found_the_empty_line = true;
            continue;
        }
        ints_t instruction;
        size_t space_index;
        find_space_in_string(line, &space_index);
        line = string_after_space(line, space_index); // remove "move ". Remaining "ZZ from N to M"
        find_space_in_string(line, &space_index);
        int n_move = std::stoi(string_before_space(line, space_index));
        line = string_after_space(line, space_index); // remaining: "from N to M"
        find_space_in_string(line, &space_index);
        line = string_after_space(line, space_index); // remaining: "N to M"
        find_space_in_string(line, &space_index);
        int start = std::stoi(string_before_space(line, space_index));
        line = string_after_space(line, space_index); // remaining: "to M"
        int end = std::stoi(string_after_space(line, space_index));
        instruction.push_back(n_move);
        instruction.push_back(start);
        instruction.push_back(end);
        instructions.push_back(instruction);
    }
    return instructions;
}

std::string part1(std::vector<std::stack<char>> stacks, ints_t_2d all_instructions)
{
    std::string out;
    for (ints_t instruc : all_instructions)
    {
        int n_move = instruc[0];
        int start_index = instruc[1] - 1;
        int end_index = instruc[2] - 1;

        for (int ii = 0; ii < n_move; ++ii)
        {
            char move_char = stacks[start_index].top();
            stacks[end_index].push(move_char);
            stacks[start_index].pop();
        }
    }
    for (auto stack : stacks)
        out.push_back(stack.top());

    return out;
}

std::string part2(std::vector<std::stack<char>> stacks, ints_t_2d all_instructions)
{
    std::string out;
    for (ints_t instruc : all_instructions)
    {
        int n_move = instruc[0];
        int start_index = instruc[1] - 1;
        int end_index = instruc[2] - 1;

        std::stack<char> transfer_stack;
        for (int ii = 0; ii < n_move; ++ii)
        {
            transfer_stack.push(stacks[start_index].top());
            stacks[start_index].pop();
        }

        for (int ii = 0; ii < n_move; ++ii)
        {
            stacks[end_index].push(transfer_stack.top());
            transfer_stack.pop();
        }

    }

    // Get the tops of the stacks
    for (auto stack : stacks)
        out.push_back(stack.top());

    return out;
}

int main ()
{
    std::string day_string = "05";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");

    std::vector<std::stack<char>> test_stacks = parse1(test_data);
    std::vector<std::stack<char>> real_stacks = parse1(real_data);
    ints_t_2d test_instructions = parse2(test_data);
    ints_t_2d real_instructions = parse2(real_data);

    std::cout << "\nPart 1\n\n";
    std::string results_test_1 = part1(test_stacks, test_instructions);
    std::string expected_test_result_1 = "CMZ";
    if (results(results_test_1, expected_test_result_1))
    {
        std::string results_real_1 = part1(real_stacks, real_instructions);
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    std::string results_test_2 = part2(test_stacks, test_instructions);
    std::string expected_test_result_2 = "MCD";
    if (results(results_test_2, expected_test_result_2))
    {
        std::string results_real_2 = part2(real_stacks, real_instructions);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}

void visualize(std::vector<std::stack<char>> stacks)
{
    size_t tallest_stack_height = 0;
    for (auto stack : stacks)
        tallest_stack_height = std::max(tallest_stack_height, stack.size());

    std::stringstream ss;
    while (tallest_stack_height > 0)
    {
        for (auto& stack : stacks)
        {
            if (stack.size() == tallest_stack_height)
            {
                ss << "[" << stack.top() << "] ";
                stack.pop();
            }
            else
                ss << "    ";
        }
        ss << "\n";
        --tallest_stack_height;
    }

    // Label the columns
    for (int ii = 1; ii <= stacks.size(); ++ii)
        ss << " " << ii << "  ";
    ss << "\n";

    std::cout << ss.str();
}
