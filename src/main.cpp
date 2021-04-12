#include "DIMACS_CNF_Parser.hpp"
#include "DPLL/SolverContext.hpp"
#include "IOStreamCreator.hpp"

int main(int argc, char **argv) {
  DIMACS_CNF_Parser Parser;

  auto InputStreamPtr = InputStreamCreator().createInputStream(argc, argv);
  auto RawClauses = Parser.parse(*InputStreamPtr);
  InputStreamPtr = nullptr;

  auto SolverContextFactory = DPLL::SolverContextFactory();
  auto SolverContext = SolverContextFactory.createSolverContext(RawClauses);
}