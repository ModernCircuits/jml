#include <lua_juce_bindings/lua_juce_bindings.hpp>

auto main(int argc, char* argv[]) -> int
{
    auto init = juce::ScopedJuceInitialiser_GUI{};

    if (argc != 2) { return EXIT_FAILURE; }

    auto state = sol::state{};
    state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
    mc::addLuaJuceModules(state);

    auto const scriptFile = juce::File{argv[1]};
    if (not scriptFile.existsAsFile()) {
        std::cerr << "Script file does not exist: " << argv[1] << '\n';
        return EXIT_FAILURE;
    }

    scriptFile.getParentDirectory().setAsCurrentWorkingDirectory();
    auto script = state.load_file(scriptFile.getFullPathName().toStdString());
    if (not script.valid()) {
        sol::error error = script;
        std::cerr << "Load error:" << error.what() << '\n';
        return EXIT_FAILURE;
    }

    auto factory = script.get<sol::protected_function>();
    auto result  = factory();
    if (not result.valid()) {
        sol::error error = result;
        std::cerr << "Run error:" << error.what() << '\n';
        return EXIT_FAILURE;
    }

    sol::object obj = result;
    auto* component = obj.as<juce::Component*>();
    if (component == nullptr) {
        std::cerr << "Failed to get juce::Component* from lua result\n";
        return EXIT_FAILURE;
    }

    component->resized();
    auto snapshot = component->createComponentSnapshot(component->getBounds());

    auto snapShotFile = juce::File{R"(C:\Developer\moderncircuits\tests\juce-lua\pic.png)"};
    if (snapShotFile.existsAsFile()) { snapShotFile.deleteFile(); }
    auto out = snapShotFile.createOutputStream();

    auto jpg = juce::PNGImageFormat{};
    jpg.writeImageToStream(snapshot, *out);

    return EXIT_SUCCESS;
}
