#include <advent_of_code.h>

struct directory
{
    std::string name;
    directory* parent;
    std::map<std::string, directory*> subdirs;
    std::map<std::string, ull> files;

    ull local_file_size()
    {
        ull total = 0;
        for (auto [name, size] : files)
            total += size;
        return total;
    }
    ull total_file_size()
    {
        ull total = local_file_size();
        for (auto [name, subdir] : subdirs)
            total += subdir->total_file_size();
        return total;
    }
};

std::map<std::string, directory*> parse(strings_t input)
{
    directory* current = new directory();

    current->name = aoc::substrings_to_strings(input[0], " ")[2];
    input.erase(input.begin());

    std::map<std::string, directory*> all_dirs;
    all_dirs.insert(std::pair<std::string, directory*>(current->name, current));

    bool populating = false;
    ints_t_2d out;// = strings_of_digits_to_ints(input);
    for (auto line : input)
    {
        strings_t parsed_line = aoc::substrings_to_strings(line, " ");
        if (populating)
        {
            if (parsed_line[0] == "$")
                populating = false;

            else if (parsed_line[0] == "dir")
            {
                directory* dir = new directory();
                dir->name = parsed_line[1];
                dir->parent = current;
                all_dirs.insert(std::pair<std::string, directory*>(dir->name, dir));
                current->subdirs.insert(std::pair<std::string, directory*>(dir->name, dir));
            }
            else  // parsed_line[0] is a number
                current->files.insert(std::pair<std::string, ull>(parsed_line[1], std::stoi(parsed_line[0])));
        }
        if (!populating)
        {
            if (parsed_line[1] == "ls")
                populating = true;
            else  // parsed_line[1] is c
                if (parsed_line[2] == "..")
                {
                    if (current->parent == nullptr)
                        std::cout << "ERROR: parent == nullptr\n";
                    current = current->parent;
                }
                else  // parsed_line[2] == a directory name
                {
                    current = current->subdirs[parsed_line[2]];
                }
        }
    }
    return all_dirs;
}

sll part1(std::map<std::string, directory*> all_dirs)
{
    sll out = 0;
    for (auto [name, dir] : all_dirs)
    {
        ull size = dir->total_file_size();
        if (size <= 100000)
        {
            std::stringstream ss;
            ss << out << " + " << size << " = ";
            out += static_cast<sll>(size);
            ss << out << std::endl;
            std::cout << ss.str();
            int a = 1;
        }
    }
    return out;
}

sll part2(std::map<std::string, directory*> all_dirs)
{
    sll out = 0;
    return out;
}

int main ()
{
    std::string day_string = "07";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");
    std::map<std::string, directory*> test_dirs = parse(test_data);
    std::map<std::string, directory*> real_dirs = parse(real_data);

    std::cout << "\nPart 1\n\n";
    sll results_test_1 = part1(test_dirs);
    sll expected_test_result_1 = 95437;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        sll results_real_1 = part1(real_dirs);
        sll too_low = 1210045;
        std::cout << too_low << " is too low\n";
        if (results_real_1 <= too_low)
            std::cout << "And so is this result\n";
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    sll results_test_2 = part2(test_dirs);
    sll expected_test_result_2 = -1;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        sll results_real_2 = part2(real_dirs);
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
