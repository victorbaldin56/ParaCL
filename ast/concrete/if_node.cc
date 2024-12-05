#include "if_node.hh"

namespace ast {

pINode makeIf(const pINode& op,
              const pINode& sc,
              const pINode& else_sc) {
  return std::make_shared<IfNode>(op, sc, else_sc);
}

IntT IfNode::calc() const {
  if (cond_->calc()) {
    stm_->calc();
  } else {
    if (else_stm_) {
      else_stm_->calc();
    }
  }
  return 0;
}

} // namespace ast
