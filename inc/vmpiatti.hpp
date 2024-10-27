#pragma once
#include <stack>
#include <string>
#include <vector>
void vmrun(std::stack<long> &s, bool &debugprint, std::vector<int> &codesection,
           std::vector<std::string> &datasection,
           std::vector<std::pair<int, int>> &pairtable);

long handleroperationrepeat(std::stack<long> &s, bool debugprint,
                            const std::string data);

bool isstrdigits(const std::string str);

std::pair<char, size_t> findsign(const std::string data,
                                 const std::string signs);

long jumpbackto(std::vector<int> codesection, const long index, const int inst);

long jumpforwardto(std::vector<int> codesection, const long index,
                   const int inst);

long ctol(std::string str);