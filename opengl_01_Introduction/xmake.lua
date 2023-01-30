add_rules("mode.debug", "mode.release")

add_requires("glfw")
set_languages("c11", "c++14")

target("opengl")
    set_kind("binary")
    set_basename("opengl_$(mode)_$(arch)")
    add_files("src/*.cpp", "src/*.c")
    add_includedirs("include")
    add_packages("glfw")
    set_rundir("$(projectdir)")