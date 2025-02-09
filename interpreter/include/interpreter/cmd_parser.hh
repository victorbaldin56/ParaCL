#pragma once

#include "boost/program_options.hpp"

#include "config.hh"

namespace po = boost::program_options;

namespace interpreter {

class CmdParser final {
  po::options_description desc_;
  po::variables_map var_map_;
  po::positional_options_description pos_desc_;
  po::command_line_parser parser_;

 public:
  CmdParser(int argc, const char* const* argv);
  Config run();
};

} // namespace interpreter
