#pragma once

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
  llvm::Value* codegen() const override;
};

} // namespace ast
