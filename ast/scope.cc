#include "scope.hh"

namespace ast {

IScope* makeScope(IScope* par) {
  return new Scope(par);
}

} // namespace ast
