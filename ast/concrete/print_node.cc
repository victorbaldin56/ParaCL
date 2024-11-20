#include "print_node.hh"

#include <iostream>

namespace ast {

pINode makePrint(const pINode& n) {
  return std::make_shared<PrintNode>(n);
}

IntT PrintNode::calc() const {
  std::cout << stm_->calc();
  return 0; // FIXME
}

} // namespace ast
