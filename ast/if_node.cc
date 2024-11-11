#include "if_node.hh"

namespace ast {

INode* makeIf(INode* op, INode* sc) {
  return new IfNode(op, sc);
}

} // namespace ast
