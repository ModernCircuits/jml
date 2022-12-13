#include "JmlCommandline.hpp"

#include "Command/Snapshot.hpp"
#include "Command/Test.hpp"

#include <lua_juce_bindings/lua_juce_bindings.hpp>

auto main(int argc, char* argv[]) -> int
{
    auto init = juce::ScopedJuceInitialiser_GUI{};

    auto cli = mc::makeJmlCommandline();
    CLI11_PARSE(cli->app, argc, argv);

    if (cli->app.got_subcommand("test")) { return mc::runTestScript(*cli); }
    if (cli->app.got_subcommand("snapshot")) { return mc::runSnapshotScript(*cli); }
    return EXIT_SUCCESS;
}
