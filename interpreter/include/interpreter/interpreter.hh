#pragma once

#include "cmd_parser.hh"

namespace interpreter {

class Interpreter final {
  Config cfg_;

 public:
  Interpreter(Config cfg) : cfg_(cfg) {}
  bool run();
};

} // namespace interpreter
