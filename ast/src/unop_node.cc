#include "ast/detail/unop_node.hh"

#include <cassert>

#include "ast/detail/dump_helpers.hh"
#include "ast/detail/var_node.hh"

namespace ast {
namespace {

inline const char* UnOpToString(UnOp op) {
  switch (op) {
  case UnOp::kPlus:
    return "+";
  case UnOp::kMinus:
    return "-";
  case UnOp::kNot:
    return "!";
  case UnOp::kBtwNot:
    return "~";
  case UnOp::kPreIncr:
    return "++ (pre)";
  case UnOp::kPreDecr:
    return "-- (pre)";
  case UnOp::kPostIncr:
    return "++ (post)";
  case UnOp::kPostDecr:
    return "-- (post)";
  default:
    assert(0 && "Unhandled UnOp enum value");
  }
}

} // namespace

pINode makeUnOp(const pINode& n, UnOp op) {
  return std::make_unique<UnOpNode>(n.get(), op);
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
    return dynamic_cast<VarNode*>(ch_)->preIncrement();
  case UnOp::kPreDecr:
    return dynamic_cast<VarNode*>(ch_)->preDecrement();
  case UnOp::kPostIncr:
    return dynamic_cast<VarNode*>(ch_)->postIncrement();
  case UnOp::kPostDecr:
    return dynamic_cast<VarNode*>(ch_)->postDecrement();
  default:
    assert(0 && "Unhandled UnOp enum value");
  }
}

void UnOpNode::dump(std::ostream& os) const {
  os << current_indent << "UnaryOperator '" << UnOpToString(op_) << "'\n";

  dump_helpers::increaseIndent();
  ch_->dump(os);
  dump_helpers::resetIndent();
}

} // namespace ast
