#ifndef PARACL_AST_BINOP_NODE_HH_
#define PARACL_AST_BINOP_NODE_HH_

#include "inode.hh"

namespace ast {

class BinOpNode : public INode {
 private:
  INode* left_;
  INode* right_;
  BinOp op_;

 public:
  BinOpNode(INode* left, BinOp op, INode* right) noexcept
      : left_(left), op_(op), right_(right) {}

  ~BinOpNode() override {
    delete left_;
    delete right_;
  }

  IntT calc() const override;
};

} // namespace ast

#endif // PARACL_AST_BINOP_NODE_HH_
