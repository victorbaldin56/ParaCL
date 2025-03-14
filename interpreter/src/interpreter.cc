#include "interpreter/interpreter.hh"

#include <stdexcept>

#include "parser/driver.hh"

namespace interpreter {

void Interpreter::run() {
  // no work to be done
  yy::PDriver driver(cfg_.filename_);
  ast::current_scope = ast::makeScope();

  if (!driver.parse()) {
    throw std::runtime_error("Execution terminated due to errors.");
  }

  switch (cfg_.action_) {
  case Config::ProgramAction::kExecute:
    ast::current_scope->calc();
    return;
  case Config::ProgramAction::kDumpAst:
    ast::current_scope->dump(std::cerr);
    return;
  default:
    assert(0 && "Unhandled Config::ProgramAction enum value");
  }
}

} // namespace interpreter
