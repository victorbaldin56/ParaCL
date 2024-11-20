#include "scope.hh"

namespace ast {

pIScope makeScope(const pIScope& par) {
  return std::make_shared<Scope>(par);
}

IntT Scope::calc() const {
  for (const pINode p : stms_) {
    p->calc();
  }
  return 0; // FIXME
}

} // namespace ast
