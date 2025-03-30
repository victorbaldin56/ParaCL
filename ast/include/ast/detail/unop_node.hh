#pragma once

#include "ast/inode.hh"

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

  int calc() const override;
  void dump(std::ostream& os) const override;
};

} // namespace ast
