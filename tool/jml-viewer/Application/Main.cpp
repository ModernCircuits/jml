#include <memory>

#include "Application/MainComponent.hpp"

struct GuiAppApplication final : juce::JUCEApplication
{

    GuiAppApplication() = default;

    auto getApplicationName() -> const juce::String override { return JUCE_APPLICATION_NAME_STRING; }
    auto getApplicationVersion() -> const juce::String override { return JUCE_APPLICATION_VERSION_STRING; }
    auto moreThanOneInstanceAllowed() -> bool override { return true; }

    auto initialise(juce::String const& commandLine) -> void override
    {
        juce::ignoreUnused(commandLine);
        _mainWindow = std::make_unique<MainWindow>(getApplicationName());
    }

    auto shutdown() -> void override { _mainWindow = nullptr; }

    auto systemRequestedQuit() -> void override { quit(); }

    auto anotherInstanceStarted(juce::String const& commandLine) -> void override { juce::ignoreUnused(commandLine); }

    struct MainWindow : juce::DocumentWindow
    {

        explicit MainWindow(juce::String const& name)
            : DocumentWindow(
                name,
                juce::Desktop::getInstance().getDefaultLookAndFeel().findColour(ResizableWindow::backgroundColourId),
                DocumentWindow::allButtons)
        {
            setUsingNativeTitleBar(true);
            setContentOwned(new mc::MainComponent(), true);

#if JUCE_IOS || JUCE_ANDROID
            setFullScreen(true);
#else
            setResizable(true, true);
            centreWithSize(getWidth(), getHeight());
#endif

            setVisible(true);
        }

        auto closeButtonPressed() -> void override { JUCEApplication::getInstance()->systemRequestedQuit(); }

    private:
        JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainWindow) // NOLINT
    };

private:
    std::unique_ptr<MainWindow> _mainWindow;
};

// This macro generates the main() routine that launches the app.
START_JUCE_APPLICATION(GuiAppApplication) // NOLINT
