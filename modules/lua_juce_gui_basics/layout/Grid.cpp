#include "Grid.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace juce {
[[maybe_unused]] static auto operator==(GridItem const&, GridItem const&) -> bool { return false; }
[[maybe_unused]] static auto operator!=(GridItem const&, GridItem const&) -> bool { return true; }
[[maybe_unused]] static auto operator==(Grid::TrackInfo const&, Grid::TrackInfo const&) -> bool { return false; }
[[maybe_unused]] static auto operator!=(Grid::TrackInfo const&, Grid::TrackInfo const&) -> bool { return true; }
} // namespace juce
namespace mc::lua::bindings {
auto juce_Grid(sol::table& state) -> void
{
    auto table = state["Grid"].get_or_create<sol::table>();

    juce_ArrayImpl<juce::GridItem>(state, "Array_GridItem");
    juce_ArrayImpl<juce::Grid::TrackInfo>(state, "Array_GridTrackInfo");

    // juce::Grid::JustifyItems
    table.new_enum(                       //
        "JustifyItems",                   //
        "start",                          //
        juce::Grid::JustifyItems::start,  //
        "end",                            //
        juce::Grid::JustifyItems::end,    //
        "center",                         //
        juce::Grid::JustifyItems::center, //
        "stretch",                        //
        juce::Grid::JustifyItems::stretch //
    );

    // juce::Grid::AlignItems
    table.new_enum(                     //
        "AlignItems",                   //
        "start",                        //
        juce::Grid::AlignItems::start,  //
        "end",                          //
        juce::Grid::AlignItems::end,    //
        "center",                       //
        juce::Grid::AlignItems::center, //
        "stretch",                      //
        juce::Grid::AlignItems::stretch //
    );

    // juce::Grid::JustifyContent
    table.new_enum(                               //
        "JustifyContent",                         //
        "start",                                  //
        juce::Grid::JustifyContent::start,        //
        "end",                                    //
        juce::Grid::JustifyContent::end,          //
        "center",                                 //
        juce::Grid::JustifyContent::center,       //
        "stretch",                                //
        juce::Grid::JustifyContent::stretch,      //
        "spaceAround",                            //
        juce::Grid::JustifyContent::spaceAround,  //
        "spaceBetween",                           //
        juce::Grid::JustifyContent::spaceBetween, //
        "spaceEvenly",                            //
        juce::Grid::JustifyContent::spaceEvenly   //
    );

    // juce::Grid::AlignContent
    table.new_enum(                             //
        "AlignContent",                         //
        "start",                                //
        juce::Grid::AlignContent::start,        //
        "end",                                  //
        juce::Grid::AlignContent::end,          //
        "center",                               //
        juce::Grid::AlignContent::center,       //
        "stretch",                              //
        juce::Grid::AlignContent::stretch,      //
        "spaceAround",                          //
        juce::Grid::AlignContent::spaceAround,  //
        "spaceBetween",                         //
        juce::Grid::AlignContent::spaceBetween, //
        "spaceEvenly",                          //
        juce::Grid::AlignContent::spaceEvenly   //
    );

    // juce::Grid::AutoFlow
    table.new_enum(                       //
        "AutoFlow",                       //
        "row",                            //
        juce::Grid::AutoFlow::row,        //
        "column",                         //
        juce::Grid::AutoFlow::column,     //
        "rowDense",                       //
        juce::Grid::AutoFlow::rowDense,   //
        "columnDense",                    //
        juce::Grid::AutoFlow::columnDense //
    );

    auto fr        = table.new_usertype<juce::Grid::Fr>("Fr", sol::constructors<juce::Grid::Fr(int)>());
    fr["fraction"] = &juce::Grid::Fr::fraction;

    auto px      = table.new_usertype<juce::Grid::Px>("Px", sol::constructors<juce::Grid::Px(float)>());
    px["pixels"] = &juce::Grid::Px::pixels;

    // clang-format off
    auto ti = table.new_usertype<juce::Grid::TrackInfo>(
        "TrackInfo",
        sol::constructors<
            juce::Grid::TrackInfo(),
            juce::Grid::TrackInfo(juce::Grid::Fr),
            juce::Grid::TrackInfo(juce::Grid::Px)
        >()
    );
    // clang-format on

    ti["isAuto"]           = &juce::Grid::TrackInfo::isAuto;
    ti["isFractional"]     = &juce::Grid::TrackInfo::isFractional;
    ti["isPixels"]         = &juce::Grid::TrackInfo::isPixels;
    ti["getStartLineName"] = &juce::Grid::TrackInfo::getStartLineName;
    ti["getEndLineName"]   = &juce::Grid::TrackInfo::getEndLineName;
    ti["getSize"]          = &juce::Grid::TrackInfo::getSize;

    table["new"]               = []() { return juce::Grid{}; };
    auto grid                  = table.new_usertype<juce::Grid>("Grid");
    grid["setGap"]             = &juce::Grid::setGap;
    grid["performLayout"]      = &juce::Grid::performLayout;
    grid["getNumberOfColumns"] = &juce::Grid::getNumberOfColumns;
    grid["getNumberOfRows"]    = &juce::Grid::getNumberOfRows;
    grid["justifyItems"]       = &juce::Grid::justifyItems;
    grid["alignItems"]         = &juce::Grid::alignItems;
    grid["justifyContent"]     = &juce::Grid::justifyContent;
    grid["alignContent"]       = &juce::Grid::alignContent;
    grid["autoFlow"]           = &juce::Grid::autoFlow;
    grid["templateColumns"]    = &juce::Grid::templateColumns;
    grid["templateRows"]       = &juce::Grid::templateRows;
    grid["templateAreas"]      = &juce::Grid::templateAreas;
    grid["autoRows"]           = &juce::Grid::autoRows;
    grid["autoColumns"]        = &juce::Grid::autoColumns;
    grid["columnGap"]          = &juce::Grid::columnGap;
    grid["rowGap"]             = &juce::Grid::rowGap;
    grid["items"]              = &juce::Grid::items;

    using GI  = juce::GridItem;
    using GIP = GI::Property;

    auto giTable   = state["GridItem"].get_or_create<sol::table>();
    giTable["new"] = [](juce::Component* comp) { return juce::GridItem{comp}; };

    auto gi = giTable.new_usertype<GI>("GridItem", sol::constructors<GI(), GI(juce::Component*)>());

    gi["setArea"] = sol::overload(                                   //
        static_cast<void (GI::*)(GIP, GIP)>(&GI::setArea),           //
        static_cast<void (GI::*)(GIP, GIP, GIP, GIP)>(&GI::setArea), //
        static_cast<void (GI::*)(juce::String const&)>(&GI::setArea) //
    );

    gi["withArea"] = sol::overload(                                                //
        static_cast<GI (GI::*)(GIP, GIP) const noexcept>(&GI::withArea),           //
        static_cast<GI (GI::*)(GIP, GIP, GIP, GIP) const noexcept>(&GI::withArea), //
        static_cast<GI (GI::*)(juce::String const&) const noexcept>(&GI::withArea) //
    );

    gi["withRow"]         = &GI::withRow;
    gi["withColumn"]      = &GI::withColumn;
    gi["withAlignSelf"]   = &GI::withAlignSelf;
    gi["withJustifySelf"] = &GI::withJustifySelf;
    gi["withWidth"]       = &GI::withWidth;
    gi["withHeight"]      = &GI::withHeight;
    gi["withSize"]        = &GI::withSize;
    gi["withMargin"]      = &GI::withMargin;
    gi["withOrder"]       = &GI::withOrder;

    gi["associatedComponent"] = &GI::associatedComponent;
    gi["order"]               = &GI::order;
    gi["justifySelf"]         = &GI::justifySelf;
    gi["alignSelf"]           = &GI::alignSelf;
    gi["column"]              = &GI::column;
    gi["row"]                 = &GI::row;
    gi["area"]                = &GI::area;
    gi["width"]               = &GI::width;
    gi["minWidth"]            = &GI::minWidth;
    gi["maxWidth"]            = &GI::maxWidth;
    gi["height"]              = &GI::height;
    gi["minHeight"]           = &GI::minHeight;
    gi["maxHeight"]           = &GI::maxHeight;
    gi["margin"]              = &GI::margin;
    gi["currentBounds"]       = &GI::currentBounds;

    // juce::GridItem::Keyword
    giTable.new_enum(          //
        "Keyword",             //
        "autoValue",           //
        GI::Keyword::autoValue //
    );

    // GI::JustifySelf
    giTable.new_enum(              //
        "JustifySelf",             //
        "start",                   //
        GI::JustifySelf::start,    //
        "end",                     //
        GI::JustifySelf::end,      //
        "center",                  //
        GI::JustifySelf::center,   //
        "stretch",                 //
        GI::JustifySelf::stretch,  //
        "autoValue",               //
        GI::JustifySelf::autoValue //
    );

    // GI::AlignSelf
    giTable.new_enum(            //
        "AlignSelf",             //
        "start",                 //
        GI::AlignSelf::start,    //
        "end",                   //
        GI::AlignSelf::end,      //
        "center",                //
        GI::AlignSelf::center,   //
        "stretch",               //
        GI::AlignSelf::stretch,  //
        "autoValue",             //
        GI::AlignSelf::autoValue //
    );

    // clang-format off
    auto gridItemMargin = giTable.new_usertype<GI::Margin>(
        "Margin",
        sol::constructors<
            GI::Margin() noexcept,
            GI::Margin(int) noexcept,
            GI::Margin(float) noexcept,
            GI::Margin(float, float, float, float) noexcept
        >()
    );
    // clang-format on

    gridItemMargin["left"]   = &GI::Margin::left;
    gridItemMargin["right"]  = &GI::Margin::right;
    gridItemMargin["top"]    = &GI::Margin::top;
    gridItemMargin["bottom"] = &GI::Margin::bottom;

    // clang-format off
    auto gridItemProperty = giTable.new_usertype<GI::Property>(
        "Property",
        sol::constructors<
            GI::Property() noexcept,
            GI::Property(GI::Keyword) noexcept,
            GI::Property(char const*) noexcept,
            GI::Property(juce::String const&) noexcept,
            GI::Property(int) noexcept,
            GI::Property(int, juce::String const&) noexcept,
            GI::Property(GI::Span) noexcept
        >()
    );
    // clang-format on

    gridItemProperty["hasSpan"]     = &GI::Property::hasSpan;
    gridItemProperty["hasAbsolute"] = &GI::Property::hasAbsolute;
    gridItemProperty["hasAuto"]     = &GI::Property::hasAuto;
    gridItemProperty["hasName"]     = &GI::Property::hasName;
    gridItemProperty["getName"]     = &GI::Property::getName;
    gridItemProperty["getNumber"]   = &GI::Property::getNumber;

    // clang-format off
    auto gridItemSpan = giTable.new_usertype<GI::Span>(
        "Span",
        sol::constructors<
            GI::Span(int) noexcept,
            GI::Span(int, juce::String const&) noexcept,
            GI::Span(juce::String const&) noexcept
        >()
    );
    // clang-format on

    gridItemSpan["number"] = &GI::Span::number;
    gridItemSpan["name"]   = &GI::Span::name;

    auto gridItemStartAndEndProperty     = giTable.new_usertype<GI::StartAndEndProperty>("StartAndEndProperty");
    gridItemStartAndEndProperty["start"] = &GI::StartAndEndProperty::start;
    gridItemStartAndEndProperty["end"]   = &GI::StartAndEndProperty::end;
}
} // namespace mc::lua::bindings
