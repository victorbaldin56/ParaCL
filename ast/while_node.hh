#ifndef PARACL_AST_WHILE_NODE_HH_
#define PARACL_AST_WHILE_NODE_HH_

#include "inode.hh"

namespace ast {

class WhileNode : public INode {
 private:
  pINode cond_;
  pINode stm_;

 public:
  WhileNode(const pINode& cond, const pINode& stm) noexcept
      : cond_(cond), stm_(stm) {}

  IntT calc() const override;
};

} // namespace ast

#endif // PARACL_AST_WHILE_NODE_HH_
