#pragma once

#include "ast/inode.hh"

namespace ast {

class AssignNode : public INode {
 private:
  pINode var_;
  pINode expr_;

 public:
  AssignNode(const pINode& var, const pINode& expr) : var_(var), expr_(expr) {}

  int calc() const override;
  void dump(std::ostream& os) const override;
};

} // namespace ast
