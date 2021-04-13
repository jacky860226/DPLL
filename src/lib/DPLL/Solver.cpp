#include "DPLL/Solver.hpp"
#include <algorithm>
#include <cassert>

namespace DPLL {

void Solver::storeResult(const Formula &F) {
  Context->setContextStatus(Status::True);
  for (auto &VS : Context->getVariableStatus()) {
    VS = Status::True;
  }
  for (auto Lit : F.getVarStack()) {
    Context->getVariableStatus()[Lit.getVar()] =
        Lit.getSign() ? Status::False : Status::True;
  }
}

Status Solver::transform(Formula &F, Literal Lit) {
  auto &ClausePtrs = F.getClausePtrs();
  for (size_t i = 0; i < ClausePtrs.size(); ++i) {
    auto ClausePtr = ClausePtrs[i];
    bool HaveUnsatClause = true;
    for (auto CurLit : *ClausePtr) {
      if (CurLit == Lit) {
        HaveUnsatClause = false;
        ClausePtrs[i] = ClausePtrs.back();
        ClausePtrs.pop_back();
        if (ClausePtrs.empty())
          return Status::True;
        --i;
        break;
      } else if (F.getFrequency()[CurLit.getVar()] != -1)
        HaveUnsatClause = false;
    }
    if (HaveUnsatClause)
      return Status::False;
  }
  return Status::Undef;
}

Status Solver::unit_propagate(Formula &F) {
  if (F.getClausePtrs().empty())
    return Status::True;

  bool FoundUnitClause;
  auto &Frequency = F.getFrequency();
  do {
    FoundUnitClause = false;
    for (auto ClausePtr : F.getClausePtrs()) {
      size_t UndefCnt = 0;
      Literal Lit = Literal::Undefine();
      for (size_t i = 0; i < ClausePtr->size(); ++i) {
        if (Frequency[ClausePtr->at(i).getVar()] != -1) {
          if (UndefCnt++)
            break;
          Lit = ClausePtr->at(i);
        }
      }
      if (UndefCnt == 1) {
        FoundUnitClause = true;
        Frequency[Lit.getVar()] = -1;
        F.getVarStack().emplace_back(Lit);
        auto Result = transform(F, Lit);
        if (Result != Status::Undef)
          return Result;
      }
    }
  } while (FoundUnitClause);
  return Status::Undef;
}

Status Solver::DPLL(Formula &F) {
  auto Result = unit_propagate(F);
  if (Result == Status::True) {
    storeResult(F);
    return Status::True;
  } else if (Result == Status::False)
    return Status::False;

  auto &Frequency = F.getFrequency();
  int Var = std::distance(Frequency.begin(),
                          std::max_element(Frequency.begin(), Frequency.end()));
  Literal X(Var, Context->getLiteralPolarity()[Var] < 0);
  for (auto Lit : {X, ~X}) {
    Formula NewF = F;
    NewF.getFrequency()[Lit.getVar()] = -1;
    NewF.getVarStack().emplace_back(Lit);

    auto TransformResult = transform(NewF, Lit);
    if (TransformResult == Status::True) {
      storeResult(F);
      return Status::True;
    } else if (TransformResult == Status::False)
      continue;

    auto DPLL_Result = DPLL(NewF);
    if (DPLL_Result == Status::True)
      return Status::True;
  }
  return Status::False;
}

} // namespace DPLL