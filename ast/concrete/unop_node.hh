#ifndef PARACL_AST_UNOP_NODE_HH_
#define PARACL_AST_UNOP_NODE_HH_

#include "inode.hh"

namespace ast {

/**
 * Holds unary operation.
 */
class UnOpNode : public INode {
 private:
  pINode ch_;
  UnOp op_;

 public:
  UnOpNode(const pINode& ch, UnOp op) noexcept : ch_(ch), op_(op) {}

  IntT calc() const override;
};

} // namespace ast

#endif // PARACL_AST_UNOP_NODE_HH_
