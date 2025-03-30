#include "ast/detail/if_node.hh"

#include "ast/detail/dump_helpers.hh"

namespace ast {

pINode makeIf(const pINode& op,
              const pINode& sc,
              const pINode& else_sc) {
  return std::make_unique<IfNode>(op.get(), sc.get(), else_sc.get());
}

int IfNode::calc() const {
  if (cond_->calc()) {
    stm_->calc();
  } else {
    if (else_stm_) {
      else_stm_->calc();
    }
  }
  return 0;
}

void IfNode::dump(std::ostream& os) const {
  os << current_indent << "If\n";

  dump_helpers::increaseIndent();

  os << current_indent << "Condition\n";
  dump_helpers::increaseIndent();
  cond_->dump(os);
  dump_helpers::resetIndent();

  os << current_indent << "Body\n";
  dump_helpers::increaseIndent();
  stm_->dump(os);
  dump_helpers::resetIndent();

  if (else_stm_) {
    os << current_indent << "Else\n";
    dump_helpers::increaseIndent();
    else_stm_->dump(os);
    dump_helpers::resetIndent();
  }

  dump_helpers::resetIndent();
}

} // namespace ast
