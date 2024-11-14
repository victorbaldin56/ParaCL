#ifndef PARACL_AST_VAR_NODE_HH_
#define PARACL_AST_VAR_NODE_HH_

#include "inode.hh"

namespace ast {

class VarNode : public INode {
 private:
  std::string name_;

 public:
  VarNode(const std::string& name) : name_(name) {}

  IntT calc() const override;
};

} // namespace ast

#endif // PARACL_AST_VAR_NODE_HH_
