#pragma once

#include <vector>

#include "ast/inode.hh"
#include "ast/scope.hh"

namespace ast {

class IfScope : public Scope {
 public:
  IfScope(const pIScope& par = nullptr) : Scope(par) {}

  int calc() const override;
};

} // namespace ast
