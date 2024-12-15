#pragma once

#include "inode.hh"

namespace ast {

class AssignNode : public INode {
 private:
  pINode var_;
  pINode expr_;

 public:
  AssignNode(const pINode& var, const pINode& expr) : var_(var), expr_(expr) {}

  IntT calc() const override;
};

} // namespace ast
