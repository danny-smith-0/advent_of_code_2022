#include <advent_of_code.h>

typedef std::pair<int, int> coordinates;

void step_head(coordinates& head, char direction)
{
    if (direction == 'L')
        --head.second;
    else if (direction == 'R')
        ++head.second;
    else if (direction == 'U')
        --head.first;
    else if (direction == 'D')
        ++head.first;
}

void step_tail(coordinates head, coordinates& tail)
{
    int vertical_offset = head.first - tail.first;
    int horizontal_offset = head.second - tail.second;
    if (vertical_offset < -1)
    {
        --tail.first;
        if(horizontal_offset < 0)
            --tail.second;
        else if (horizontal_offset > 0)
            ++tail.second;
    }
    else if (vertical_offset > 1)
    {
        ++tail.first;
        if (horizontal_offset < 0)
            --tail.second;
        else if (horizontal_offset > 0)
            ++tail.second;
    }
    else if (horizontal_offset < -1)
    {
        --tail.second;
        if (vertical_offset < 0)
            --tail.first;
        else if (vertical_offset > 0)
            ++tail.first;
    }
    else if (horizontal_offset > 1)
    {
        ++tail.second;
        if (vertical_offset < 0)
            --tail.first;
        else if (vertical_offset > 0)
            ++tail.first;
    }
}

std::string plot_coords(std::vector<coordinates> coords, bool snake = false)
{
    //get limits
    int min_row = 0; int max_row = 0; int min_col = 0; int max_col = 0;
    for (auto coord : coords)
    {
        min_row = std::min(min_row, coord.first);
        max_row = std::max(max_row, coord.first);
        min_col = std::min(min_col, coord.second);
        max_col = std::max(max_col, coord.second);
    }

    // Initialize the rectangle of .'s
    strings_t plot(max_row - min_row + 1, std::string(max_col - min_col + 1, '.'));

    // Plot either #'s or the part of the snake
    std::string snake_str = "H123456789$@!"; // Extra characters to show if it messes up
    for (size_t ii = 0; ii < coords.size(); ++ii)
    {
        plot[coords[ii].first - min_row][coords[ii].second - min_col] = snake ? snake_str[ii] : '#';
    }

    // Mark the starting point for reference
    plot[-min_row][-min_col] = 's';

    // Concatenate into a single string
    std::string plot_string;
    for (auto line : plot)
    {
        plot_string.append(line);
        plot_string.append("\n");
    }

    return plot_string;
}

sll part1(strings_t input)
{
    coordinates head(0, 0);
    coordinates tail(0, 0);
    std::vector<coordinates> past_tail_locations;

    for (auto line : input)
    {
        strings_t line_parsed_into_strings = aoc::substrings_to_strings(line, " ");
        char direction = *line_parsed_into_strings[0].c_str();
        int step_count = std::stoi(line_parsed_into_strings[1]);
        for (int ii = 0; ii < step_count; ++ii)
        {
            step_head(head, direction);
            step_tail(head, tail);
            // log the places the tail has been
            if (std::find(past_tail_locations.begin(), past_tail_locations.end(), tail) == past_tail_locations.end())
                past_tail_locations.push_back(tail);
        }
    }
    return static_cast<sll>(past_tail_locations.size());
}

sll part2(strings_t input)
{
    std::vector<coordinates> snake(10, coordinates(0,0));  // H123456789
    std::vector<coordinates> past_tail_locations;
    for (auto line : input)
    {
        strings_t line_parsed_into_strings = aoc::substrings_to_strings(line, " ");
        char direction = *line_parsed_into_strings[0].c_str();
        int step_count = std::stoi(line_parsed_into_strings[1]);
        for (int ii = 0; ii < step_count; ++ii)
        {
            step_head(snake[0], direction);
            for (size_t knot_index = 1; knot_index < snake.size(); ++knot_index )
                step_tail(snake[knot_index - 1], snake[knot_index]);

            // log the places the tail has been
            if (std::find(past_tail_locations.begin(), past_tail_locations.end(), snake.back()) == past_tail_locations.end())
                past_tail_locations.push_back(snake.back());
        }
    }
    return static_cast<sll>(past_tail_locations.size());
}

int main ()
{
    std::string day_string = "09";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t test_data2 = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input_2.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_data);
    sll expected_test_result_1 = 13;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_data);
        sll solved = 6018;  // 5896 is too low
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test_data2);
    sll expected_test_result_2 = 36;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_data);
        sll solved = 2619;
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
