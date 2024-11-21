#include "var_node.hh"

#include <stdexcept>

namespace ast {

pINode makeVar(const std::string& name) {
  return std::make_shared<VarNode>(name);
}

IntT VarNode::calc() const {
  SymtabIt it = find();
  if (it == symtab.end()) {
    std::string what = "Undefined variable " + name_;
    throw std::runtime_error(what); // FIXME: на стадию парсинга
  }
  return it->second.value;
}

} // namespace ast
