/**
 * @file
 * Contains classes that introduce virtual AST interface.
 */
#pragma once

#include <memory>
#include <stdexcept>
#include <string>

#include "llvm/IR/Value.h"

namespace ast {

/**
 * @defgroup ParaCLTypes Basic types in ParaCL
 * @{
 */

/** just `int` */
using IntT = int;

/** @} */

class INode;
class IScope;

using pINode = std::shared_ptr<INode>;
using pIScope = std::shared_ptr<IScope>;

/**
 * Generalized Node of AST.
 */
class INode {
 public:
  virtual IntT calc() const = 0;
  virtual std::shared_ptr<llvm::Value> codegen() const = 0;
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
};

/**
 * Unary operations.
 */
enum class UnOp {
  kPlus,
  kMinus,
  kNot,
};

/**
 * @defgroup NodeCreators
 * Allocate concrete nodes and return pointer.
 * @{
 */

pINode  makeValue (IntT val);
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

/** @} */

extern pIScope current_scope;

} // namespace ast
