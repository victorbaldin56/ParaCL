#ifndef PARACL_AST_INODE_HH_
#define PARACL_AST_INODE_HH_

namespace ast {

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

}

extern ast::IScope* current_scope;

#endif // PARACL_AST_INODE_HH_
