#include "context.hh"

namespace ast {

ast::pIScope current_scope;
std::stack<IntT> calc_stack;

pIScope& getCurrentScopeRef() { return current_scope; }

} // namespace ast
