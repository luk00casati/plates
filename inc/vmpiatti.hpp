#pragma once
#include <stack>
#include <string>
#include <vector>

void vmrun(std::stack<long> &s, bool &debugprint, std::vector<int> &codesection,
           std::vector<std::string> &datasection);

long handleroperationrepeat(std::stack<long> &s, bool debugprint,
                            const std::string data);

bool handleroperationif(std::stack<long> &s, bool debugprint,
                        const std::string data);

bool isstrdigits(const std::string str);

std::pair<char, size_t> findsign(const std::string data,
                                 const std::string signs);

size_t jumpbackto(std::vector<int> &codesection, const size_t current_index,
                  const int current_inst, const int dest_inst);

size_t jumpforwardto(std::vector<int> &codesection, const size_t current_index,
                     const int current_inst, const int dest_inst);

long ctol(const std::string str);