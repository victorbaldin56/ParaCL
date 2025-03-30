#include "ast/detail/assign_node.hh"

#include "ast/detail/dump_helpers.hh"
#include "ast/detail/scope.hh"
#include "ast/detail/var_node.hh"

namespace ast {

pINode makeAssign(const std::string &var_name, const pINode &expr) {
  Scope *scope = dynamic_cast<Scope *>(current_scope.get());
  Symtab::iterator it = scope->maybeInsertSymbol(var_name);
  pINode var_ptr = std::make_unique<VarNode>(it);
  return std::make_unique<AssignNode>(std::move(var_ptr), expr.get());
}

int AssignNode::calc() const {
  int expr_val = expr_->calc();
  VarNode *vp = dynamic_cast<VarNode *>(var_.get());
  vp->assign(expr_val);
  return expr_val;
}

void AssignNode::dump(std::ostream &os) const {
  os << current_indent << "AssignOperator\n";

  dump_helpers::increaseIndent();
  var_->dump(os);
  expr_->dump(os);
  dump_helpers::resetIndent();
}

} // namespace ast
