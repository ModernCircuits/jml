#include "MenuBar.hpp"

#include "BinaryData.hpp"
#include "CommandIDs.hpp"

namespace mc {

MenuBar::MenuBar(juce::ApplicationCommandManager& commandManager) : _commandManager{commandManager}
{
    setApplicationCommandManagerToWatch(&_commandManager);
    addAndMakeVisible(_menu);
}

auto MenuBar::resized() -> void { _menu.setBounds(getLocalBounds()); }

auto MenuBar::getMenuBarNames() -> juce::StringArray
{
    return {
        "File",
        "Edit",
    };
}

auto MenuBar::getMenuForIndex(int menuIndex, juce::String const& /*menuName*/) -> juce::PopupMenu
{

    if (menuIndex == 0) {
        auto menu       = juce::PopupMenu{};
        auto openIcon   = juce::Drawable::createFromImageData(mcbd::file_open_svg, mcbd::file_open_svgSize);
        auto saveIcon   = juce::Drawable::createFromImageData(mcbd::save_svg, mcbd::save_svgSize);
        auto saveAsIcon = juce::Drawable::createFromImageData(mcbd::save_as_svg, mcbd::save_as_svgSize);
        menu.addCommandItem(&_commandManager, CommandIDs::open, "Open", openIcon->createCopy());
        menu.addSeparator();
        menu.addCommandItem(&_commandManager, CommandIDs::save, "Save", saveIcon->createCopy());
        menu.addCommandItem(&_commandManager, CommandIDs::saveAs, "Save As", saveAsIcon->createCopy());
        return menu;
    }

    if (menuIndex == 1) {
        auto menu     = juce::PopupMenu{};
        auto undoIcon = juce::Drawable::createFromImageData(mcbd::undo_svg, mcbd::undo_svgSize);
        auto redoIcon = juce::Drawable::createFromImageData(mcbd::redo_svg, mcbd::redo_svgSize);
        menu.addCommandItem(&_commandManager, CommandIDs::undo, "Undo", undoIcon->createCopy());
        menu.addCommandItem(&_commandManager, CommandIDs::redo, "Redo", redoIcon->createCopy());
        return menu;
    }

    jassertfalse;
    return {};
}

auto MenuBar::menuItemSelected(int /*menuItemID*/, int /*topLevelMenuIndex*/) -> void {}

} // namespace mc
