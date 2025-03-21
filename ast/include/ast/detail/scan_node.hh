#pragma once

#include "ast/inode.hh"
#include "var_node.hh"

namespace ast {

class ScanNode : public INode {
 private:
  // nothing here

 public:
  explicit ScanNode() noexcept {}

  int calc() const override;
  void dump(std::ostream& os) const override;
};

} // namespace ast
