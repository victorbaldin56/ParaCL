#include "ast/assign_node.hh"

#include "ast/scope.hh"
#include "ast/var_node.hh"

namespace ast {

pINode makeAssign(const std::string& var_name, const pINode& expr) {
  std::shared_ptr<Scope> scope
      = std::static_pointer_cast<Scope>(current_scope);
  Symtab::iterator it = scope->maybeInsertSymbol(var_name);
  pINode var_ptr = std::make_shared<VarNode>(it);
  return std::make_shared<AssignNode>(var_ptr, expr);
}

IntT AssignNode::calc() const {
  IntT expr_val = expr_->calc();
  std::shared_ptr<VarNode> vp = std::static_pointer_cast<VarNode>(var_);
  vp->assign(expr_val);
  return expr_val;
}

} // namespace ast