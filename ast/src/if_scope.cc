#include "ast/if_scope.hh"

namespace ast {

int IfScope::calc() const {
  for (auto&& p : if_stms_) {
    if (p->calc()) {
      break;
    }
  }
  return 0;
}

} // namespace ast
