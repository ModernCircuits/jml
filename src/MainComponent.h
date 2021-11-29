#pragma once

#include <juce_gui_extra/juce_gui_extra.h>

#define SOL_ALL_SAFETIES_ON 1
#include <sol/sol.hpp>

struct MainComponent : juce::Component {
  MainComponent();

  void paint(juce::Graphics &) override;
  void resized() override;

private:
  auto mouseDown(juce::MouseEvent const &event) -> void override;
  sol::state _lua;
  JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(MainComponent)
};
