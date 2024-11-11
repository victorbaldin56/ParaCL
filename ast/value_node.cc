#include "value_node.hh"

namespace ast {

INode* makeValue(IntT val) {
  return new ValueNode(val);
}

} // namespace ast
