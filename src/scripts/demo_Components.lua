function randomColor() return randomColorWithAlpha(255) end

function randomColorWithAlpha(alpha)
  local sysRandom = juce.Random.getSystemRandom()
  local r = sysRandom:nextInt(255)
  local g = sysRandom:nextInt(255)
  local b = sysRandom:nextInt(255)
  return juce.Colour.new(r, g, b, alpha)
end

local mainComponent = juce.LuaComponent.new()
local btn_1 = juce.TextButton.new(juce.String.new("Foo"))
local btn_2 = juce.TextButton.new(juce.String.new("Baz"))
local slider_1 = juce.Slider.new()
local color = juce.Colours.cadetblue;

mainComponent:addAndMakeVisible(btn_1)
mainComponent:addAndMakeVisible(btn_2)
mainComponent:addAndMakeVisible(slider_1)

btn_1.onClick = function() print("Button 1") end
btn_2.onClick = function() mainComponent:repaint() end

function mainComponent:paint(g)
  g:setColour(color)
  g:fillAll()
end

function mainComponent:resized()
  local area = mainComponent:getLocalBounds()
  local btn1Area = area:removeFromTop(50):reduced(5)
  btn_1:setBounds(btn1Area)
  btn_2:setBounds(400, 200, 250, 150)
  slider_1:setBounds(10, 200, 250, 150)
end

function mainComponent:mouseDown()
  color = randomColor()
  mainComponent:repaint()
end

return mainComponent
