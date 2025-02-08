#include "ast/if_node.hh"

namespace ast {

pINode makeIf(const pINode& op,
              const pINode& sc,
              const pINode& else_sc) {
  return std::make_shared<IfNode>(op, sc, else_sc);
}

int IfNode::calc() const {
  int cond = cond_->calc();
  if (cond) {
    stm_->calc();
  }
  return cond;
}

} // namespace ast
