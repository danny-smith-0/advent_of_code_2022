#include <advent_of_code.h>

sll part1(ints_t_2d input)
{
    sll out = 0;

    size_t rows = input.size();
    size_t cols = input[0].size();

    // Make a corresponding matrix of bools with all false except the perimeter
    bools_t bool_row(cols, false);
    bool_row[0] = true;
    bool_row[cols - 1] = true;

    bools_t_2d bool_matrix(rows, bool_row);
    bool_matrix[0] = bools_t(cols, true);
    bool_matrix[rows - 1] = bools_t(cols, true);

    // rows
    for (size_t ii = 1; ii < cols - 1; ++ii)
    {
        // left to right
        int max_left = -1;
        for (size_t jj = 0; jj < cols - 1; ++jj)
        {
            int cell_value = input[ii][jj];
            if (cell_value > max_left)
            {
                bool_matrix[ii][jj] = true;
                max_left = cell_value;
            }
            if (max_left == 9)
                break;
        }

        // right to left
        // TODO For efficiency, stop going left at the furthest seen one from the left
        int max_right = -1;
        for (int jj = static_cast<int>(cols) - 1; jj >= 0; --jj)
        {
            int cell_value = input[ii][jj];
            if (cell_value > max_right)
            {
                bool_matrix[ii][jj] = true;
                max_right = cell_value;
            }
            if (max_right == 9)
                break;
        }
    }

    // columns
    for (size_t jj = 1; jj < cols - 1; ++jj)
    {
        // top to bottom
        int max_top = -1;
        for (size_t ii = 0; ii < rows - 1; ++ii)
        {
            int cell_value = input[ii][jj];
            if (cell_value > max_top)
            {
                bool_matrix[ii][jj] = true;
                max_top = cell_value;
            }
            if (max_top == 9)
                break;
        }

        // top to bottom
        int max_bottom = -1;
        for (int ii = static_cast<int>(rows) - 1; ii >= 0; --ii)
        {
            int cell_value = input[ii][jj];
            if (cell_value > max_bottom)
            {
                bool_matrix[ii][jj] = true;
                max_bottom = cell_value;
            }
            if (max_bottom == 9)
                break;
        }
    }
    out = static_cast<sll>(aoc::count_bools_t_2d(bool_matrix));
    return out;
}

sll part2(ints_t_2d input)
{
    sll max_viewing = 0;
    size_t rows = input.size();
    size_t cols = input[0].size();
    //skip outside edges because they all have a viewing distance of 0
    for (int ii = 1; ii < static_cast<int>(rows) - 1; ++ii)
    {
        for (int jj = 1; jj < static_cast<int>(cols) - 1; ++ jj)
        {
            sll my_height = input[ii][jj];
            sll n_view = 0; sll e_view = 0; sll s_view = 0; sll w_view = 0;
            // North
            for (int nn = ii - 1; nn >= 0; --nn)
            {
                int value = input[nn][jj];
                if (value < my_height) { ++n_view; }
                else { ++n_view; break; }
            }
            // East
            for (int ee = jj + 1; ee < rows; ++ee)
            {
                int value = input[ii][ee];
                if (value < my_height) { ++e_view; }
                else { ++e_view; break; }
            }
            // South
            for (int ss = ii + 1; ss < cols; ++ss)
            {
                int value = input[ss][jj];
                if (value < my_height) { ++s_view; }
                else { ++s_view; break; }
            }
            // West
            for (int ww = jj - 1; ww >= 0; --ww)
            {
                int value = input[ii][ww];
                if (value < my_height) { ++w_view; }
                else { ++w_view; break; }
            }

            sll current_viewing = n_view * e_view * s_view * w_view;
            max_viewing = std::max(max_viewing, current_viewing);
        }
    }
    return max_viewing;
}

int main ()
{
    std::string day_string = "08";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");
    ints_t_2d test_data_parsed = aoc::strings_of_digits_to_ints(test_data);
    ints_t_2d real_data_parsed = aoc::strings_of_digits_to_ints(real_data);

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_data_parsed);
    sll expected_test_result_1 = 21;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_data_parsed);
        sll solved = 1538;
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test_data_parsed);
    sll expected_test_result_2 = 8;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_data_parsed);
        sll solved = 496125;
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
