#include "ast/binop_node.hh"

#include <cassert>

namespace ast {

pINode makeBinOp(const pINode& left, BinOp op, const pINode& right) {
  return std::make_shared<BinOpNode>(left, op, right);
}

IntT BinOpNode::calc() const {
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

} // namespace ast
