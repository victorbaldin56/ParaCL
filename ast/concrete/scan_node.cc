#include "scan_node.hh"

#include <iostream>

namespace ast {

pINode makeScan(const pINode& n) {
  return std::make_shared<ScanNode>(n);
}

IntT ScanNode::calc() const {
  std::shared_ptr<VarNode> var_ptr = std::static_pointer_cast<VarNode>(stm_);
  std::cin >> var_ptr->find()->second.value;
  return 0; // FIXME (?)
}

} // namespace ast
