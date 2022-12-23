
# filename = "puzzle_inputs/day_21_test_input.txt"
filename = "puzzle_inputs/day_21_input.txt"
file = open(filename, "rt")
lines = file.read().splitlines()
parsed_lines = []
for line in lines:
    parsed_lines.append(line.split(': '))

while 'root' not in locals():
    for line in parsed_lines:
        func = line[0] + " = int(" + line[1] + ")"  # Add casting to int for division
        try:
            exec(func)
        except:
            continue

print("root is " + str(eval("root")))
