#include "unop_node.hh"

namespace ast {

INode* makeUnOp(INode* n, UnOp op) {
  return new UnOpNode(n, op);
}

} // namespace ast
