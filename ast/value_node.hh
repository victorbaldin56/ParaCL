#ifndef PARACL_AST_VALUE_NODE_HH_
#define PARACL_AST_VALUE_NODE_HH_

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
};

} // namespace ast

#endif // PARACL_AST_VALUE_NODE_HH_
