from conan import ConanFile
from conan.tools.cmake import cmake_layout

class ParaCLRecipe(ConanFile):
  name = "paracl"
  version = "1.0"
  settings = "os", "compiler", "build_type", "arch"
  generators = "CMakeDeps", "CMakeToolchain"
  options = {"testing": [True, False]}
  default_options = {"testing": False}

  def requirements(self):
    self.requires("boost/1.86.0")
    if self.options.testing:
      self.test_requires("gtest/1.15.0")

  def layout(self):
    cmake_layout(self)
