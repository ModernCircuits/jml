#include "CodeDocument.hpp"

#include <juce_gui_extra/juce_gui_extra.h>

namespace mc::lua::bindings {

auto juce_CodeDocument(sol::table& state) -> void
{
    auto table = state["CodeDocument"].get_or_create<sol::table>();

    auto doc                        = table.new_usertype<juce::CodeDocument>("CodeDocument", sol::constructors<juce::CodeDocument()>());
    doc["getAllContent"]            = &juce::CodeDocument::getAllContent;
    doc["getTextBetween"]           = &juce::CodeDocument::getTextBetween;
    doc["getLine"]                  = &juce::CodeDocument::getLine;
    doc["getNumCharacters"]         = &juce::CodeDocument::getNumCharacters;
    doc["getNumLines"]              = &juce::CodeDocument::getNumLines;
    doc["getMaximumLineLength"]     = &juce::CodeDocument::getMaximumLineLength;
    doc["replaceSection"]           = &juce::CodeDocument::replaceSection;
    doc["replaceAllContent"]        = &juce::CodeDocument::replaceAllContent;
    doc["applyChanges"]             = &juce::CodeDocument::applyChanges;
    doc["loadFromStream"]           = &juce::CodeDocument::loadFromStream;
    doc["writeToStream"]            = &juce::CodeDocument::writeToStream;
    doc["getNewLineCharacters"]     = &juce::CodeDocument::getNewLineCharacters;
    doc["setNewLineCharacters"]     = &juce::CodeDocument::setNewLineCharacters;
    doc["newTransaction"]           = &juce::CodeDocument::newTransaction;
    doc["undo"]                     = &juce::CodeDocument::undo;
    doc["redo"]                     = &juce::CodeDocument::redo;
    doc["clearUndoHistory"]         = &juce::CodeDocument::clearUndoHistory;
    doc["getUndoManager"]           = &juce::CodeDocument::getUndoManager;
    doc["setSavePoint"]             = &juce::CodeDocument::setSavePoint;
    doc["hasChangedSinceSavePoint"] = &juce::CodeDocument::hasChangedSinceSavePoint;
    doc["findWordBreakBefore"]      = &juce::CodeDocument::findWordBreakBefore;
    doc["findTokenContaining"]      = &juce::CodeDocument::findTokenContaining;
    doc["findLineContaining"]       = &juce::CodeDocument::findLineContaining;
    doc["addListener"]              = &juce::CodeDocument::addListener;
    doc["removeListener"]           = &juce::CodeDocument::removeListener;
    // doc["deleteSection"]            = &juce::CodeDocument::deleteSection;
    // doc["deleteSection"]            = &juce::CodeDocument::deleteSection;
    // doc["insertText"]               = &juce::CodeDocument::insertText;
    // doc["insertText"]               = &juce::CodeDocument::insertText;

    table["new"] = [] { return std::unique_ptr<juce::CodeDocument>(); };
}

} // namespace mc::lua::bindings
