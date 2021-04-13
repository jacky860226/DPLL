#include "DPLL/SolverContext.hpp"

namespace DPLL {

Formula SolverContext::createFormula() const {
  std::vector<const Clause *> ClausePtrs;
  std::vector<int> Frequency(VariableNum);
  for (auto &C : this->ClausePtrs) {
    ClausePtrs.emplace_back(C.get());
    for (auto Lit : *C) {
      ++Frequency.at(Lit.getVar());
    }
  }
  return Formula(std::move(ClausePtrs), std::move(Frequency));
}

void SolverContext::outputResult(std::ostream &output) const {
  assert(isSolved());
  if (ContextStatus == Status::False) {
    output << "UNSAT\n";
    return;
  }
  output << "SAT\n";
  for (size_t i = 0; i < VariableStatus.size(); ++i) {
    if (VariableStatus[i] == Status::False)
      output << '-';
    output << i + 1 << ' ';
  }
  output << "0\n";
}

std::unique_ptr<SolverContext> SolverContextFactory::createSolverContext(
    const std::vector<std::vector<int>> &RawClauses) const {
  unsigned VariableNum = 0;
  std::vector<std::unique_ptr<Clause>> ClausePtrs;

  for (auto &RC : RawClauses)
    for (int RV : RC)
      VariableNum = std::max(VariableNum, (unsigned)std::abs(RV));
  std::vector<int> LiteralPolarity(VariableNum);

  for (auto &RC : RawClauses) {
    auto ClausePtr = std::make_unique<Clause>();
    for (int RV : RC) {
      Literal Lit(std::abs(RV) - 1, RV < 0);
      ClausePtr->emplace_back(Lit);
      if (Lit.getSign())
        --LiteralPolarity[Lit.getVar()];
      else
        ++LiteralPolarity[Lit.getVar()];
    }
    ClausePtrs.emplace_back(std::move(ClausePtr));
  }
  return std::make_unique<SolverContext>(VariableNum, std::move(ClausePtrs),
                                         std::move(LiteralPolarity));
}

} // namespace DPLL