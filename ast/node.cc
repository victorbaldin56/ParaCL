#include "node.hh"

namespace ast {

Scope::~Scope() {
  for (INode* p : stms_) {
    delete p;
  }
}

INode* makeValue(IntT val) {
  return new ValueNode(val);
}

INode* makeUnOp(INode* n, UnOp op) {
  return new UnOpNode(n, op);
}

INode* makeBinOp(INode* left, BinOp op, INode* right) {
  return new BinOpNode(left, op, right);
}

INode* makeIf(INode* op, INode* sc) {

}

INode* makeWhile(INode* op, INode* sc) {
  // TODO
}

INode* makeVar(const std::string& name) {
  // TODO
}

INode* makePrint(INode* n) {
  // TODO
}

INode* makeScan(INode* n) {
  // TODO
}

IScope* makeScope(IScope* par) {
  // TODO
}

}
