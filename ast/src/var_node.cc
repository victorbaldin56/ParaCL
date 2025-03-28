#include "ast/detail/var_node.hh"

#include <stdexcept>

#include "ast/detail/scope.hh"

namespace ast {

pINode makeVar(const std::string& name) {
  std::shared_ptr<Scope> scope
      = std::static_pointer_cast<Scope>(current_scope);
  Scope::ItNBool it_n_bool = scope->getSymbol(name);

  if (!it_n_bool.second) {
    std::string what = "'" + name + "'" + " was not declared in this scope";
    throw std::runtime_error(what);
  }

  return std::make_shared<VarNode>(it_n_bool.first);
}

void VarNode::dump(std::ostream& os) const {
  os << current_indent << "Variable '" << it_->first << "'\n";
}

} // namespace ast
