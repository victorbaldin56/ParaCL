#include "while_node.hh"

namespace ast {

INode* makeWhile(INode* op, INode* sc) {
  return new WhileNode(op, sc);
}

} // namespace ast
