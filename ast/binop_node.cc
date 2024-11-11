#include "binop_node.hh"

namespace ast {

INode* makeBinOp(INode* left, BinOp op, INode* right) {
  return new BinOpNode(left, op, right);
}

} // namespace ast
