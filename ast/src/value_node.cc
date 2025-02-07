#include "ast/value_node.hh"

namespace ast {

pINode makeValue(int val) {
  return std::make_shared<ValueNode>(val);
}

} // namespace ast
