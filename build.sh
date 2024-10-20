#!/bin/sh
clang++ main.cpp codegen.cpp cpiatti.cpp -Wall -Wextra -pedantic -std=c++11 -static -o plates
strip plates
./plates