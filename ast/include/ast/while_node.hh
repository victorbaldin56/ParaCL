#pragma once

#include "inode.hh"

namespace ast {

class WhileNode : public INode {
 private:
  pINode cond_;
  pINode stm_;

 public:
  WhileNode(const pINode& cond, const pINode& stm) noexcept
      : cond_(cond), stm_(stm) {}

  IntT calc() const override;
};

} // namespace ast

