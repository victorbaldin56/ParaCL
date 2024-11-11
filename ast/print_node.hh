#ifndef PARACL_AST_PRINT_NODE_HH_
#define PARACL_AST_PRINT_NODE_HH_

#include "inode.hh"

namespace ast {

class PrintNode : public INode {
private:
  INode* stm_;

 public:
  explicit PrintNode(INode* stm) noexcept : stm_(stm) {}
  ~PrintNode() override { delete stm_; }

  IntT calc() const override;
};

} // namespace ast

#endif // PARACL_AST_PRINT_NODE_HH_
