#include "ImageCache.hpp"

#include <juce_graphics/juce_graphics.h>

auto juce_ImageCache(sol::table& state) -> void
{
    auto cache                   = state.create_named("ImageCache");
    cache["getFromFile"]         = &juce::ImageCache::getFromFile;
    cache["getFromMemory"]       = &juce::ImageCache::getFromMemory;
    cache["getFromHashCode"]     = &juce::ImageCache::getFromHashCode;
    cache["addImageToCache"]     = &juce::ImageCache::addImageToCache;
    cache["setCacheTimeout"]     = &juce::ImageCache::setCacheTimeout;
    cache["releaseUnusedImages"] = &juce::ImageCache::releaseUnusedImages;
}
