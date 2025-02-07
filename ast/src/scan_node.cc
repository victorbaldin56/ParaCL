#include "ast/scan_node.hh"

#include <iostream>

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

} // namespace ast
