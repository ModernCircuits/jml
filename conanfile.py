# SPDX-License-Identifier: BSL-1.0

import re
import os

from conan import ConanFile
from conan.tools.files import load

required_conan_version = ">=1.50.0"


class ModernCircuitsJML(ConanFile):
    name = "jml"
    url = "https://github.com/ModernCircuits/jml"
    description = "JUCE Meets Lua"
    license = "BSL-1.0"
    settings = "os", "compiler", "build_type", "arch"
    generators = "cmake_find_package", "markdown"

    def set_version(self):
        path = os.path.join(self.recipe_folder, "CMakeLists.txt")
        content = load(self, path)
        regex = r"project\([^\)]+VERSION (\d+\.\d+\.\d+)[^\)]*\)"
        ver = re.search(regex, content).group(1)
        self.version = ver.strip()

    def requirements(self):
        self.requires("mc-core/0.13.0@modern-circuits/stable")
        self.requires("cli11/2.2.0")
        self.requires("sml/1.1.6")
        self.requires("sol2/3.2.3")

    def config_options(self):
        self.options["lua"].compile_as_cpp = True

    def imports(self):
        self.copy("license*", dst="licenses", folder=True, ignore_case=True)
