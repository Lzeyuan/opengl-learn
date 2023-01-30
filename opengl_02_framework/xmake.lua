add_rules("mode.debug", "mode.release")

set_version("1.0.0")
set_languages("c11", "c++14")

add_requires("glfw")
target("framework")
    set_kind("binary")
    set_basename("framework_$(mode)_$(arch)")
    add_files("src/*.cpp", "src/*.c")
    add_includedirs("include")
    add_packages("glfw")
    set_rundir("$(projectdir)")