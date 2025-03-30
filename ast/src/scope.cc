#include "ast/detail/scope.hh"

#include "ast/detail/dump_helpers.hh"

namespace ast {

pIScope makeScope(const pIScope& par) {
  return std::make_unique<Scope>(par.get());
}

int Scope::calc() const {
  for (const pINode& p : stms_) {
    p->calc();
  }
  return 0;
}

void Scope::dump(std::ostream& os) const {
  os << current_indent << "Scope\n";

  dump_helpers::increaseIndent();
  std::for_each(stms_.cbegin(), stms_.cend(),
                [&os](auto&& s){ s->dump(os); });
  dump_helpers::resetIndent();
}

/**
 * Finds symbol in current & all parent scopes.
 */
Scope::ItNBool Scope::getSymbol(const std::string& name) {
  for (Scope* pscope = this; pscope != nullptr;
       pscope = dynamic_cast<Scope*>(pscope->parentScope())) {
    ItNBool it_n_bool = pscope->getLocalSymbol(name);

    if (it_n_bool.second) {
      return it_n_bool;
    }
  }

  return {symtab_.end(), false};
}

} // namespace ast
