#ifndef PARACL_AST_IF_NODE_HH_
#define PARACL_AST_IF_NODE_HH_

#include "inode.hh"

namespace ast {

class IfNode : public INode {
 private:
  INode* cond_;
  INode* stm_;

 public:
  IfNode(INode* cond, INode* stm) noexcept : cond_(cond), stm_(stm) {}

  ~IfNode() {
    delete cond_;
    delete stm_;
  }

  IntT calc() const override;
};

} // namespace ast

#endif // PARACL_AST_IF_NODE_HH_
