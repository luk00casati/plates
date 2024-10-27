#pragma once
#include <stack>
#include <string>
#include <vector>

int genir(const std::string inputfilename, std::vector<int> &codesection,
          std::vector<std::string> &datasection);

std::pair<bool, int> regex_in_list(const std::string str);

std::string removecomment(const std::string &in);

std::string removespace(std::string str);

int handle_end_type(std::stack<int> &end_type, std::vector<int> &codesection);