#pragma once

#include "ast/inode.hh"

namespace ast {

class PrintNode : public INode {
private:
  INode* stm_;

 public:
  explicit PrintNode(INode* stm) noexcept : stm_(stm) {}

  int calc() const override;
  void dump(std::ostream& os) const override;
};

} // namespace ast
