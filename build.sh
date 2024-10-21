#!/bin/sh
clang++ main.cpp codegen.cpp cpiatti.cpp -Wall -Wextra -pedantic -std=c++11 -static -pedantic -std=c++11 -o plates
strip plates
./plates