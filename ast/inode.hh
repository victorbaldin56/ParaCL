#ifndef PARACL_AST_INODE_HH_
#define PARACL_AST_INODE_HH_

namespace ast {

using IntT = int;

class INode {
 public:
  virtual ~INode() {}
};

class IScope : public INode {
 public:

};

}

#endif // PARACL_AST_INODE_HH_
