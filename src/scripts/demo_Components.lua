local function randomColorWithAlpha(alpha)
  local sysRandom = juce.Random.getSystemRandom()
  local r = sysRandom:nextInt(255)
  local g = sysRandom:nextInt(255)
  local b = sysRandom:nextInt(255)
  return juce.Colour.new(r, g, b, alpha)
end

local function randomColor()
  return randomColorWithAlpha(255)
end



local mainComponent = juce.LuaComponent.new()
local btn_1 = juce.TextButton.new(juce.String.new("Foo"))
local btn_2 = juce.TextButton.new(juce.String.new("Baz"))
local slider_1 = juce.Slider.new()
local topColor = juce.Colours.cadetblue
local bottomColor = juce.Colours.black

mainComponent:addAndMakeVisible(btn_1)
mainComponent:addAndMakeVisible(btn_2)
mainComponent:addAndMakeVisible(slider_1)

slider_1.onValueChange = function()
  slider_1:setColour(juce.SliderColourIds.thumbColourId, randomColor())
end

btn_1.onClick = function()
  print("Button 1")
end
btn_2.onClick = function()
  mainComponent:repaint()
end



function mainComponent:paint(g)
  local gradient = juce.ColourGradient.vertical(topColor, bottomColor, mainComponent:getLocalBounds())
  g:setGradientFill(gradient)
  g:fillAll()
end

function mainComponent:resized()
  local area = mainComponent:getLocalBounds()
  print(area)
  local btn1Area = area:removeFromTop(50):reduced(5)
  btn_1:setBounds(btn1Area)
  btn_2:setBounds(400, 200, 250, 150)
  slider_1:setBounds(10, 200, 250, 150)
end

function mainComponent:mouseDown()
  topColor = randomColor()
  bottomColor = randomColor()
  mainComponent:repaint()
end

lnf = juce.LuaLookAndFeel.new()
function lnf:drawButtonBackground(g, btn, color, highlighted, down)
	print("foo")
	g:fillAll(color)
	--g:fillRoundedRectangle(btn:getBounds():toFloat(), 5.0)
end
mainComponent:setLookAndFeel(lnf)

local timer = juce.LuaTimer.new()
function timer:timerCallback()
  topColor = randomColor()
  bottomColor = randomColor()
  mainComponent:repaint()
end
timer:startTimer(2000)

return mainComponent
