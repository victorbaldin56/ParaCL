/**
 * @file
 * Contains classes that introduce virtual AST interface.
 */
#pragma once

#include <memory>
#include <stdexcept>
#include <string>

namespace ast {

class INode;
class IScope;

using pINode = std::shared_ptr<INode>;
using pIScope = std::shared_ptr<IScope>;

/**
 * Generalized Node of AST.
 */
class INode {
 public:
  virtual int calc() const = 0;
  virtual ~INode() {}
};

/**
 * Scope interface, is also Node.
 */
class IScope : public INode {
 public:
  virtual void push(const pINode& node) = 0;
  virtual pIScope parentScope() const = 0;
};

/**
 * Binary operations.
 */
enum class BinOp {
  kAdd,
  kSub,
  kMul,
  kDiv,
  kMod,

  kIsEq,
  kIsNe,
  kIsLt,
  kIsLe,
  kIsGt,
  kIsGe,

  kAnd,
  kOr,

  kBtwAnd,
  kBtwOr,
  kXor,

  kShl,
  kShr,
};

/**
 * Unary operations.
 */
enum class UnOp {
  kPlus,
  kMinus,
  kNot,
  kBtwNot,
  kPreIncr,
  kPostIncr,
  kPreDecr,
  kPostDecr,
};

/**
 * @defgroup NodeCreators
 * Allocate concrete nodes and return pointer.
 * @{
 */

pINode  makeValue (int val);
pINode  makeUnOp  (const pINode& n, UnOp op);
pINode  makeBinOp (const pINode& left, BinOp op, const pINode& right);
pINode  makeWhile (const pINode& op, const pINode& sc);
pINode  makeIf    (const pINode& op,
                   const pINode& sc,
                   const pINode& else_sc = nullptr);
pINode  makeVar   (const std::string& name);
pINode  makePrint (const pINode& n);
pINode  makeScan  ();
pINode  makeAssign(const std::string& var_name, const pINode& rhs);

pIScope makeScope(const pIScope& par = nullptr);
pIScope makeIfScope(const pIScope& par = nullptr);

/** @} */

extern pIScope current_scope;

} // namespace ast
