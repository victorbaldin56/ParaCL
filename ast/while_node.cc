#include "while_node.hh"

namespace ast {

pINode makeWhile(const pINode& op, const pINode& sc) {
  return std::make_shared<WhileNode>(op, sc);
}

IntT WhileNode::calc() const {
  return 0; // TODO
}

} // namespace ast
