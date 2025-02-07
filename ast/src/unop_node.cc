#include "ast/unop_node.hh"

#include <cassert>

namespace ast {

pINode makeUnOp(const pINode& n, UnOp op) {
  return std::make_shared<UnOpNode>(n, op);
}

int UnOpNode::calc() const {
  switch (op_) {
  case UnOp::kPlus:
    return ch_->calc();
  case UnOp::kMinus:
    return -ch_->calc();
  case UnOp::kNot:
    return !ch_->calc();
  case UnOp::kBtwNot:
    return ~ch_->calc();
  default:
    assert(0 && "Unhandled UnOp enum value");
  }
}

} // namespace ast
