#include "print_node.hh"

namespace ast {

INode* makePrint(INode* n) {
  return new PrintNode(n);
}

} // namespace ast
