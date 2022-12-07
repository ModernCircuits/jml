#pragma once

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc {
struct FileChangeListener final : juce::Timer
{
    explicit FileChangeListener(juce::File file) : _file{std::move(file)}, _writeTime{_file.getLastModificationTime()}
    {
        startTimer(500);
    }

    std::function<void()> onChange{};

private:
    auto timerCallback() -> void override
    {
        auto const writeTime = _file.getLastModificationTime();
        if (writeTime == _writeTime) { return; }
        _writeTime = writeTime;

        if (onChange) { onChange(); }
    }

    juce::File _file;
    juce::Time _writeTime;
};

} // namespace mc
