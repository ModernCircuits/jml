#include "MainComponent.h"

namespace Colors = juce::Colours;
using juce::Colour;
using juce::Graphics;

MainComponent::MainComponent() {
  setSize(600, 400);

  _lua.open_libraries(sol::lib::base);

  auto juceModule = _lua["juce"].get_or_create<sol::table>();

  // clang-format off
  using RectangleInt  = juce::Rectangle<int>;
  juceModule.new_usertype<RectangleInt>("RectangleInt",
    sol::constructors<RectangleInt(),RectangleInt(int,int,int,int)>(),
    "x",
    sol::property(&RectangleInt::getX, &RectangleInt::setX),
    "y",
    sol::property(&RectangleInt::getY, &RectangleInt::setY)
  );

  juceModule.new_usertype<Colour>("Colour",
    sol::constructors<Colour(),Colour(juce::uint8,juce::uint8,juce::uint8,juce::uint8)>()
  );

  auto g = juceModule.new_usertype<Graphics>("Graphics");
  g.set_function("fillAll", static_cast<void (Graphics::*)(juce::Colour) const>(&Graphics::fillAll));

  using juce::Random;
  auto r = juceModule.new_usertype<Random>("Random");
  r.set_function("nextBool", &Random::nextBool);
  r.set_function("nextFloat", &Random::nextFloat);
  r.set_function("nextDouble", &Random::nextDouble);
  r.set_function("nextInt", static_cast<int (Random::*)() noexcept>(&Random::nextInt));
  // clang-format on

  // _lua.script(R"(
  // 	function paint (g)
  // 		g:fillAll(black)
  // 	end
  // )");
  _lua["random"] = std::ref(juce::Random::getSystemRandom());
  _lua["white"] = Colors::white;
  _lua["black"] = Colors::black;
  _lua["active"] = false;
}

void MainComponent::paint(juce::Graphics &g) {
  _lua["g"] = std::ref(g);

  _lua.script_file(
      R"(C:\Developer\moderncircuits\tests\juce-lua\src\scripts\paint.lua)");
}

void MainComponent::resized() {}

auto MainComponent::mouseDown(juce::MouseEvent const &event) -> void {
  _lua.script(R"(
    active = not active
  )");
  repaint();
}
