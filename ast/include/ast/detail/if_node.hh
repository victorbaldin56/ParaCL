#pragma once

#include "ast/inode.hh"

namespace ast {

class IfNode : public INode {
 protected:
  INode* cond_;
  INode* stm_;
  INode* else_stm_;

 public:
  IfNode(INode* cond, INode* stm, INode* else_stm) noexcept
      : cond_(cond), stm_(stm), else_stm_(else_stm) {}
  int calc() const override;
  void dump(std::ostream& os) const override;
};

} // namespace ast
