#include "print_node.hh"

namespace ast {

pINode makePrint(const pINode& n) {
  return std::make_shared<PrintNode>(n);
}

IntT PrintNode::calc() const {
  return 0; // TODO
}

} // namespace ast
