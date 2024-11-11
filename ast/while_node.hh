#ifndef PARACL_AST_WHILE_NODE_HH_
#define PARACL_AST_WHILE_NODE_HH_

#include "inode.hh"

namespace ast {

class WhileNode : public INode {
 private:
  INode* cond_;
  INode* stm_;

 public:
  WhileNode(INode* cond, INode* stm) noexcept : cond_(cond), stm_(stm) {}

  ~WhileNode() {
    delete cond_;
    delete stm_;
  }

  IntT calc() const override;
};

} // namespace ast

#endif // PARACL_AST_WHILE_NODE_HH_
