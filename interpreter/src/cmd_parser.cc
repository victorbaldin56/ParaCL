#include "interpreter/cmd_parser.hh"

#include <iostream>

namespace interpreter {

CmdParser::CmdParser(int argc, const char* const* argv) : parser_(argc, argv) {
  desc_.add_options()
    ("help,h"  ,                           "Print help message")
    ("source"  , po::value<std::string>(), "Source file")
    ("ast-dump",                           "Dump AST in console");
  pos_desc_.add("source", -1);
  parser_.options(desc_).positional(pos_desc_).allow_unregistered();
}

Config CmdParser::run() {
  po::store(parser_.run(), var_map_);
  po::notify(var_map_);

  Config cfg;

  if (var_map_.count("help")) {
    std::cout << "Usage: pcl [options] [file] ...\n"
                 "Options:\n" << desc_;
    cfg.help_flag_ = true;
    return cfg;
  }

  if (var_map_.count("source")) {
    cfg.filename_ = var_map_["source"].as<std::string>();
  }

  if (var_map_.count("ast-dump")) {
    cfg.action_ = Config::ProgramAction::kDumpAst;
  } else {
    cfg.action_ = Config::ProgramAction::kExecute;
  }
  return cfg;
}

} // namespace interpreter
