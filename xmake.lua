set_project("MyApp")
set_version("1.0.0")

add_rules("mode.debug", "mode.release")

add_requires("sqlitecpp")

target("App")
    set_kind("binary")
    add_files("src/main.cpp")  
    add_includedirs("lib")     
    add_packages("sqlitecpp")