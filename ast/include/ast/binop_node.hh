#pragma once

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

  int calc() const override;
};

} // namespace ast
