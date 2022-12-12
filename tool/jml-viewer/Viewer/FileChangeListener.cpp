#include "FileChangeListener.hpp"

namespace mc {

FileChangeListener::FileChangeListener(juce::File file)
    : _file{std::move(file)}, _writeTime{_file.getLastModificationTime()}
{
    startTimer(500);
}

auto FileChangeListener::timerCallback() -> void
{
    auto const writeTime = _file.getLastModificationTime();
    if (writeTime == _writeTime) { return; }
    _writeTime = writeTime;

    if (onChange) { onChange(); }
}

} // namespace mc
