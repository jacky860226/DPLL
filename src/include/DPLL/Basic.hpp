#pragma once
#include <cinttypes>
#include <vector>

namespace DPLL {

enum Status : int8_t { False = 0, True = 1, Undef = 2 };

class Literal {
  int V;

public:
  Literal() = default;
  Literal(int Var, bool Sign = false) : V(Var + Var + (int)Sign) {}
  static Literal Undefine() { return Literal(-1); }
  Literal operator^(bool b) const {
    Literal Res;
    Res.V = V ^ (unsigned)b;
    return Res;
  }
  Literal operator~() const { return operator^(1); }
  bool getSign() const { return V & 1; }
  int getVar() const { return V >> 1; }
  operator int() const { return V; }
};

class Clause : public std::vector<Literal> {
public:
  Clause() = default;
  Clause(std::vector<Literal> &&Ps) : std::vector<Literal>(std::move(Ps)) {}
  Clause(Clause &&Other) : std::vector<Literal>(std::move(Other)) {}
};

} // namespace DPLL