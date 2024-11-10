#include "node.hh"

namespace ast {

INode* makeValue(IntT val) {
  // TODO
}

INode* makeUnOp(INode* n, UnOp op) {
  // TODO
}

INode* makeBinOp(INode* left, BinOp op, INode* right) {
  // TODO
}

INode* makeIf(INode* op, INode* sc) {
  // TODO
}

INode* makeWhile(INode* op, INode* sc) {
  // TODO
}

IScope* makeScope(IScope* par) {
  // TODO
}

}
