#include "ImageComponent.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace mc::lua::bindings {

auto juce_ImageComponent(sol::table& state) -> void
{
    // clang-format off
    auto imgComponent = state.new_usertype<juce::ImageComponent>("ImageComponent",
        sol::constructors<juce::ImageComponent(juce::String const&)>(),
        sol::base_classes,
        sol::bases<
            juce::MouseListener,
            juce::Component,
            juce::TooltipClient,
            juce::SettableTooltipClient
        >()
    );
    // clang-format on

    imgComponent["getImage"]          = &juce::ImageComponent::getImage;
    imgComponent["setImagePlacement"] = &juce::ImageComponent::setImagePlacement;
    imgComponent["getImagePlacement"] = &juce::ImageComponent::getImagePlacement;
    imgComponent["setImage"]          = sol::overload(                                                                          //
        [](juce::ImageComponent* comp, juce::Image const& img) { comp->setImage(img); },                               //
        [](juce::ImageComponent* comp, juce::Image const& img, juce::RectanglePlacement p) { comp->setImage(img, p); } //
    );
}

} // namespace mc::lua::bindings
