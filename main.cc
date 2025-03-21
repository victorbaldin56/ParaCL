#include <cstdlib>
#include <iostream>

#include "parser/color_output.hh"
#include "interpreter/interpreter.hh"

int main(int argc, char** argv) try {
  interpreter::CmdParser parser(argc, argv);
  interpreter::Interpreter interp(parser.run());
  if (!interp.run()) {
    return EXIT_FAILURE;
  }
  return 0;
} catch (std::exception& ex) {
  std::cerr << ex.what() << std::endl;
  return EXIT_FAILURE;
}
