#include <cassert>

#include "unop_node.hh"

namespace ast {

pINode makeUnOp(const pINode& n, UnOp op) {
  return std::make_shared<UnOpNode>(n, op);
}

IntT UnOpNode::calc() const {

}

} // namespace ast
