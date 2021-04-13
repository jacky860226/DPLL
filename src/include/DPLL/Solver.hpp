#pragma once
#include "DPLL/SolverContext.hpp"

namespace DPLL {

class Solver {
  SolverContext *Context;

  void storeResult(const Formula &F);
  Status transform(Formula &F, Literal Lit);
  Status unit_propagate(Formula &F);
  Status DPLL(Formula &F);

public:
  bool solve(SolverContext *Context) {
    this->Context = Context;
    auto F = Context->createFormula();
    auto Result = DPLL(F);
    if (Result == Status::False)
      Context->setContextStatus(Status::False);
    return Result == Status::True;
  }
};

} // namespace DPLL