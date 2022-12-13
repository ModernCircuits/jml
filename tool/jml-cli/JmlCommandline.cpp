#include "JmlCommandline.hpp"

namespace mc {

auto makeJmlCommandline() -> std::unique_ptr<JmlCommandline>
{
    auto cli = std::make_unique<JmlCommandline>();
    cli->app.add_flag("--verbose,-v", cli->verbose, "Print verbose output");

    auto* test = cli->app.add_subcommand("test", "Run test script");
    test->add_option("--script,-s", cli->scriptPath)->description("Path to lua script")->check(CLI::ExistingFile);

    auto* snapshot = cli->app.add_subcommand("snapshot", "Run snapshot script");
    snapshot->add_option("--script,-s", cli->scriptPath)->description("Path to lua script")->check(CLI::ExistingFile);

    return cli;
}

} // namespace mc
