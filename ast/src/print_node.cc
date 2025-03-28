#include "ast/detail/print_node.hh"

#include <iostream>

#include "ast/detail/dump_helpers.hh"

namespace ast {

pINode makePrint(const pINode& n) {
  return std::make_shared<PrintNode>(n);
}

int PrintNode::calc() const {
  std::cout << stm_->calc() << "\n";
  return 0;
}

void PrintNode::dump(std::ostream& os) const {
  os << current_indent << "PrintOperator\n";

  dump_helpers::increaseIndent();
  stm_->dump(os);
  dump_helpers::resetIndent();
}

} // namespace ast
