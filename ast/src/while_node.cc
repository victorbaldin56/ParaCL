#include "ast/while_node.hh"

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

}

} // namespace ast
