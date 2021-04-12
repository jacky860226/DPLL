#pragma once
#include "Basic.hpp"
#include <memory>
namespace DPLL {

class Formula {
  std::vector<const Clause *> ClausePtrs;
  std::vector<int> Frequency;
  std::vector<Literal> VarStack;

public:
  Formula(std::vector<const Clause *> &&ClausePtrs,
          std::vector<int> &&Frequency)
      : ClausePtrs(std::move(ClausePtrs)), Frequency(std::move(Frequency)) {}
  Formula(Formula &&Other)
      : ClausePtrs(std::move(Other.ClausePtrs)),
        Frequency(std::move(Other.Frequency)),
        VarStack(std::move(Other.VarStack)) {}
  Formula &operator=(Formula &&Other) {
    ClausePtrs = std::move(Other.ClausePtrs);
    Frequency = std::move(Other.Frequency);
    VarStack = std::move(Other.VarStack);
    return *this;
  }
  std::vector<const Clause *> &getClausePtrs() { return ClausePtrs; }
  std::vector<int> &getFrequency() { return Frequency; }
  std::vector<Literal> &getVariableStatus() { return VarStack; }
};
class SolverContext {
  const unsigned VariableNum;
  const std::vector<std::unique_ptr<Clause>> ClausePtrs;
  std::vector<int> LiteralPolarity;
  std::vector<Status> VariableStatus;

public:
  SolverContext(unsigned VariableNum,
                std::vector<std::unique_ptr<Clause>> &&ClausePtrs,
                std::vector<int> &&LiteralPolarity)
      : VariableNum(VariableNum), ClausePtrs(std::move(ClausePtrs)),
        LiteralPolarity(std::move(LiteralPolarity)),
        VariableStatus(VariableNum, Status::Undef) {}

  unsigned getVariableNum() const { return VariableNum; }
  std::vector<int> &getLiteralPolarity() { return LiteralPolarity; }
  const std::vector<int> &getLiteralPolarity() const { return LiteralPolarity; }
  std::vector<Status> getVariableStatus() { return VariableStatus; }
  const std::vector<Status> getVariableStatus() const { return VariableStatus; }
  Formula createFormula() const;
};

class SolverContextFactory {
public:
  std::unique_ptr<SolverContext>
  createSolverContext(const std::vector<std::vector<int>> &RawClauses) const;
};

} // namespace DPLL