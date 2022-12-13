#pragma once

#include "Property/ValuePropertyComponent.hpp"

namespace mc {
struct FilePropertyComponent final : ValuePropertyComponent
{
    FilePropertyComponent(juce::Value const& value, juce::String const& name, juce::String title = "Open",
                          juce::String pattern = "*.*");
    ~FilePropertyComponent() override = default;

    auto refresh() -> void override;

private:
    auto browseForFile() -> void;

    struct Container final : Component
    {
        Container();
        ~Container() override = default;

        auto resized() -> void override;

        juce::TextEditor filename;
        juce::TextButton browse{"..."};
        juce::TextButton clear{"X"};
    };

    Container _container;

    juce::String _title;
    juce::String _pattern;

    UniquePtr<juce::FileChooser> _chooser;
};

} // namespace mc
