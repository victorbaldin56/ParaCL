#pragma once

#include <vector>

#include "inode.hh"
#include "symtab.hh"

namespace ast {

class Scope : public IScope {
 private:
  std::vector<pINode> stms_;
  pIScope parent_;

  Symtab symtab_;

 public:
  explicit Scope(const pIScope& parent) noexcept : parent_(parent) {}

  int calc() const override;
  void dump(std::ostream& os) const override;

  pIScope parentScope() const override { return parent_; }
  void push(const pINode& node) override { stms_.push_back(node); }

  using ItNBool = std::pair<Symtab::iterator, bool>;

  ItNBool getLocalSymbol(const std::string& name) {
    ItNBool ret;
    ret.first = symtab_.find(name);
    ret.second = (ret.first != symtab_.end());
    return ret;
  }

  ItNBool getSymbol(const std::string& name);

  Symtab::iterator insertSymbol(const std::string& name) {
    return symtab_.insert({name, {}}).first;
  }

  Symtab::iterator maybeInsertSymbol(const std::string& name) {
    ItNBool it_n_bool = getSymbol(name);

    if (!it_n_bool.second) {
      it_n_bool.first = insertSymbol(name);
    }
    return it_n_bool.first;
  }
};

} // namespace ast
