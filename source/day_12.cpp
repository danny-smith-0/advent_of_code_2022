#include <advent_of_code.h>
#include <functional>

struct VertInfo
{
    coords_t coord;
    char value = '#';
    char height = '#';
    int dist = INT_MAX - 1;
    coords_t prev_coord;
    char prev_height = '#';

    VertInfo(){}
    VertInfo(size_t ii, size_t jj, strings_t const& heightmap, VertInfo const& previous)
    {
        coord.first = ii;
        coord.second = jj;

        value = heightmap[ii][jj];
        if (value == 'S')
            height = 'a';
        else if (value == 'E')
            height = 'z';
        else
            height = value;

        dist = previous.dist + 1;
        prev_coord = previous.coord;
        prev_height = previous.height;
    }
};

std::string print_coords(coords_t coords)
{
    std::stringstream ss;
    ss << "(" << coords.first << ", " << coords.second << ")";
    return ss.str();
}

VertInfo get_vert_with_lowest_distance(std::vector<VertInfo>& unvisited_verts)
{
    if (unvisited_verts.size() == 1)
    {
        VertInfo vert = unvisited_verts[0];
        unvisited_verts.clear();
        return vert;
    }

    int min_dist = INT_MAX;
    std::vector<VertInfo>::iterator min_itr = unvisited_verts.begin();
    for (auto itr = unvisited_verts.begin(); itr < unvisited_verts.end(); ++itr)
    {
        if (itr->dist < min_dist)
        {
            min_dist = itr->dist;
            min_itr = itr;
        }
    }

    VertInfo vert = *min_itr;
    unvisited_verts.erase(min_itr);
    return vert;
}

coords_t_vec get_start_coords(strings_t heightmap, char start_char = 'S')
{
    coords_t_vec start_pts;
    for (size_t ii = 0; ii < heightmap.size(); ++ii)
    {
        std::string::iterator iter_start = std::find(heightmap[ii].begin(), heightmap[ii].end(), start_char);
        while (iter_start != heightmap[ii].end())
        {
            size_t jj = iter_start - heightmap[ii].begin();
            coords_t coord(ii, jj);
            start_pts.push_back(coord);
            iter_start = std::find(iter_start + 1, heightmap[ii].end(), start_char);
        }
    }
    return start_pts;
}

// I thought part two was going to change the way we decided if we could climb, e.g. you can now climb as long as the steps are <= 3
// Nope. Just got some fun practice passing around a funcion object
std::function<bool(char, char)> can_i_reach_my_neighbor = [](char orig, char neighbor)
{
    char height;
    if (neighbor == 'S')
        height = 'a';
    else if (neighbor == 'E')
        height = 'z';
    else
        height = neighbor;

    return height <= orig + 1;
};

