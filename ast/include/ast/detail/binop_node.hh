#pragma once

#include "ast/inode.hh"

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
  void dump(std::ostream& os) const override;
};

} // namespace ast
