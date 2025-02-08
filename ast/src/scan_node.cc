#include "ast/scan_node.hh"

#include <iostream>

#include "ast/dump_helpers.hh"
#include "ast/scope.hh"

namespace ast {

pINode makeScan() {
  return std::make_shared<ScanNode>();
}

int ScanNode::calc() const {
  int tmp{};
  std::cin >> tmp;
  return tmp;
}

void ScanNode::dump(std::ostream& os) const {
  os << current_indent << "ScanOperator\n";
}

} // namespace ast
