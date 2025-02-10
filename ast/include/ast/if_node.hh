#pragma once

#include "inode.hh"

namespace ast {

class IfNode : public INode {
 protected:
  pINode cond_;
  pINode stm_;
  pINode else_stm_;

 public:
  IfNode(pINode cond, pINode stm, pINode else_stm) noexcept
      : cond_(cond), stm_(stm), else_stm_(else_stm) {}
  int calc() const override;
  void dump(std::ostream& os) const override;
};

class ElseIfNode : public IfNode {
 public:
  ElseIfNode(pINode cond, pINode stm) noexcept : IfNode(cond, stm) {}
  void dump(std::ostream& os) const override;
};

class ElseNode : public INode {
  pINode stm_;

 public:
  ElseNode(pINode stm) noexcept : stm_(stm) {}
  int calc() const override { return stm_->calc(); }
  void dump(std::ostream& os) const override;
};

} // namespace ast
