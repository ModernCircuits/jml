#include "Application.hpp"

namespace mc {

namespace {

struct MainWindow final : juce::DocumentWindow
{
    explicit MainWindow(juce::String const& name)
        : DocumentWindow(name, juce::Colours::black, DocumentWindow::allButtons)
    {
        setUsingNativeTitleBar(true);
        setContentOwned(new MainComponent(), true);
        setResizable(true, true);
        centreWithSize(getWidth(), getHeight());
        setVisible(true);
    }

    auto closeButtonPressed() -> void override
    {
        // This is called when the user tries to close this window. Here, we'll just
        // ask the app to quit when this happens, but you can change this to do
        // whatever you need.
        juce::JUCEApplication::getInstance()->systemRequestedQuit();
    }
};

} // namespace

auto Application::getApplicationName() -> const juce::String { return JUCE_APPLICATION_NAME_STRING; }

auto Application::getApplicationVersion() -> const juce::String { return JUCE_APPLICATION_VERSION_STRING; }

auto Application::moreThanOneInstanceAllowed() -> bool { return true; }

auto Application::initialise(juce::String const& commandLine) -> void
{
    // This method is where you should put your application's initialisation code..
    juce::ignoreUnused(commandLine);
    juce::LookAndFeel::setDefaultLookAndFeel(&_lnf);
    _mainWindow = std::make_unique<MainWindow>(getApplicationName());
}

auto Application::shutdown() -> void
{
    // Add your application's shutdown code here..
    _mainWindow = nullptr; // (deletes our window)
    juce::LookAndFeel::setDefaultLookAndFeel(nullptr);
}

auto Application::systemRequestedQuit() -> void
{
    // This is called when the app is being asked to quit: you can ignore this
    // request and let the app carry on running, or call quit() to allow the app to close.
    quit();
}

auto Application::anotherInstanceStarted(juce::String const& commandLine) -> void
{
    // When another instance of the app is launched while this one is running,
    // this method is invoked, and the commandLine parameter tells you what
    // the other instance's command-line arguments were.
    juce::ignoreUnused(commandLine);
}

} // namespace mc
