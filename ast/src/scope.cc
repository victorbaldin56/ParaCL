#include "ast/scope.hh"

namespace ast {

pIScope makeScope(const pIScope& par) {
  return std::make_shared<Scope>(par);
}

int Scope::calc() const {
  for (const pINode& p : stms_) {
    p->calc();
  }
  return 0;
}

void Scope::dump(std::ostream& os) const {

}

/**
 * Finds symbol in current & all parent scopes.
 */
Scope::ItNBool Scope::getSymbol(const std::string& name) {
  for (Scope* pscope = this; pscope != nullptr;
       pscope = static_cast<Scope*>(pscope->parentScope().get())) {
    ItNBool it_n_bool = pscope->getLocalSymbol(name);

    if (it_n_bool.second) {
      return it_n_bool;
    }
  }

  return {symtab_.end(), false};
}

} // namespace ast
