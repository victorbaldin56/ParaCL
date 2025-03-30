#include "ast/detail/scan_node.hh"

#include <iostream>

#include "ast/detail/dump_helpers.hh"
#include "ast/detail/scope.hh"

namespace ast {

pINode makeScan() {
  return std::make_unique<ScanNode>();
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
