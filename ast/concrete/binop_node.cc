#include "binop_node.hh"

namespace ast {

pINode makeBinOp(const pINode& left, BinOp op, const pINode& right) {
  return std::make_shared<BinOpNode>(left, op, right);
}

IntT BinOpNode::calc() const {
  return 0; // TODO
}

} // namespace ast
