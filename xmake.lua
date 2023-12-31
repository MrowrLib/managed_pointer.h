add_rules("mode.debug", "mode.releasedbg", "mode.release")

set_languages("c++14")

target("managed_pointer")
    set_kind("headeronly")
    add_includedirs("include", { public = true })

target("Example")
    set_kind("binary")
    add_files("Example.cpp")
    add_deps("managed_pointer")
