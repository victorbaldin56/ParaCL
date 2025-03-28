/**
 * Symtab implementation.
 */
#pragma once

#include <unordered_map>

#include "ast/inode.hh"

namespace ast {

struct SymtabItem {
  int value;
};

using Symtab = std::unordered_map<std::string, SymtabItem>;

} // namespace ast
