cmake_minimum_required (VERSION 3.14)
project (advent_of_code_2022)

add_subdirectory(ext/aoc_utils)

add_executable ( aoc
    # source/day_01.cpp
    # source/day_02.cpp
    # source/day_03.cpp
    source/day_04.cpp
    # source/day_05.cpp
    # source/day_06.cpp
	# source/day_07.cpp
	# source/day_08.cpp
	# source/day_09.cpp
	# source/day_10.cpp
	# source/day_11.cpp
	# source/day_12.cpp
	# source/day_13.cpp
	# source/day_14.cpp
	# source/day_15.cpp
	# source/day_16.cpp
	# source/day_17.cpp
	# source/day_18.cpp
	# source/day_19.cpp
	# source/day_20.cpp
	# source/day_21.cpp
	# source/day_22.cpp
	# source/day_23.cpp
	# source/day_24.cpp
	# source/day_25.cpp
)

target_link_libraries( aoc
    PUBLIC
    aoc_utils
)

target_compile_features( aoc
	PRIVATE
	cxx_std_17
)
