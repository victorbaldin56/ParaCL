#include "var_node.hh"

namespace ast {

pINode makeVar(const std::string& name) {
  return std::make_shared<VarNode>(name);
}

IntT VarNode::calc() const {
  return find()->second.value;
}

} // namespace ast
