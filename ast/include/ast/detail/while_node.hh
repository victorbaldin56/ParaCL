#pragma once

#include "ast/inode.hh"

namespace ast {

class WhileNode : public INode {
 private:
  INode* cond_;
  INode* stm_;

 public:
  WhileNode(INode* cond, INode* stm) noexcept
      : cond_(cond), stm_(stm) {}

  int calc() const override;
  void dump(std::ostream& os) const override;
};

} // namespace ast
