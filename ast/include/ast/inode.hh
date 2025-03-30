/**
 * @file
 * Contains classes that introduce virtual AST interface.
 */
#pragma once

#include <algorithm>
#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>

namespace ast {

constexpr char kDumpIndent[] = "  ";

class INode;
class IScope;

using pINode = std::unique_ptr<INode>;
using pIScope = std::unique_ptr<IScope>;

/**
 * Generalized Node of AST.
 */
class INode {
 public:
  virtual int calc() const = 0;
  virtual void dump(std::ostream& os) const = 0;
  virtual ~INode() {}
};

/**
 * Scope interface, is also Node.
 */
class IScope : public INode {
 public:
  virtual void push(pINode& node) = 0;
  virtual IScope* parentScope() const = 0;
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
pIScope makeScope(IScope* par);

/** @} */

extern pIScope current_scope;
extern std::string current_indent; // for dump

} // namespace ast
