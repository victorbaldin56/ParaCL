#pragma once

#include "ast/inode.hh"

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
};

} // namespace ast
