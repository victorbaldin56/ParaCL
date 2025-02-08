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

void PrintNode::dump(std::ostream& os) const {

}

} // namespace ast
