#ifndef PARACL_AST_BINOP_NODE_HH_
#define PARACL_AST_BINOP_NODE_HH_

#include "inode.hh"

namespace ast {

class BinOpNode : public INode {
 private:
  pINode left_;
  pINode right_;
  BinOp op_;

 public:
  BinOpNode(const pINode& left, BinOp op, const pINode& right) noexcept
      : left_(left), op_(op), right_(right) {}

  IntT calc() const override;
};

} // namespace ast

#endif // PARACL_AST_BINOP_NODE_HH_
