#pragma once

#include <string>

namespace interpreter {

struct Config {
  enum class ProgramAction {
    kExecute,
    kDumpAst,
  };

  bool help_flag_;
  std::string filename_;
  ProgramAction action_;
};

} // namespace interpreter
