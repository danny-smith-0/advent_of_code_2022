
def get_elf_move(elf, elves, round):
    # Contents: North, East, Cell is Available
    nw = [elf[0] +  1, elf[1] + -1, True]
    nn = [elf[0] +  1, elf[1] +  0, True]
    ne = [elf[0] +  1, elf[1] +  1, True]
    ww = [elf[0] +  0, elf[1] + -1, True]
    ee = [elf[0] +  0, elf[1] +  1, True]
    sw = [elf[0] + -1, elf[1] + -1, True]
    ss = [elf[0] + -1, elf[1] +  0, True]
    se = [elf[0] + -1, elf[1] +  1, True]

    for other_elf in elves:
        if nw[2] and other_elf == nw[:2]:
            nw[2] = False
        if nn[2] and other_elf == nn[:2]:
            nn[2] = False
        if ne[2] and other_elf == ne[:2]:
            ne[2] = False
        if ww[2] and other_elf == ww[:2]:
            ww[2] = False
        if ee[2] and other_elf == ee[:2]:
            ee[2] = False
        if sw[2] and other_elf == sw[:2]:
            sw[2] = False
        if ss[2] and other_elf == ss[:2]:
            ss[2] = False
        if se[2] and other_elf == se[:2]:
            se[2] = False

    move = []
    if nw[2] and nn[2] and ne[2] and ww[2] and ee[2] and sw[2] and ss[2] and se[2]:
        return move

    # this might save some time?
    if not (nw[2] and nn[2] and ne[2]) and not (nw[2] and ww[2] and sw[2]) and \
        not (sw[2] and ss[2] and se[2]) and not (ne[2] and ee[2] and se[2]):
        return move

    check_coords = ["north", "south", "west", "east"]
    check_coords *= 2
    shifter = round % 4
    check_coords = check_coords[shifter:shifter + 4]

    for check in check_coords:
        if check == "north" and   nw[2] and nn[2] and ne[2]:
            move = nn[:2]
            return move
        elif check == "south" and sw[2] and ss[2] and se[2]:
            move = ss[:2]
            return move
        elif check == "west" and  nw[2] and ww[2] and sw[2]:
            move = ww[:2]
            return move
        elif check == "east" and  ne[2] and ee[2] and se[2]:
            move = ee[:2]
            return move
    return move

def step_elves(n_step, elves):
    moves = []
    for ii, elf in enumerate(elves):
        proposed_move = get_elf_move(elf, elves, n_step)
        if len(proposed_move) > 0:
            num_moves = len(moves)
            # remove any moves that are the same as proposed
            moves = [ii for ii in moves if ii[0] != proposed_move]
            num_moves_updated = len(moves)
            # if nothing was removed (the proposed move is unique), add it
            if num_moves == num_moves_updated:
                moves.append([proposed_move, ii])

    # do the moves
    changed = len(moves) > 0
    for move in moves:
        elves[move[1]] = move[0]
    return changed

def get_elf_grid(elves):
    min_north = min([elf[0] for elf in elves])
    max_north = max([elf[0] for elf in elves])
    min_east = min([elf[1] for elf in elves])
    max_east = max([elf[1] for elf in elves])

    north_width = max_north - min_north + 1
    east_width = max_east - min_east + 1
    grid = [ ['.'] * east_width for _ in range(north_width)]
    for elf in elves:
        grid[-(elf[0] - max_north)][elf[1] - min_east] = '#'
    return grid, north_width, east_width

def print_grid(grid):
    my_str = ""
    for line in grid:
        for elem in line:
            my_str += elem
        my_str += "\n"
    print(my_str)

def part1(elves):
    for step in range(10):
        print(step + 1)
        step_elves(step, elves)

    grid, north_width, east_width = get_elf_grid(elves)
    empty_spaces = north_width * east_width - len(elves)
    print_grid(grid)
    return empty_spaces

def part2(elves):
    changed = True
    step = -1
    while changed:
        step += 1
        print(step + 1)
        changed = step_elves(step, elves)
        if not changed:
            grid, _, _  = get_elf_grid(elves)
            print_grid(grid)
    return step + 1


### Main function

day = "23"
filename = "puzzle_inputs/day_" + day + "_input.txt"
# filename = "puzzle_inputs/day_" + day + "_test_input.txt"
# filename = "puzzle_inputs/day_" + day + "_test_input_2.txt"
file = open(filename, "rt")
input = file.read().splitlines()
elves_pt1 = []
elves_pt2 = []
for ii, input_line in enumerate(input):
    for jj, input_cell in enumerate(input_line):
        if input_cell == '#':
            elves_pt1.append([-ii, jj])
            elves_pt2.append([-ii, jj])


print("part1: " + str(part1(elves_pt1)))
# 4116

print("part2: " + str(part2(elves_pt2)))
# 984

print("el fin")
