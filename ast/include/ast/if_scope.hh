#pragma once

#include <vector>

#include "ast/inode.hh"

namespace ast {

class IfScope : public IScope {
  std::vector<pINode> if_stms_;
  pIScope par_;

 public:
  IfScope(const pIScope& par = nullptr) : par_(par) {}

  int calc() const override;
  void push(const pINode& node) override { if_stms_.push_back(node); }
  pIScope parentScope() const override { return par_; }
};

} // namespace ast
