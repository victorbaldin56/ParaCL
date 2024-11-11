#include "scan_node.hh"

namespace ast {

INode* makeScan(INode* n) {
  return new ScanNode(n);
}

} // namespace ast
