#ifndef PARACL_AST_DETAIL_HH_
#define PARACL_AST_DETAIL_HH_

#include <stack>

#include "inode.hh"

namespace ast {

extern std::stack<IntT> calc_stack;

} // namespace ast

#endif // PARACL_AST_DETAIL_HH_
