#pragma once

#include <vector>

#include "ast/inode.hh"

namespace ast {

class IfScope : public IScope {
  std::vector<pINode> if_stms_;

 public:
  int calc() const override;
  void push(const pINode& node) override { if_stms_.push_back(node); }
};

} // namespace ast
