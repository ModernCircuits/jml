#include "ComboBox.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

SOL_BASE_CLASSES(juce::ComboBox,
    juce::Component,
    juce::MouseListener,
    juce::SettableTooltipClient,
    juce::TooltipClient,
    juce::Value::Listener);

auto juce_ComboBox(sol::table& state) -> void
{
    // clang-format off
    state.new_enum("ComboBoxColourIds",
        "arrowColourId",
            juce::ComboBox::ColourIds::arrowColourId,
        "backgroundColourId",
            juce::ComboBox::ColourIds::backgroundColourId,
        "buttonColourId",
            juce::ComboBox::ColourIds::buttonColourId,
        "focusedOutlineColourId",
            juce::ComboBox::ColourIds::focusedOutlineColourId,
        "outlineColourId",
            juce::ComboBox::ColourIds::outlineColourId,
        "textColourId",
            juce::ComboBox::ColourIds::textColourId
    );

    auto combo = state.new_usertype<juce::ComboBox>("ComboBox",
        sol::factories(
            [](juce::String const& id) { return std::make_shared<juce::ComboBox>(id); }
        ),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient,
            juce::Value::Listener
        >()
    );
    // clang-format on

    // combo["getRootMenu"]                   = &juce::ComboBox::getRootMenu;
    // combo["getRootMenu"]                   = &juce::ComboBox::getRootMenu;
    // combo["clear"]                         = &juce::ComboBox::clear;
    // combo["setSelectedId"]                 = &juce::ComboBox::setSelectedId;
    // combo["setSelectedItemIndex"]          = &juce::ComboBox::setSelectedItemIndex;
    // combo["setText"]                       = &juce::ComboBox::setText;

    combo["setEditableText"]               = &juce::ComboBox::setEditableText;
    combo["isTextEditable"]                = &juce::ComboBox::isTextEditable;
    combo["setJustificationType"]          = &juce::ComboBox::setJustificationType;
    combo["getJustificationType"]          = &juce::ComboBox::getJustificationType;
    combo["addItem"]                       = &juce::ComboBox::addItem;
    combo["addItemList"]                   = &juce::ComboBox::addItemList;
    combo["addSeparator"]                  = &juce::ComboBox::addSeparator;
    combo["addSectionHeading"]             = &juce::ComboBox::addSectionHeading;
    combo["setItemEnabled"]                = &juce::ComboBox::setItemEnabled;
    combo["isItemEnabled"]                 = &juce::ComboBox::isItemEnabled;
    combo["changeItemText"]                = &juce::ComboBox::changeItemText;
    combo["getNumItems"]                   = &juce::ComboBox::getNumItems;
    combo["getItemText"]                   = &juce::ComboBox::getItemText;
    combo["getItemId"]                     = &juce::ComboBox::getItemId;
    combo["indexOfItemId"]                 = &juce::ComboBox::indexOfItemId;
    combo["getSelectedId"]                 = &juce::ComboBox::getSelectedId;
    combo["getSelectedIdAsValue"]          = &juce::ComboBox::getSelectedIdAsValue;
    combo["getSelectedItemIndex"]          = &juce::ComboBox::getSelectedItemIndex;
    combo["getText"]                       = &juce::ComboBox::getText;
    combo["showEditor"]                    = &juce::ComboBox::showEditor;
    combo["showPopup"]                     = &juce::ComboBox::showPopup;
    combo["hidePopup"]                     = &juce::ComboBox::hidePopup;
    combo["isPopupActive"]                 = &juce::ComboBox::isPopupActive;
    combo["addListener"]                   = &juce::ComboBox::addListener;
    combo["removeListener"]                = &juce::ComboBox::removeListener;
    combo["setTextWhenNothingSelected"]    = &juce::ComboBox::setTextWhenNothingSelected;
    combo["getTextWhenNothingSelected"]    = &juce::ComboBox::getTextWhenNothingSelected;
    combo["setTextWhenNoChoicesAvailable"] = &juce::ComboBox::setTextWhenNoChoicesAvailable;
    combo["getTextWhenNoChoicesAvailable"] = &juce::ComboBox::getTextWhenNoChoicesAvailable;
    combo["setTooltip"]                    = &juce::ComboBox::setTooltip;
    combo["setScrollWheelEnabled"]         = &juce::ComboBox::setScrollWheelEnabled;
    combo["onChange"]                      = &juce::ComboBox::onChange;
}
