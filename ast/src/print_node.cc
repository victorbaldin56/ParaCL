#include "ast/print_node.hh"

#include <iostream>

namespace ast {

pINode makePrint(const pINode& n) {
  return std::make_shared<PrintNode>(n);
}

int PrintNode::calc() const {
  std::cout << stm_->calc() << "\n";
  return 0;
}

} // namespace ast
