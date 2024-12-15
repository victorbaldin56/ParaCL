#pragma once

#include "inode.hh"
#include "var_node.hh"

namespace ast {

class ScanNode : public INode {
 private:
  // nothing here

 public:
  explicit ScanNode() noexcept {}

  IntT calc() const override;
};

} // namespace ast
