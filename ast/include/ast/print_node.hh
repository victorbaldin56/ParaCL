#pragma once

#include "inode.hh"

namespace ast {

class PrintNode : public INode {
private:
  pINode stm_;

 public:
  explicit PrintNode(const pINode& stm) noexcept : stm_(stm) {}

  IntT calc() const override;
};

} // namespace ast

