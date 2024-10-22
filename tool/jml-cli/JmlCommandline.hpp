#pragma once

#include <mc_lua_juce/mc_lua_juce.hpp>

JUCE_BEGIN_IGNORE_WARNINGS_GCC_LIKE("-Wimplicit-int-float-conversion")
#include <CLI/CLI.hpp>
JUCE_END_IGNORE_WARNINGS_GCC_LIKE

namespace mc {

struct JmlCommandline
{
    // "root"
    CLI::App app{"jml-cli"};
    bool verbose{false};

    // "test"
    std::string scriptPath{};
};

[[nodiscard]] auto makeJmlCommandline() -> std::unique_ptr<JmlCommandline>;

} // namespace mc
