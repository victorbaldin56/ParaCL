#pragma once

#include "inode.hh"
#include "symtab.hh"

namespace ast {

class VarNode : public INode {
 private:
  Symtab::iterator it_;

 public:
  VarNode(Symtab::iterator it) : it_(it) {}

  int calc() const override { return it_->second.value; }

  void assign(int val) { it_->second.value = val; }
};

} // namespace ast