int shortest_path(strings_t heightmap, std::function<bool(char, char)> can_i_reach_my_neighbor, std::vector<VertInfo> unvisited, VertInfo const& end_path)
{
    std::vector<VertInfo> visited;

    while (!unvisited.empty())
    {
        // Pick the unvisited vert with the lowest distance
        VertInfo vert = get_vert_with_lowest_distance(unvisited);

        if (vert.coord.first == 3 && vert.coord.second == 2)
            int abc = 1;

        // Add neighbors if they are reachable
        std::vector<VertInfo> neighbors;
        if (vert.coord.second < heightmap[0].size() - 1)
        {
            VertInfo neighbor(vert.coord.first, vert.coord.second + 1, heightmap, vert);  // Moving Right
            neighbors.push_back(neighbor);
        }
        if (vert.coord.first < heightmap.size() - 1)
        {
            VertInfo neighbor(vert.coord.first + 1, vert.coord.second, heightmap, vert);  // Moving Down
            neighbors.push_back(neighbor);
        }
        if (vert.coord.second > 0)
        {
            VertInfo neighbor(vert.coord.first, vert.coord.second - 1, heightmap, vert);  // Moving Left
            neighbors.push_back(neighbor);
        }
        if (vert.coord.first > 0)
        {
            VertInfo neighbor(vert.coord.first - 1, vert.coord.second, heightmap, vert);  // Moving Up
            neighbors.push_back(neighbor);
        }

        for (auto neighbor : neighbors)
        {
            // Can I reach it?
            if (neighbor.height == 'q')
                int abc = 1;
            bool accessible = can_i_reach_my_neighbor(vert.height, neighbor.height);

            if (accessible)
            {
                //Has it already been visited?
                std::vector<VertInfo>::iterator itr_visited = std::find_if(visited.begin(), visited.end(), [neighbor](VertInfo visited_vert) -> bool { return neighbor.coord == visited_vert.coord;} );
                bool new_vert = itr_visited == visited.end();
                if (new_vert)
                {
                    // Either add it to the list of unvisted, or if already exists, update it if the new path has a lower distance
                    std::vector<VertInfo>::iterator itr_unvisited = std::find_if(unvisited.begin(), unvisited.end(), [neighbor](VertInfo unvisited_vert) -> bool { return neighbor.coord == unvisited_vert.coord;} );
                    if (itr_unvisited != unvisited.end())
                    {
                        if (neighbor.dist < itr_unvisited->dist)
                            *itr_unvisited = neighbor;
                    }
                    else
                        unvisited.push_back(neighbor);
                }
            }
        }

        visited.push_back(vert);
    }

    auto end_vert = std::find_if(visited.begin(), visited.end(), [end_path](VertInfo visited_vert) -> bool { return end_path.coord == visited_vert.coord;});
    if (end_vert != visited.end())
        return end_vert->dist;
    else
        return INT_MAX;
}

int shortest_path_multiple_starts(strings_t heightmap, std::function<bool(char, char)> can_i_reach_my_neighbor, char start_char = 'S')
{
    // Find the start
    coords_t_vec start_coords = get_start_coords(heightmap, start_char);

    // Find the end, 'E'
    VertInfo end_path;
    for (size_t ii = 0; ii < heightmap.size(); ++ii)
    {
        std::string::iterator iter_E = std::find(heightmap[ii].begin(), heightmap[ii].end(), 'E');
        if (iter_E != heightmap[ii].end())
        {
            size_t jj = iter_E - heightmap[ii].begin();
            end_path = VertInfo(ii, jj, heightmap,VertInfo());
        }
    }

    int count = 0;
    int min_path_length = INT_MAX;
    for (auto start_coord : start_coords)
    {
        std::vector<VertInfo> unvisited;

        VertInfo start(start_coord.first, start_coord.second, heightmap, VertInfo());
        start.dist = 0;
        unvisited.push_back(start);
        unvisited.push_back(end_path);

        int path_length = shortest_path(heightmap, can_i_reach_my_neighbor, unvisited, end_path);
        std::cout << ++count << " of " << start_coords.size() << ": " << path_length << " " << print_coords(start_coord) << "\n";
        min_path_length = std::min(min_path_length, path_length);
    }
    return min_path_length;
}

int part1(strings_t input)
{
    return shortest_path_multiple_starts(input, can_i_reach_my_neighbor, 'S');
}

int part2(strings_t input)
{
    return shortest_path_multiple_starts(input, can_i_reach_my_neighbor, 'a');
}

int main ()
{
    std::string day_string = "12";
    std::cout << "Day " << day_string << std::endl;
    strings_t test_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_test_input.txt");
    strings_t real_data = aoc::get_strings_from_file("../puzzle_inputs/day_" + day_string + "_input.txt");

    std::cout << "\nPart 1\n\n";
    int results_test_1 = part1(test_data);
    int expected_test_result_1 = 31;
    if (aoc::results(results_test_1, expected_test_result_1))
    {
        int results_real_1 = part1(real_data);
        int solved = 420;
        std::cout << "Real result is " << results_real_1 << std::endl;
    }

    std::cout << "\nPart 2\n\n";
    int results_test_2 = part2(test_data);
    int expected_test_result_2 = 29;
    if (aoc::results(results_test_2, expected_test_result_2))
    {
        int results_real_2 = part2(real_data);
        int solved = 414;
        std::cout << "Real result is " << results_real_2 << "\n\nFinished" << std::endl;
    }

    return 0;
}
