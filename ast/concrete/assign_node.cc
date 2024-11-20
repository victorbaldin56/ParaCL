#include "assign_node.hh"

#include "var_node.hh"

namespace ast {

pINode makeAssign(const pINode& var, const pINode& expr) {
  return std::make_shared<AssignNode>(var, expr);
}

IntT AssignNode::calc() const {
  IntT expr_val = expr_->calc();

  std::shared_ptr<VarNode> var_ptr = std::static_pointer_cast<VarNode>(var_);
  SymtabIt it = var_ptr->find();
  if (it == symtab.end()) {
    symtab.insert({var_ptr->name(), {expr_val}});
  }
  it->second.value = expr_val;
  return expr_val;
}

} // namespace ast
