#pragma once
#include <cstdio>
#include <istream>
#include <sstream>
#include <string>
#include <tuple>
#include <vector>

class DIMACS_CNF_Parser {
  void readVariableNum(unsigned VariableNum) { std::ignore = VariableNum; }
  void readClauseNum(unsigned ClauseNum) { std::ignore = ClauseNum; }

public:
  std::vector<std::vector<int>> parse(std::istream &input);
};