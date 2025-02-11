#include "ast/while_node.hh"

#include "ast/dump_helpers.hh"

namespace ast {

pINode makeWhile(const pINode& op, const pINode& sc) {
  return std::make_shared<WhileNode>(op, sc);
}

int WhileNode::calc() const {
  while (cond_->calc()) {
    stm_->calc();
  }
  return 0;
}

void WhileNode::dump(std::ostream& os) const {
  os << current_indent << "While\n";

  dump_helpers::increaseIndent();

  os << current_indent << "Condition\n";
  dump_helpers::increaseIndent();
  cond_->dump(os);
  dump_helpers::resetIndent();

  os << current_indent << "Body\n";
  dump_helpers::increaseIndent();
  stm_->dump(os);
  dump_helpers::resetIndent();

  dump_helpers::resetIndent();
}

llvm::Value* WhileNode::codegen() const {

}

} // namespace ast
