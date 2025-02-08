#pragma once

#include "inode.hh"

namespace ast {

class PrintNode : public INode {
private:
  pINode stm_;

 public:
  explicit PrintNode(const pINode& stm) noexcept : stm_(stm) {}

  int calc() const override;
  void dump(std::ostream& os) const override;
};

} // namespace ast
