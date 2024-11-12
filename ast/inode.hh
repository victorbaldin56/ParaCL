#ifndef PARACL_AST_INODE_HH_
#define PARACL_AST_INODE_HH_

#include <memory>
#include <string>

namespace ast {

/**
 * Built-in numeric types in ParaCL
 */
using IntT = int;

class INode;
class IScope;

using pINode = std::shared_ptr<INode>;
using pIScope = std::shared_ptr<IScope>;

class INode {
 public:
  virtual IntT calc() const = 0;
  virtual ~INode() {}
};

class IScope : public INode {
 public:
  // TODO: стоит ли здесь делать виртуальные методы, обе операции
  // тривиальны и хорошо инлайнятся?
  virtual void push(const pINode& node) = 0;
  virtual pIScope parentScope() const = 0;
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
pINode  makeValue(IntT val);
pINode  makeUnOp (const pINode& n, UnOp op);
pINode  makeBinOp(const pINode& left, BinOp op, const pINode& right);
pINode  makeWhile(const pINode& op, const pINode& sc);
pINode  makeIf   (const pINode& op, const pINode& sc);
pINode  makeVar  (const std::string& name);
pINode  makePrint(const pINode& n);
pINode  makeScan (const pINode& n);
pIScope makeScope(const pIScope& par = nullptr);

} // namespace ast

/**
 * Global context for interpreter.
 */
extern ast::pIScope current_scope;

#endif // PARACL_AST_INODE_HH_
