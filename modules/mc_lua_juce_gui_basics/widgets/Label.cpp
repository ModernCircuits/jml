#include "Label.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

SOL_BASE_CLASSES(juce::Label, juce::Component, juce::MouseListener, juce::SettableTooltipClient, juce::TooltipClient);
namespace mc::lua::bindings {
auto juce_Label(sol::table& state) -> void
{
    // clang-format off
    auto label = state.new_usertype<juce::Label>("Label",
        sol::constructors<juce::Label(juce::String const&, juce::String const&)>(),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    label["setText"]                       = &juce::Label::setText;
    label["getText"]                       = &juce::Label::getText;
    label["getTextValue"]                  = &juce::Label::getTextValue;
    label["setFont"]                       = &juce::Label::setFont;
    label["getFont"]                       = &juce::Label::getFont;
    label["setJustificationType"]          = &juce::Label::setJustificationType;
    label["getJustificationType"]          = &juce::Label::getJustificationType;
    label["setBorderSize"]                 = &juce::Label::setBorderSize;
    label["getBorderSize"]                 = &juce::Label::getBorderSize;
    label["attachToComponent"]             = &juce::Label::attachToComponent;
    label["getAttachedComponent"]          = &juce::Label::getAttachedComponent;
    label["isAttachedOnLeft"]              = &juce::Label::isAttachedOnLeft;
    label["setMinimumHorizontalScale"]     = &juce::Label::setMinimumHorizontalScale;
    label["getMinimumHorizontalScale"]     = &juce::Label::getMinimumHorizontalScale;
    label["setKeyboardType"]               = &juce::Label::setKeyboardType;
    label["addListener"]                   = &juce::Label::addListener;
    label["removeListener"]                = &juce::Label::removeListener;
    label["setEditable"]                   = &juce::Label::setEditable;
    label["isEditableOnSingleClick"]       = &juce::Label::isEditableOnSingleClick;
    label["isEditableOnDoubleClick"]       = &juce::Label::isEditableOnDoubleClick;
    label["doesLossOfFocusDiscardChanges"] = &juce::Label::doesLossOfFocusDiscardChanges;
    label["isEditable"]                    = &juce::Label::isEditable;
    label["showEditor"]                    = &juce::Label::showEditor;
    label["hideEditor"]                    = &juce::Label::hideEditor;
    label["isBeingEdited"]                 = &juce::Label::isBeingEdited;
    label["getCurrentTextEditor"]          = &juce::Label::getCurrentTextEditor;
}
} // namespace mc::lua::bindings
