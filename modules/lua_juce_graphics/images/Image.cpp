#include "Image.hpp"

#include <juce_graphics/juce_graphics.h>
namespace mc::lua::bindings {
auto juce_Image(sol::table& state) -> void
{
    // clang-format off
    state.new_enum("ImagePixelFormat",
        "UnknownFormat",
            juce::Image::PixelFormat::UnknownFormat,
        "RGB",
            juce::Image::PixelFormat::RGB,
        "ARGB",
            juce::Image::PixelFormat::ARGB,
        "SingleChannel",
            juce::Image::PixelFormat::SingleChannel
    );

    auto img = state.new_usertype<juce::Image>("Image",
        sol::constructors<
            juce::Image(),
            juce::Image(juce::Image::PixelFormat, int, int, bool),
            juce::Image(juce::Image::PixelFormat, int, int, bool, juce::ImageType const&),
            juce::Image(juce::ReferenceCountedObjectPtr<juce::ImagePixelData>)
        >()
    );
    // clang-format on

    img["isValid"]               = &juce::Image::isValid;
    img["isNull"]                = &juce::Image::isNull;
    img["getWidth"]              = &juce::Image::getWidth;
    img["getHeight"]             = &juce::Image::getHeight;
    img["getBounds"]             = &juce::Image::getBounds;
    img["getFormat"]             = &juce::Image::getFormat;
    img["isARGB"]                = &juce::Image::isARGB;
    img["isRGB"]                 = &juce::Image::isRGB;
    img["isSingleChannel"]       = &juce::Image::isSingleChannel;
    img["hasAlphaChannel"]       = &juce::Image::hasAlphaChannel;
    img["clear"]                 = &juce::Image::clear;
    img["rescaled"]              = &juce::Image::rescaled;
    img["createCopy"]            = &juce::Image::createCopy;
    img["convertedToFormat"]     = &juce::Image::convertedToFormat;
    img["duplicateIfShared"]     = &juce::Image::duplicateIfShared;
    img["getClippedImage"]       = &juce::Image::getClippedImage;
    img["getPixelAt"]            = &juce::Image::getPixelAt;
    img["setPixelAt"]            = &juce::Image::setPixelAt;
    img["multiplyAlphaAt"]       = &juce::Image::multiplyAlphaAt;
    img["multiplyAllAlphas"]     = &juce::Image::multiplyAllAlphas;
    img["desaturate"]            = &juce::Image::desaturate;
    img["moveImageSection"]      = &juce::Image::moveImageSection;
    img["createSolidAreaMask"]   = &juce::Image::createSolidAreaMask;
    img["getProperties"]         = &juce::Image::getProperties;
    img["createLowLevelContext"] = &juce::Image::createLowLevelContext;
    img["getReferenceCount"]     = &juce::Image::getReferenceCount;
    img["getPixelData"]          = &juce::Image::getPixelData;
}
} // namespace mc::lua::bindings
