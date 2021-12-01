local mainComponent = juce.LuaComponent.new()
local btn_1 = juce.TextButton.new(juce.String.new("Foo"))
local btn_2 = juce.TextButton.new(juce.String.new("Baz"))
local slider_1 = juce.Slider.new()

mainComponent:addAndMakeVisible(btn_1, -1)
mainComponent:addAndMakeVisible(btn_2, -1)
mainComponent:addAndMakeVisible(slider_1, -1)

btn_1.onClick = function() print("Button 1") end
btn_2.onClick = function() mainComponent:repaint() end

function mainComponent:paint(g)
  g:setColour(juce.Colours.cadetblue)
  g:fillAll()
end

function mainComponent:resized()
  local b = juce.RectangleInt.new(10, 10, 40, 40)
  btn_1:setBounds(b)
  btn_2:setBounds(400, 200, 250, 150)
  slider_1:setBounds(10, 200, 250, 150)
end

return mainComponent