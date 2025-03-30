#pragma once

#include "ast/inode.hh"

namespace ast {

class BinOpNode : public INode {
 private:
  INode* left_;
  INode* right_;
  BinOp op_;

 public:
  BinOpNode(INode* left, BinOp op, INode* right) noexcept
      : left_(left), op_(op), right_(right) {}

  int calc() const override;
  void dump(std::ostream& os) const override;
};

} // namespace ast
