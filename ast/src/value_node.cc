#include "ast/value_node.hh"

namespace ast {

pINode makeValue(int val) {
  return std::make_shared<ValueNode>(val);
}

void ValueNode::dump(std::ostream& os) const {
  os << current_indent << "Value<int>: " << value_ << "\n";
}

} // namespace ast
