//
// Created by manjaro on 6/1/23.
//
#include "color_prints.h"
#include <stdio.h>
#ifndef color_prints
#define color_prints

void print_green(const char* str){
    fflush(stdout);
    printf("\x1B[32m%s", str);
}
void print_red(const char* str){
    printf("\x1B[31m%s", str);
}
void print_purple(const char* str){
    printf("\x1B[35m%s", str);
}
void print_blue(const char* str){
    printf("\x1B[34m%s", str);
}
#endif

