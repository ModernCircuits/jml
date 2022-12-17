#pragma once

namespace mc {

template<typename T>
struct ValueTreeConverter
{
    [[nodiscard]] static auto toValueTree(T const& t) -> juce::ValueTree;
    [[nodiscard]] static auto fromValueTree(juce::ValueTree const& vt) -> T;
};

template<typename T>
[[nodiscard]] auto toValueTree(T const& val) -> juce::ValueTree
{
    return ValueTreeConverter<T>::toValueTree(val);
}

template<typename T>
[[nodiscard]] auto fromValueTree(juce::ValueTree const& tree) -> T
{
    return ValueTreeConverter<T>::fromValueTree(tree);
}

struct GetGlobalComponentBounds
{
    struct Request
    {
        inline static constexpr auto const* type = "GetGlobalComponentBoundsRequest";
        juce::String componentID{};
    };

    struct Response
    {
        inline static constexpr auto const* type = "GetGlobalComponentBoundsResponse";
        juce::Rectangle<int> globalBounds{};
    };
};

template<>
struct ValueTreeConverter<GetGlobalComponentBounds::Request>
{
    [[nodiscard]] static auto toValueTree(GetGlobalComponentBounds::Request const& request) -> juce::ValueTree
    {
        auto tree = juce::ValueTree{GetGlobalComponentBounds::Request::type};
        tree.setProperty("componentID", request.componentID, nullptr);
        return tree;
    }

    [[nodiscard]] static auto fromValueTree(juce::ValueTree const& tree) -> GetGlobalComponentBounds::Request
    {
        auto request        = GetGlobalComponentBounds::Request{};
        request.componentID = tree["componentID"];
        return request;
    }
};

template<>
struct ValueTreeConverter<GetGlobalComponentBounds::Response>
{
    [[nodiscard]] static auto toValueTree(GetGlobalComponentBounds::Response const& response) -> juce::ValueTree
    {
        auto tree = juce::ValueTree{GetGlobalComponentBounds::Response::type};
        auto var  = juce::VariantConverter<juce::Rectangle<int>>::toVar(response.globalBounds);
        tree.setProperty("globalBounds", var, nullptr);
        return tree;
    }

    [[nodiscard]] static auto fromValueTree(juce::ValueTree const& tree) -> GetGlobalComponentBounds::Response
    {
        auto request         = GetGlobalComponentBounds::Response{};
        request.globalBounds = juce::VariantConverter<juce::Rectangle<int>>::fromVar(tree["globalBounds"]);
        return request;
    }
};

} // namespace mc
