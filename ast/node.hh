/**
 * Concrete nodes implementation.
 */
#ifndef PARACL_AST_NODE_HH_
#define PARACL_AST_NODE_HH_

#include <cassert>
#include <vector>

#include "inode.hh"

namespace ast {

/**
 * Contains constant value.
 */
class ValueNode : public INode {
 private:
  IntT value_;

 public:
  explicit ValueNode(IntT val) noexcept : value_(val) {}

  IntT calc() const noexcept override { return value_; }
};

/**
 * Holds unary operation.
 */
class UnOpNode : public INode {
 private:
  INode* ch_;
  UnOp op_;

 public:
  UnOpNode(INode* ch, UnOp op) noexcept : ch_(ch), op_(op) {}
  ~UnOpNode() override { delete ch_; }

  IntT calc() const override;
};

class BinOpNode : public INode {
 private:
  INode* left_;
  INode* right_;
  BinOp op_;

 public:
  BinOpNode(INode* left, BinOp op, INode* right) noexcept
      : left_(left), op_(op), right_(right) {}

  ~BinOpNode() override {
    delete left_;
    delete right_;
  }

  IntT calc() const override;
};

class WhileNode : public INode {
 private:
  INode* cond_;
  INode* stm_;

 public:
  WhileNode(INode* cond, INode* stm) noexcept : cond_(cond), stm_(stm) {}

  ~WhileNode() {
    delete cond_;
    delete stm_;
  }

  IntT calc() const override;
};

class IfNode : public INode {

};
class VarNode : public INode {

};

class PrintNode : public INode {

};

class ScanNode : public INode {

};

class Scope : public IScope {
 private:
  std::vector<INode*> stms_;
  IScope* parent_;

 public:
  Scope(IScope* parent) noexcept : parent_(parent) {}
  ~Scope() override;

  IScope* parentScope() const override { return parent_; }

};

}

#endif // PARACL_AST_NODE_HH_
