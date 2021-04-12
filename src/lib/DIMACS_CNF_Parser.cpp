#include "DIMACS_CNF_Parser.hpp"

std::vector<std::vector<int>> DIMACS_CNF_Parser::parse(std::istream &input) {
  std::string str, all;
  while (std::getline(input, str)) {
    if (str[0] == 'c')
      continue;
    if (str[0] == 'p') {
      unsigned variableNum, clauseNum;
      sscanf(str.c_str(), "p cnf %u %u", &variableNum, &clauseNum);
      this->readVariableNum(variableNum);
      this->readClauseNum(clauseNum);
      continue;
    }
    all += " " + str + " ";
  }
  std::vector<std::vector<int>> RawClauses;
  std::stringstream ss(all);
  std::vector<int> clause;
  int v;
  while (ss >> v) {
    if (v == 0) {
      clause.shrink_to_fit();
      RawClauses.emplace_back(std::move(clause));
      clause.clear();
      continue;
    }
    clause.emplace_back(v);
  }
  return RawClauses;
}