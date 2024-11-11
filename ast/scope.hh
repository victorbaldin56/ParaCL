#ifndef PARACL_AST_NODE_HH_
#define PARACL_AST_NODE_HH_

#include <vector>

#include "inode.hh"
#include "symtab.hh"

namespace ast {

class Scope : public IScope {
 private:
  std::vector<INode*> stms_;
  IScope* parent_;

  Symtab symtab_;

 public:
  explicit Scope(IScope* parent) noexcept : parent_(parent) {}
  ~Scope() override;

  IntT calc() const override { return 0; }

  IScope* parentScope() const override { return parent_; }
  void push(INode* node) override { stms_.push_back(node); }
};

} // namespace ast

#endif // PARACL_AST_NODE_HH_
