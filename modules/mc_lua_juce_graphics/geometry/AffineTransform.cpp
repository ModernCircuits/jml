#include "AffineTransform.hpp"

#include <juce_graphics/juce_graphics.h>
namespace mc::lua::bindings {
auto juce_AffineTransform(sol::table& state) -> void
{
    using Transform = juce::AffineTransform;

    // clang-format off
    auto transform = state.new_usertype<Transform>("AffineTransform",
        sol::constructors<
            Transform(),
            Transform(float, float, float, float, float, float)
        >()
    );
    transform.set_function("rotated", sol::overload(
            static_cast<Transform (Transform::*)(float) const noexcept>(&Transform::rotated),
            static_cast<Transform (Transform::*)(float, float, float) const noexcept>(&Transform::rotated)
        )
    );
    transform.set_function("scaled", sol::overload(
            static_cast<Transform (Transform::*)(float) const noexcept>(&Transform::scaled),
            static_cast<Transform (Transform::*)(float, float) const noexcept>(&Transform::scaled),
            static_cast<Transform (Transform::*)(float, float, float, float) const noexcept>(&Transform::scaled)
        )
    );
    transform.set_function("rotation", sol::overload(
            static_cast<Transform (*)(float) noexcept>(&Transform::rotation),
            static_cast<Transform (*)(float, float, float) noexcept>(&Transform::rotation)
        )
    );
    // clang-format on
    transform["withAbsoluteTranslation"] = &Transform::withAbsoluteTranslation;
    transform["sheared"]                 = &Transform::sheared;
    transform["shear"]                   = &Transform::shear;
    transform["verticalFlip"]            = &Transform::verticalFlip;
    transform["inverted"]                = &Transform::inverted;
    transform["followedBy"]              = &Transform::followedBy;
    transform["isIdentity"]              = &Transform::isIdentity;
    transform["isSingularity"]           = &Transform::isSingularity;
    transform["isOnlyTranslation"]       = &Transform::isOnlyTranslation;
    transform["getTranslationX"]         = &Transform::getTranslationX;
    transform["getTranslationY"]         = &Transform::getTranslationY;
    transform["getDeterminant"]          = &Transform::getDeterminant;

    transform["mat00"] = &Transform::mat00;
    transform["mat01"] = &Transform::mat01;
    transform["mat02"] = &Transform::mat02;
    transform["mat10"] = &Transform::mat10;
    transform["mat11"] = &Transform::mat11;
    transform["mat12"] = &Transform::mat12;
}
} // namespace mc::lua::bindings
