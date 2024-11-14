#ifndef PARACL_AST_NODE_HH_
#define PARACL_AST_NODE_HH_

#include <vector>

#include "inode.hh"
#include "symtab.hh"

namespace ast {

class Scope : public IScope {
 private:
  std::vector<pINode> stms_;
  pIScope parent_;

  Symtab symtab_;

 public:
  explicit Scope(const pIScope& parent) noexcept : parent_(parent) {}

  void calc() const override;

  pIScope parentScope() const override { return parent_; }
  void push(const pINode& node) override { stms_.push_back(node); }
};

} // namespace ast

#endif // PARACL_AST_NODE_HH_
