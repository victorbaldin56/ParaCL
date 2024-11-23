#include <cstdlib>
#include <iostream>

#include <boost/program_options.hpp>

#include "driver.hh"

namespace po = boost::program_options;

int main(int argc, char** argv) {
  try {
    po::options_description desc("Options");
    desc.add_options()
      ("help,h", "Print help message")
      ("source", po::value<std::string>(), "source file");

    po::positional_options_description pos_desc;
    pos_desc.add("source", -1);

    po::command_line_parser parser(argc, argv);
    parser.options(desc).positional(pos_desc).allow_unregistered();
    po::parsed_options parsed_opts = parser.run();

    po::variables_map var_map;
    po::store(parsed_opts, var_map);
    po::notify(var_map);

    if (var_map.count("help")) {
      std::cout << desc << "\n";
      return 0;
    }

    if (var_map.count("source")) {
      std::string filename = var_map["source"].as<std::string>();

      yy::PDriver driver(filename);
      ast::current_scope = ast::makeScope();

      if (!driver.parse()) {
        return EXIT_FAILURE;
      }

      ast::current_scope->calc();
    }
  } catch (po::error& ex) {
    std::cerr << ex.what() << "\n";
    return EXIT_FAILURE;
  } catch (std::runtime_error& ex) {
    std::cerr << ex.what() << "\n";
    return EXIT_FAILURE;
  }

  return 0;
}
