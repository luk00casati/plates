#pragma once
#include <string>
#include <vector>
#include <stack>
int genir(const std::string inputfilename, std::vector<int> &codesection,
          std::vector<std::string> &datasection);
long get_offset(std::vector<std::pair<int, int>> &pairtable, const long val);
std::vector<std::pair<int, int>> gen_pairtable(std::vector<int> &codesection);
std::pair<bool, int> regex_in_list(const std::string str);
std::string removecomment(const std::string &in);
std::string removespace(std::string str);
int handle_end_type(std::stack<int> &end_type, std::vector<int> &codesection);