#include "ast/if_node.hh"

#include "ast/dump_helpers.hh"

namespace ast {

pINode makeIf(const pINode& op,
              const pINode& sc) {
  return std::make_shared<IfNode>(op, sc);
}

pINode makeElseIf(const pINode& op, const pINode& sc) {
  return std::make_shared<ElseIfNode>(op, sc);
}

pINode makeElse(const pINode& sc) {
  return std::make_shared<ElseNode>(sc);
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

  dump_helpers::resetIndent();
}

void ElseIfNode::dump(std::ostream& os) const {
  os << current_indent << "ElseIf\n";

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

void ElseNode::dump(std::ostream& os) const {
  os << current_indent << "Else\n";

  dump_helpers::increaseIndent();
  stm_->dump(os);
  dump_helpers::resetIndent();
}

} // namespace ast
