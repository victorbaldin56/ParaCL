#include "ast/binop_node.hh"

#include <cassert>

#include "ast/dump_helpers.hh"

namespace ast {
namespace {

inline const char* BinOpToString(BinOp op) {
  switch (op) {
  case BinOp::kAdd:
    return "+";
  case BinOp::kSub:
    return "-";
  case BinOp::kMul:
    return "*";
  case BinOp::kDiv:
    return "/";
  case BinOp::kMod:
    return "%";
  case BinOp::kIsEq:
    return "==";
  case BinOp::kIsNe:
    return "!=";
  case BinOp::kIsGt:
    return ">";
  case BinOp::kIsGe:
    return ">=";
  case BinOp::kIsLt:
    return "<";
  case BinOp::kIsLe:
    return "<=";
  case BinOp::kAnd:
    return "&&";
  case BinOp::kOr:
    return "||";
  case BinOp::kBtwAnd:
    return "&";
  case BinOp::kBtwOr:
    return "|";
  case BinOp::kXor:
    return "^";
  default:
    assert(0 && "Unhandled BinOp value");
  }
}

} // namespace

pINode makeBinOp(const pINode& left, BinOp op, const pINode& right) {
  return std::make_shared<BinOpNode>(left, op, right);
}

int BinOpNode::calc() const {
  switch (op_) {
  case BinOp::kAdd:
    return left_->calc() +  right_->calc();
  case BinOp::kSub:
    return left_->calc() -  right_->calc();
  case BinOp::kMul:
    return left_->calc() *  right_->calc();
  case BinOp::kDiv:
    return left_->calc() /  right_->calc();
  case BinOp::kMod:
    return left_->calc() %  right_->calc();
  case BinOp::kIsEq:
    return left_->calc() == right_->calc();
  case BinOp::kIsNe:
    return left_->calc() != right_->calc();
  case BinOp::kIsGt:
    return left_->calc() >  right_->calc();
  case BinOp::kIsGe:
    return left_->calc() >= right_->calc();
  case BinOp::kIsLt:
    return left_->calc() <  right_->calc();
  case BinOp::kIsLe:
    return left_->calc() <= right_->calc();
  case BinOp::kAnd:
    return left_->calc() && right_->calc();
  case BinOp::kOr:
    return left_->calc() || right_->calc();
  case BinOp::kBtwAnd:
    return left_->calc() &  right_->calc();
  case BinOp::kBtwOr:
    return left_->calc() |  right_->calc();
  case BinOp::kXor:
    return left_->calc() ^  right_->calc();
  case BinOp::kShl:
    return left_->calc() << right_->calc();
  case BinOp::kShr:
    return left_->calc() >> right_->calc();
  default:
    assert(0 && "Unhandled BinOp value");
  }
}

void BinOpNode::dump(std::ostream& os) const {
  os << current_indent << "BinaryOperator '" << BinOpToString(op_) << "'\n";

  dump_helpers::increaseIndent();
  left_->dump(os);
  right_->dump(os);
  dump_helpers::resetIndent();
}

llvm::Value* BinOpNode::codegen() const {

}

} // namespace ast
