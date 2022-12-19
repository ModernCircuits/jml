#include "JmlCommandline.hpp"

#include "Command/Snapshot.hpp"
#include "Command/Test.hpp"

#include <mc_lua_juce/mc_lua_juce.hpp>

static auto run(auto const func, auto const& app) -> int
{
    if (auto const result = func(app); result.failed()) {
        std::cerr << result.getErrorMessage() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

auto main(int argc, char* argv[]) -> int
{
    auto init = juce::ScopedJuceInitialiser_GUI{};

    auto cli = mc::makeJmlCommandline();
    CLI11_PARSE(cli->app, argc, argv);

    if (cli->app.got_subcommand("test")) { return run(mc::runTestScript, *cli); }
    if (cli->app.got_subcommand("snapshot")) { return run(mc::runSnapshotScript, *cli); }
    return EXIT_SUCCESS;
}
