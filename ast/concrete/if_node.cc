#include "if_node.hh"

namespace ast {

pINode makeIf(const pINode& op, const pINode& sc) {
  return std::make_shared<IfNode>(op, sc);
}

IntT IfNode::calc() const {
  if (cond_) {
    stm_->calc();
  }
  return 0; // FIXME (?)
}

} // namespace ast
