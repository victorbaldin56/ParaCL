#pragma once

#include "ast/inode.hh"

namespace ast {
namespace dump_helpers {

inline void increaseIndent() {
  current_indent += kDumpIndent;
}

inline void resetIndent() {
  current_indent.erase(current_indent.size() - sizeof(kDumpIndent) + 1);
}

} // namespace dump_helpers
} // namespace ast
