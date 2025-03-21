#pragma once

#include "ast/inode.hh"
#include "symtab.hh"

namespace ast {

class VarNode : public INode {
 private:
  Symtab::iterator it_;

 public:
  VarNode(Symtab::iterator it) : it_(it) {}

  int calc() const override { return it_->second.value; }
  void dump(std::ostream& os) const override;

  void assign(int val) { it_->second.value = val; }
  int preIncrement() { return ++it_->second.value; }
  int preDecrement() { return --it_->second.value; }

  int postIncrement() {
    int tmp = it_->second.value;
    ++it_->second.value;
    return tmp;
  }

  int postDecrement() {
    int tmp = it_->second.value;
    --it_->second.value;
    return tmp;
  }
};

} // namespace ast
