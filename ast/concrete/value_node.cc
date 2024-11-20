#include "value_node.hh"

namespace ast {

pINode makeValue(IntT val) {
  return std::make_shared<ValueNode>(val);
}

} // namespace ast
