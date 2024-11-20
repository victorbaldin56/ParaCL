#ifndef PARACL_AST_SCAN_NODE_HH_
#define PARACL_AST_SCAN_NODE_HH_

#include "inode.hh"
#include "var_node.hh"

namespace ast {

class ScanNode : public INode {
 private:
  pINode stm_;

 public:
  explicit ScanNode(const pINode& stm) noexcept : stm_(stm) {}

  IntT calc() const override;
};

} // namespace ast

#endif // PARACL_AST_SCAN_NODE_HH_
