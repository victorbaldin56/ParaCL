#include <cstdlib>
#include <iostream>

#include "interpreter/interpreter.hh"

int main(int argc, char** argv) try {
  interpreter::CmdParser parser(argc, argv);
  interpreter::Interpreter interp(parser.run());
  interp.run();
  return 0;
} catch (std::runtime_error& ex) {
  std::cerr << ex.what() << "\n";
  return EXIT_FAILURE;
}
