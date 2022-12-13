#include "FilePropertyComponent.hpp"

namespace mc {
FilePropertyComponent::FilePropertyComponent(juce::Value const& value, juce::String const& name, juce::String title,
                                             juce::String pattern)
    : ValuePropertyComponent{value, name}, _title{std::move(title)}, _pattern{std::move(pattern)}
{
    _container.browse.onClick = [this] { browseForFile(); };
    _container.clear.onClick  = [this] { this->value().setValue(""); };

    addAndMakeVisible(_container);
}

void FilePropertyComponent::refresh() { _container.filename.setText(value().toString()); }

auto FilePropertyComponent::browseForFile() -> void
{
    auto folderChooserFlags = juce::FileBrowserComponent::openMode;
    _chooser                = makeUnique<juce::FileChooser>(_title, juce::File(value().toString()), _pattern);
    _chooser->launchAsync(folderChooserFlags, [this](juce::FileChooser const&) {
        value().setValue(_chooser->getResult().getFullPathName());
    });
}

FilePropertyComponent::Container::Container()
{
    addAndMakeVisible(filename);
    addAndMakeVisible(browse);
    addAndMakeVisible(clear);

    filename.setReadOnly(true);
}

void FilePropertyComponent::Container::resized()
{
    auto rc = getLocalBounds();
    clear.setBounds(rc.removeFromRight(rc.getHeight()));
    browse.setBounds(rc.removeFromRight(rc.getHeight()));
    rc.removeFromRight(3);
    filename.setBounds(rc);
}

} // namespace mc
