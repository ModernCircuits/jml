#include "Grid.hpp"

#include <juce_gui_basics/juce_gui_basics.h>

namespace juce {
auto operator==(GridItem const&, GridItem const&) -> bool { return false; }
auto operator!=(GridItem const&, GridItem const&) -> bool { return true; }
auto operator==(Grid::TrackInfo const&, Grid::TrackInfo const&) -> bool { return false; }
auto operator!=(Grid::TrackInfo const&, Grid::TrackInfo const&) -> bool { return true; }
} // namespace juce

auto juce_Grid(sol::table& state) -> void
{
    // auto noOperators                           = sol::automagic_enrollments{};
    // noOperators.less_than_operator             = false;
    // noOperators.less_than_or_equal_to_operator = false;
    // noOperators.equal_to_operator              = false;

    juce_ArrayImpl<juce::GridItem>(state, "Array_GridItem");
    juce_ArrayImpl<juce::Grid::TrackInfo>(state, "Array_GridTrackInfo");

    auto grid = state.new_usertype<juce::Grid>("Grid");

    // juce::Grid::JustifyItems
    state.new_enum(                       //
        "GridJustifyItems",               //
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
    state.new_enum(                     //
        "GridAlignItems",               //
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
    state.new_enum(                               //
        "GridJustifyContent",                     //
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
    state.new_enum(                             //
        "GridAlignContent",                     //
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
    state.new_enum(                       //
        "GridAutoFlow",                   //
        "row",                            //
        juce::Grid::AutoFlow::row,        //
        "column",                         //
        juce::Grid::AutoFlow::column,     //
        "rowDense",                       //
        juce::Grid::AutoFlow::rowDense,   //
        "columnDense",                    //
        juce::Grid::AutoFlow::columnDense //
    );

    auto fr        = state.new_usertype<juce::Grid::Fr>("GridFr", sol::constructors<juce::Grid::Fr(int)>());
    fr["fraction"] = &juce::Grid::Fr::fraction;

    auto px      = state.new_usertype<juce::Grid::Px>("GridPx", sol::constructors<juce::Grid::Px(float)>());
    px["pixels"] = &juce::Grid::Px::pixels;

    auto ti = state.new_usertype<juce::Grid::TrackInfo>("GridTrackInfo");

    ti["isAuto"]           = &juce::Grid::TrackInfo::isAuto;
    ti["isFractional"]     = &juce::Grid::TrackInfo::isFractional;
    ti["isPixels"]         = &juce::Grid::TrackInfo::isPixels;
    ti["getStartLineName"] = &juce::Grid::TrackInfo::getStartLineName;
    ti["getEndLineName"]   = &juce::Grid::TrackInfo::getEndLineName;
    ti["getSize"]          = &juce::Grid::TrackInfo::getSize;

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
}
