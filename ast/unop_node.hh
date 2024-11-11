#ifndef PARACL_AST_UNOP_NODE_HH_
#define PARACL_AST_UNOP_NODE_HH_

#include "inode.hh"

namespace ast {

/**
 * Holds unary operation.
 */
class UnOpNode : public INode {
 private:
  INode* ch_;
  UnOp op_;

 public:
  UnOpNode(INode* ch, UnOp op) noexcept : ch_(ch), op_(op) {}
  ~UnOpNode() override { delete ch_; }

  IntT calc() const override;
};

} // namespace ast

#endif // PARACL_AST_UNOP_NODE_HH_
