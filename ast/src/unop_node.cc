#include "ast/unop_node.hh"

#include <cassert>

#include "ast/dump_helpers.hh"
#include "ast/var_node.hh"

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
  case UnOp::kPreIncr:
    return std::static_pointer_cast<VarNode>(ch_)->preIncrement();
  case UnOp::kPreDecr:
    return std::static_pointer_cast<VarNode>(ch_)->preDecrement();
  case UnOp::kPostIncr:
    return std::static_pointer_cast<VarNode>(ch_)->postIncrement();
  case UnOp::kPostDecr:
    return std::static_pointer_cast<VarNode>(ch_)->postDecrement();
  default:
    assert(0 && "Unhandled UnOp enum value");
  }
}

void UnOpNode::dump(std::ostream& os) const {
  os << current_indent << "UnaryOperator\n";

  dump_helpers::increaseIndent();
  ch_->dump(os);
  dump_helpers::resetIndent();
}

} // namespace ast
