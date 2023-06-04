cmake_minimum_required(VERSION 3.24)
project(snake C)

set(CMAKE_C_STANDARD 11)

add_executable(snake main.c color_prints.h color_prints.c linked_list.c linked_list.h snake_game.h snake_game.c)
