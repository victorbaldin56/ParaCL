#include "scope.hh"

namespace ast {

pIScope makeScope(const pIScope& par) {
  return std::make_shared<Scope>(par);
}

IntT Scope::calc() const {
  for (const pINode p : stms_) {
    p->calc();
  }
  return 0;
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
