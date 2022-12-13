#pragma once

#include "JmlCommandline.hpp"

namespace mc {

inline auto runSnapshotScript(JmlCommandline const& cli) -> int
{
    auto state = sol::state{};
    state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
    mc::addLuaJuceModules(state);

    auto const scriptFile = juce::File{cli.scriptPath};
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

    sol::object obj = result;
    auto* component = obj.as<juce::Component*>();
    if (component == nullptr) {
        juce::ConsoleApplication::fail("Failed to get juce::Component* from lua result\n", EXIT_FAILURE);
    }

    component->resized();
    auto snapshot = component->createComponentSnapshot(component->getBounds());

    auto snapShotFile = juce::File::getCurrentWorkingDirectory().getChildFile("snapshot.png");
    if (snapShotFile.existsAsFile()) { snapShotFile.deleteFile(); }
    auto out = snapShotFile.createOutputStream();

    auto jpg = juce::PNGImageFormat{};
    jpg.writeImageToStream(snapshot, *out);

    return EXIT_SUCCESS;
}

} // namespace mc
