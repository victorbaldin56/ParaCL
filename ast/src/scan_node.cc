#include "ast/scan_node.hh"

#include <iostream>

#include "scope.hh"

namespace ast {

pINode makeScan() {
  return std::make_shared<ScanNode>();
}

IntT ScanNode::calc() const {
  IntT tmp{};
  std::cin >> tmp;
  return tmp;
}

} // namespace ast
