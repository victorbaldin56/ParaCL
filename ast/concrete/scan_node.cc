#include "scan_node.hh"

#include <iostream>

#include "scope.hh"

namespace ast {

pINode makeScan(const std::string& var_name) {
  std::shared_ptr<Scope> scope
      = std::static_pointer_cast<Scope>(current_scope);
  Symtab::iterator it = scope->maybeInsertSymbol(var_name);
  pINode var_ptr = std::make_shared<VarNode>(it);
  return std::make_shared<ScanNode>(var_ptr);
}

IntT ScanNode::calc() const {
  std::shared_ptr<VarNode> vp = std::static_pointer_cast<VarNode>(var_);
  IntT tmp{};
  std::cin >> tmp;
  vp->assign(tmp);
  return 0;
}

} // namespace ast
