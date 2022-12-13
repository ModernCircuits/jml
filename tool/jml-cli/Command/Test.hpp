#pragma once

#include "JmlCommandline.hpp"

namespace mc {
inline auto runTestScript(JmlCommandline const& cli) -> int
{
    auto state = sol::state{};
    state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
    mc::addLuaJuceModules(state);

    auto const scriptFile = juce::File{cli.scriptPath};
    if (cli.verbose) { std::cout << "Run test: " << scriptFile.getFileNameWithoutExtension().toStdString() << '\n'; }
    scriptFile.getParentDirectory().setAsCurrentWorkingDirectory();

    auto script = state.load_file(scriptFile.getFullPathName().toStdString());
    if (not script.valid()) {
        sol::error error = script;
        juce::ConsoleApplication::fail(error.what(), EXIT_FAILURE);
    }

    auto factory = script.get<sol::protected_function>();
    auto result  = factory();
    if (not result.valid()) {
        sol::error error = result;
        juce::ConsoleApplication::fail(error.what(), EXIT_FAILURE);
    }

    if (cli.verbose) { std::cout << "Done test: " << scriptFile.getFileNameWithoutExtension().toStdString() << '\n'; }
    return EXIT_SUCCESS;
}
} // namespace mc
