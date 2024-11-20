/**
 * Symtab implementation.
 */
#ifndef PARACL_AST_SYMTAB_HH_
#define PARACL_AST_SYMTAB_HH_

#include <unordered_map>

#include "inode.hh"

namespace ast {

struct SymtabItem {
  IntT value;
};

using Symtab = std::unordered_map<std::string, SymtabItem>;
using SymtabIt = Symtab::iterator;

}

#endif // PARACL_AST_SYMTAB_HH_
