#include "ast/while_node.hh"

namespace ast {

pINode makeWhile(const pINode& op, const pINode& sc) {
  return std::make_shared<WhileNode>(op, sc);
}

IntT WhileNode::calc() const {
  while (cond_->calc()) {
    stm_->calc();
  }
  return 0;
}

} // namespace ast
