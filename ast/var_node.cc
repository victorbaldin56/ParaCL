#include "var_node.hh"

namespace ast {

INode* makeVar(const std::string& name) {
  return new VarNode(name);
}

} // namespace ast
