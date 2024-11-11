#ifndef PARACL_AST_SCAN_NODE_HH_
#define PARACL_AST_SCAN_NODE_HH_

#include "inode.hh"

namespace ast {

class ScanNode : public INode {
 private:
  INode* stm_;

 public:
  explicit ScanNode(INode* stm) noexcept : stm_(stm) {}
  ~ScanNode() override { delete stm_; }

  IntT calc() const override;
};

} // namespace ast

#endif // PARACL_AST_SCAN_NODE_HH_
