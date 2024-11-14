#include "scope.hh"

namespace ast {

pIScope makeScope(const pIScope& par) {
  return std::make_shared<Scope>(par);
}

void Scope::calc() const {
  for (const pINode& s : stms_) {
    s->calc();
  }
}

} // namespace ast
