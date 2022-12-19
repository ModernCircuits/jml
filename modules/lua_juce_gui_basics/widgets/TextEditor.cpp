#include "TextEditor.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc::lua::bindings {

auto juce_TextEditor(sol::table& state) -> void
{
    // clang-format off
    auto editor = state.new_usertype<juce::TextEditor>("TextEditor",
        sol::constructors<juce::TextEditor(juce::String const&, juce::juce_wchar)>(),
        sol::base_classes,
        sol::bases<
            juce::TextInputTarget,
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    editor["setMultiLine"]                           = &juce::TextEditor::setMultiLine;
    editor["isMultiLine"]                            = &juce::TextEditor::isMultiLine;
    editor["setReturnKeyStartsNewLine"]              = &juce::TextEditor::setReturnKeyStartsNewLine;
    editor["getReturnKeyStartsNewLine"]              = &juce::TextEditor::getReturnKeyStartsNewLine;
    editor["setTabKeyUsedAsCharacter"]               = &juce::TextEditor::setTabKeyUsedAsCharacter;
    editor["isTabKeyUsedAsCharacter"]                = &juce::TextEditor::isTabKeyUsedAsCharacter;
    editor["setEscapeAndReturnKeysConsumed"]         = &juce::TextEditor::setEscapeAndReturnKeysConsumed;
    editor["setReadOnly"]                            = &juce::TextEditor::setReadOnly;
    editor["isReadOnly"]                             = &juce::TextEditor::isReadOnly;
    editor["setCaretVisible"]                        = &juce::TextEditor::setCaretVisible;
    editor["isCaretVisible"]                         = &juce::TextEditor::isCaretVisible;
    editor["setScrollbarsShown"]                     = &juce::TextEditor::setScrollbarsShown;
    editor["areScrollbarsShown"]                     = &juce::TextEditor::areScrollbarsShown;
    editor["setPasswordCharacter"]                   = &juce::TextEditor::setPasswordCharacter;
    editor["getPasswordCharacter"]                   = &juce::TextEditor::getPasswordCharacter;
    editor["setPopupMenuEnabled"]                    = &juce::TextEditor::setPopupMenuEnabled;
    editor["isPopupMenuEnabled"]                     = &juce::TextEditor::isPopupMenuEnabled;
    editor["isPopupMenuCurrentlyActive"]             = &juce::TextEditor::isPopupMenuCurrentlyActive;
    editor["setFont"]                                = &juce::TextEditor::setFont;
    editor["applyFontToAllText"]                     = &juce::TextEditor::applyFontToAllText;
    editor["getFont"]                                = &juce::TextEditor::getFont;
    editor["applyColourToAllText"]                   = &juce::TextEditor::applyColourToAllText;
    editor["setWhitespaceUnderlined"]                = &juce::TextEditor::setWhitespaceUnderlined;
    editor["isWhitespaceUnderlined"]                 = &juce::TextEditor::isWhitespaceUnderlined;
    editor["setSelectAllWhenFocused"]                = &juce::TextEditor::setSelectAllWhenFocused;
    editor["setTextToShowWhenEmpty"]                 = &juce::TextEditor::setTextToShowWhenEmpty;
    editor["getTextToShowWhenEmpty"]                 = &juce::TextEditor::getTextToShowWhenEmpty;
    editor["setScrollBarThickness"]                  = &juce::TextEditor::setScrollBarThickness;
    editor["addListener"]                            = &juce::TextEditor::addListener;
    editor["removeListener"]                         = &juce::TextEditor::removeListener;
    editor["getText"]                                = &juce::TextEditor::getText;
    editor["getTextInRange"]                         = &juce::TextEditor::getTextInRange;
    editor["isEmpty"]                                = &juce::TextEditor::isEmpty;
    editor["setText"]                                = &juce::TextEditor::setText;
    editor["getTextValue"]                           = &juce::TextEditor::getTextValue;
    editor["insertTextAtCaret"]                      = &juce::TextEditor::insertTextAtCaret;
    editor["clear"]                                  = &juce::TextEditor::clear;
    editor["cut"]                                    = &juce::TextEditor::cut;
    editor["copy"]                                   = &juce::TextEditor::copy;
    editor["paste"]                                  = &juce::TextEditor::paste;
    editor["getCaretPosition"]                       = &juce::TextEditor::getCaretPosition;
    editor["setCaretPosition"]                       = &juce::TextEditor::setCaretPosition;
    editor["scrollEditorToPositionCaret"]            = &juce::TextEditor::scrollEditorToPositionCaret;
    editor["getCaretRectangleForCharIndex"]          = &juce::TextEditor::getCaretRectangleForCharIndex;
    editor["setHighlightedRegion"]                   = &juce::TextEditor::setHighlightedRegion;
    editor["getHighlightedRegion"]                   = &juce::TextEditor::getHighlightedRegion;
    editor["getHighlightedText"]                     = &juce::TextEditor::getHighlightedText;
    editor["getCharIndexForPoint"]                   = &juce::TextEditor::getCharIndexForPoint;
    editor["getTotalNumChars"]                       = &juce::TextEditor::getTotalNumChars;
    editor["getTextWidth"]                           = &juce::TextEditor::getTextWidth;
    editor["getTextHeight"]                          = &juce::TextEditor::getTextHeight;
    editor["setIndents"]                             = &juce::TextEditor::setIndents;
    editor["getTopIndent"]                           = &juce::TextEditor::getTopIndent;
    editor["getLeftIndent"]                          = &juce::TextEditor::getLeftIndent;
    editor["setBorder"]                              = &juce::TextEditor::setBorder;
    editor["getBorder"]                              = &juce::TextEditor::getBorder;
    editor["setScrollToShowCursor"]                  = &juce::TextEditor::setScrollToShowCursor;
    editor["setJustification"]                       = &juce::TextEditor::setJustification;
    editor["getJustificationType"]                   = &juce::TextEditor::getJustificationType;
    editor["setLineSpacing"]                         = &juce::TextEditor::setLineSpacing;
    editor["getLineSpacing"]                         = &juce::TextEditor::getLineSpacing;
    editor["getTextBounds"]                          = &juce::TextEditor::getTextBounds;
    editor["moveCaretLeft"]                          = &juce::TextEditor::moveCaretLeft;
    editor["moveCaretRight"]                         = &juce::TextEditor::moveCaretRight;
    editor["moveCaretRight"]                         = &juce::TextEditor::moveCaretRight;
    editor["moveCaretUp"]                            = &juce::TextEditor::moveCaretUp;
    editor["moveCaretDown"]                          = &juce::TextEditor::moveCaretDown;
    editor["pageUp"]                                 = &juce::TextEditor::pageUp;
    editor["pageDown"]                               = &juce::TextEditor::pageDown;
    editor["scrollDown"]                             = &juce::TextEditor::scrollDown;
    editor["scrollUp"]                               = &juce::TextEditor::scrollUp;
    editor["moveCaretToTop"]                         = &juce::TextEditor::moveCaretToTop;
    editor["moveCaretToStartOfLine"]                 = &juce::TextEditor::moveCaretToStartOfLine;
    editor["moveCaretToEndOfLine"]                   = &juce::TextEditor::moveCaretToEndOfLine;
    editor["deleteBackwards"]                        = &juce::TextEditor::deleteBackwards;
    editor["deleteForwards"]                         = &juce::TextEditor::deleteForwards;
    editor["copyToClipboard"]                        = &juce::TextEditor::copyToClipboard;
    editor["cutToClipboard"]                         = &juce::TextEditor::cutToClipboard;
    editor["pasteFromClipboard"]                     = &juce::TextEditor::pasteFromClipboard;
    editor["selectAll"]                              = &juce::TextEditor::selectAll;
    editor["undo"]                                   = &juce::TextEditor::undo;
    editor["redo"]                                   = &juce::TextEditor::redo;
    editor["addPopupMenuItems"]                      = &juce::TextEditor::addPopupMenuItems;
    editor["performPopupMenuAction"]                 = &juce::TextEditor::performPopupMenuAction;
    editor["setInputFilter"]                         = &juce::TextEditor::setInputFilter;
    editor["getInputFilter"]                         = &juce::TextEditor::getInputFilter;
    editor["setInputRestrictions"]                   = &juce::TextEditor::setInputRestrictions;
    editor["setKeyboardType"]                        = &juce::TextEditor::setKeyboardType;
    editor["setClicksOutsideDismissVirtualKeyboard"] = &juce::TextEditor::setClicksOutsideDismissVirtualKeyboard;
    editor["getClicksOutsideDismissVirtualKeyboard"] = &juce::TextEditor::getClicksOutsideDismissVirtualKeyboard;
    editor["moveCaretToEnd"]                         = sol::overload(                                                  //
        [](juce::TextEditor* comp) { comp->moveCaretToEnd(); },                                //
        [](juce::TextEditor* comp, bool selecting) { return comp->moveCaretToEnd(selecting); } //
    );
    editor["getTextIndexAt"]                         = sol::overload(                                                            //
        [](juce::TextEditor const* comp, int x, int y) { return comp->getTextIndexAt(x, y); },           //
        [](juce::TextEditor const* comp, juce::Point<int> point) { return comp->getTextIndexAt(point); } //
    );
}

} // namespace mc::lua::bindings
