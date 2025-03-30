#pragma once

#include "ast/inode.hh"

namespace ast {

class AssignNode : public INode {
 private:
  pINode var_;
  INode* expr_;

 public:
  AssignNode(pINode&& var, INode* expr) : var_(std::move(var)), expr_(expr) {}

  int calc() const override;
  void dump(std::ostream& os) const override;
};

} // namespace ast
