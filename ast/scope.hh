#ifndef PARACL_AST_NODE_HH_
#define PARACL_AST_NODE_HH_

#include <vector>

#include "inode.hh"

namespace ast {

class Scope : public IScope {
 private:
  std::vector<INode*> stms_;
  IScope* parent_;

 public:
  Scope(IScope* parent) noexcept : parent_(parent) {}
  ~Scope() override;

  IScope* parentScope() const override { return parent_; }
  void push(INode* node) override { stms_.push_back(node); }
};

} // namespace ast

#endif // PARACL_AST_NODE_HH_
