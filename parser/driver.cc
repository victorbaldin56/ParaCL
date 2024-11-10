#include "driver.hh"

#include <stdexcept>

ast::IScope* current_scope = nullptr;

namespace yy {

PDriver::PDriver(const std::string& input_file_name)
    : input_file_name_(input_file_name), plex_(new PLexer) {
  input_stream_.open(input_file_name, std::ios_base::in);
  if (!input_stream_.is_open()) {
    std::string what = "Failed to open file " + input_file_name_;
    throw std::runtime_error(what);
  }

  plex_->switch_streams(input_stream_, std::cout);
}

} // namespace yy
