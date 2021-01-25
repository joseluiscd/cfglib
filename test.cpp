#include "cfg.hpp"
#include <fmt/format.h>

struct Config {
    double a_float;
    std::string a_string;
    std::string other_string;
};

int main(int argc, char** argv)
{
    Config c;

    c.a_float = 2.0;
    c.a_string = "This is a test string";
    c.other_string = "This is the other test string";

    fmt::print("{}, {}, {}\n", c.a_float, c.a_string, c.other_string);

    // Write example
    cfg::write("config.toml")
        .begin_global_section()
        .add_value("a_float", c.a_float)
        .add_value("a_string", c.a_string)
        .end_section()

        .begin_section("other")
        .add_value("string", c.other_string)
        .end_section()
        .run();

    // Read example
    Config f;
    cfg::parse("config.toml")
        .begin_global_section()
        .add_value("a_float", f.a_float)
        .add_value("a_string", f.a_string)
        .end_section()

        .begin_section("other")
        .add_value("string", f.other_string)
        .end_section()
        .run();

    fmt::print("{}, {}, {}\n", f.a_float, f.a_string, f.other_string);
}