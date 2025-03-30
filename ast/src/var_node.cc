#include "ast/detail/var_node.hh"

#include <stdexcept>

#include "ast/detail/scope.hh"

namespace ast {

pINode makeVar(const std::string &name) {
  Scope *scope = dynamic_cast<Scope *>(current_scope.get());
  Scope::ItNBool it_n_bool = scope->getSymbol(name);

  if (!it_n_bool.second) {
    std::string what = "'" + name + "'" + " was not declared in this scope";
    throw std::runtime_error(what);
  }

  return std::make_unique<VarNode>(it_n_bool.first);
}

void VarNode::dump(std::ostream &os) const {
  os << current_indent << "Variable '" << it_->first << "'\n";
}

} // namespace ast
