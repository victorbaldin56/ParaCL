#pragma once

#include "codegen.hh"
#include "inode.hh"

namespace ast {

/**
 * Contains constant value.
 */
class ValueNode : public INode {
 private:
  int value_;

 public:
  explicit ValueNode(int val) noexcept : value_(val) {}

  int calc() const noexcept override { return value_; }
  void dump(std::ostream& os) const override;

  llvm::Value* codegen() const override {
    auto* ty = global_gen->getInt32Ty();
    return llvm::ConstantInt::get(ty, value_);
  }
};

} // namespace ast
