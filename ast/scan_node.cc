#include "scan_node.hh"

namespace ast {

pINode makeScan(const pINode& n) {
  return std::make_shared<ScanNode>(n);
}

IntT ScanNode::calc() const {
  return 0; // TODO
}

} // namespace ast
