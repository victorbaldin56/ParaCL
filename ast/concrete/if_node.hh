#pragma once

#include "inode.hh"

namespace ast {

class IfNode : public INode {
 private:
  pINode cond_;
  pINode stm_;

 public:
  IfNode(pINode cond, pINode stm) noexcept : cond_(cond), stm_(stm) {}

  IntT calc() const override;
};

} // namespace ast

