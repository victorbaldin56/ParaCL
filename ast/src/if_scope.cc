#include "ast/if_scope.hh"

#include "ast/dump_helpers.hh"

namespace ast {

pIScope makeIfScope(const pIScope& par) {
  return std::make_shared<IfScope>(par);
}

// calculates the chain of else ifs
int IfScope::calc() const {
  for (auto&& p : stms_) {
    if (p->calc()) {
      break;
    }
  }
  return 0;
}

void IfScope::dump(std::ostream& os) const {
  os << current_indent << "IfBlock\n";

  dump_helpers::increaseIndent();
  std::for_each(stms_.cbegin(), stms_.cend(),
                [&os](auto&& s){ s->dump(os); });
  dump_helpers::resetIndent();
}

} // namespace ast
