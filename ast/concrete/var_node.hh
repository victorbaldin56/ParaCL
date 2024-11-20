#pragma once

#include "context.hh"
#include "inode.hh"
#include "symtab.hh"

namespace ast {

class VarNode : public INode {
 private:
  std::string name_;

 public:
  VarNode(const std::string& name) : name_(name) {}
  SymtabIt find() const { return symtab.find(name_); }
  const std::string& name() const { return name_; }

  IntT calc() const override;
};

} // namespace ast
