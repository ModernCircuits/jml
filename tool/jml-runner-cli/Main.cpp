#include <lua_juce_bindings/lua_juce_bindings.hpp>

auto main(int argc, char* argv[]) -> int
{
    if (argc != 2) { return EXIT_FAILURE; }

    auto state = sol::state{};
    state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
    mc::addLuaJuceModules(state);

    auto script = state.load_file(argv[1]);
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

    return EXIT_SUCCESS;
}
