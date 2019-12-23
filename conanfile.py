from conans import ConanFile, CMake, tools


class SIXDConan(ConanFile):
    name = "sixd"
    requires = (("yaml-cpp/0.6.2@bincrafters/stable"),
                ("eigen/3.3.7@conan/stable"),
                ("pngpp/0.2.9-1@richard-vock/stable"))
    version = "0.1"
    license = "unlicense"
    author = "Richard Vock vock@cs.uni-bonn.de"
    url = "https://github.com/richard-vock/sixd"
    description = "SIXD challenge dataset loading library"
    topics = ("RGBD", "dataset")
    settings = "os", "compiler", "build_type", "arch"
    options = {"shared": [True, False]}
    default_options = "shared=False"
    generators = "cmake"
    exports_sources = "include*", "src*", "CMakeLists.txt"

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def package(self):
        self.copy("include/*.hpp", dst="include/sixd", keep_path=False)
        self.copy("include/*.ipp", dst="include/sixd", keep_path=False)
        self.copy("*sixd.lib", dst="lib", keep_path=False)
        self.copy("*.dll", dst="bin", keep_path=False)
        self.copy("*.so", dst="lib", keep_path=False)
        self.copy("*.dylib", dst="lib", keep_path=False)
        self.copy("*.a", dst="lib", keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ["sixd", "stdc++fs"]

