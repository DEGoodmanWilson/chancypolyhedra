from conans import ConanFile, CMake


class ChanPolyConan(ConanFile):
    name = "chancypolyhedra"
    version = "0.1.0"
    url = "https://github.com/DEGoodmanWilson/chancypolyhedra.git"
    license = "MIT"
    settings = "os", "compiler", "build_type", "arch"
    options = {"build_shared_libs": [True, False],
               "build_chancypolyhedra_tests": [True, False],
               "build_chancypolyhedra_coverage": [True, False],
               "build_chancypolyhedra_api": [True, False]}
    default_options = "build_shared_libs=False", "build_chancypolyhedra_tests=False", "build_chancypolyhedra_coverage=False", "build_chancypolyhedra_api=False"
    requires = "PEGTL/2.0.0@DEGoodmanWilson/testing"
    generators = "cmake"
    exports = ["*"]

    def configure(self):
        if self.options.build_chancypolyhedra_coverage:
            self.options.build_chancypolyhedra_tests = True

    def requirements(self):
        if self.options.build_chancypolyhedra_tests:
            self.requires.add("gtest/1.7.0@lasote/stable", private=False)
            self.options["gtest"].shared = False
        else:
            if "gtest" in self.requires:
                del self.requires["gtest"]

        if self.options.build_chancypolyhedra_api:
            self.requires.add("luna/3.0.0@DEGoodmanWilson/stable", private=False)
            self.requires.add("easyloggingpp/9.80@memsharded/testing", private=False)
            self.requires.add("nl-json/2.1.1@genvidtech/1.4.0", private=False)
        else:
            if "luna" in self.requires:
                del self.requires["luna"]
            if "easyloggingpp" in self.requires:
                del self.requires["easyloggingpp"]

    def build(self):
        cmake = CMake(self.settings)
        build_shared_libs = "-DBUILD_SHARED_LIBS=ON" if self.options.build_shared_libs else "-DBUILD_SHARED_LIBS=OFF"
        build_chancypolyhedra_tests = "-DBUILD_CHANCYPOLYHEDRA_TESTS=ON" if self.options.build_chancypolyhedra_tests else "-DBUILD_CHANCYPOLYHEDRA_TESTS=OFF"
        build_chancypolyhedra_coverage = "-DBUILD_CHANCYPOLYHEDRA_COVERAGE=ON" if self.options.build_chancypolyhedra_coverage else "-DBUILD_CHANCYPOLYHEDRA_COVERAGE=OFF"
        build_chancypolyhedra_api = "-DBUILD_CHANCYPOLYHEDRA_API=ON" if self.options.build_chancypolyhedra_api else "-DBUILD_CHANCYPOLYHEDRA_API=OFF"
        self.run('cmake %s %s %s %s "%s" %s' % (build_shared_libs, build_chancypolyhedra_tests, build_chancypolyhedra_coverage, build_chancypolyhedra_api, self.conanfile_directory, cmake.command_line))
        self.run('cmake --build . %s' % cmake.build_config)

    def package(self):
        self.copy("*.h", dst="include/chancypolyhedra", src="chancypolyhedra")
        self.copy("*.lib", dst="lib", src="lib")
        self.copy("*.a", dst="lib", src="lib")

    def package_info(self):
        self.cpp_info.libs = ["chancypolyhedra"]
