#include "interpreter/interpreter.hh"

#include <stdexcept>

#include "parser/driver.hh"

namespace interpreter {

bool Interpreter::run() {
  yy::PDriver driver(cfg_.filename_);
  ast::current_scope = ast::makeScope();

  if (!driver.parse()) {
    return false;
  }

  try {
    switch (cfg_.action_) {
    case Config::ProgramAction::kExecute:
      ast::current_scope->calc();
      return true;
    case Config::ProgramAction::kDumpAst:
      ast::current_scope->dump(std::cerr);
      return true;
    default:
      assert(0 && "Unhandled Config::ProgramAction enum value");
    }
  } catch (std::exception& ex) {
    std::cerr << ex.what() << std::endl;
    return false;
  }
}

} // namespace interpreter
