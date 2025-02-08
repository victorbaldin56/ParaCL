#include "ast/if_scope.hh"

namespace ast {

pIScope makeIfScope(const pIScope& par) {
  return std::make_shared<IfScope>(par);
}

int IfScope::calc() const {
  for (auto&& p : if_stms_) {
    if (p->calc()) {
      break;
    }
  }
  return 0;
}

} // namespace ast
