#pragma once

#include "codegen.hh"
#include "inode.hh"

namespace ast {

/**
 * Contains constant value.
 */
class ValueNode : public INode {
 private:
  IntT value_;

 public:
  explicit ValueNode(IntT val) noexcept : value_(val) {}

  IntT calc() const noexcept override { return value_; }

  llvm::Value* codegen() const override {
    auto* ty = global_gen->getInt32Ty();
    return llvm::ConstantInt::get(ty, value_);
  }
};

} // namespace ast
