#include <lua_juce_bindings/lua_juce_bindings.hpp>

static auto runTestScript(juce::ArgumentList const& args) -> void
{
    args.checkMinNumArguments(2);
    jassert(args.containsOption("unit-test"));

    auto state = sol::state{};
    state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
    mc::addLuaJuceModules(state);

    auto const scriptFile = args[1].resolveAsExistingFile();
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

    auto snapShotFile = juce::File{R"(C:\Developer\moderncircuits\tests\juce-lua\pic.png)"};
    if (snapShotFile.existsAsFile()) { snapShotFile.deleteFile(); }
    auto out = snapShotFile.createOutputStream();

    auto jpg = juce::PNGImageFormat{};
    jpg.writeImageToStream(snapshot, *out);
}

auto main(int argc, char* argv[]) -> int
{
    auto init = juce::ScopedJuceInitialiser_GUI{};
    auto app  = juce::ConsoleApplication{};

    app.addHelpCommand("help", "Usage:", true);
    app.addVersionCommand("version", "jml-cli version 0.1.0");
    app.addCommand({
        .commandOption       = "test",
        .argumentDescription = "test script.lua",
        .command             = runTestScript,
    });
    app.addCommand({
        .commandOption       = "snapshot",
        .argumentDescription = "snapshot script.lua",
        .command             = runTestScript,
    });

    return app.findAndRunCommand(argc, argv);
}
