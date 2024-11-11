#ifndef PARACL_AST_INODE_HH_
#define PARACL_AST_INODE_HH_

#include <string>

namespace ast {

// built-in numeric types in ParaCL
using IntT = int;

class INode {
 public:
  virtual IntT calc() const = 0;
  virtual ~INode() {}
};

class IScope : public INode {
 public:
  virtual void push(const INode* node) = 0;
  virtual IScope* parentScope() const = 0;
};

enum class BinOp {
  kAdd,
  kSub,
  kMul,
  kDiv,
  kMod,
  kAssign,

  kIsEq,
  kIsNe,
  kIsLt,
  kIsLe,
  kIsGt,
  kIsGe,
};

enum class UnOp {
  kPlus,
  kMinus,
};

// create concrete nodes
INode*  makeValue(IntT val);
INode*  makeUnOp (INode* n, UnOp op);
INode*  makeBinOp(INode* left, BinOp op, INode* right);
INode*  makeWhile(INode* op, INode* sc);
INode*  makeIf   (INode* op, INode* sc);
INode*  makeVar  (const std::string& name);
IScope* makeScope(INode* par = nullptr);

}

extern ast::IScope* current_scope;

#endif // PARACL_AST_INODE_HH_
