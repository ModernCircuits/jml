local white = juce.Colour.new(255, 255, 255, 255)
local black = juce.Colour.new(  0,   0,   0, 255)
local red   = juce.Colour.new(255,   0,   0, 255)
local green = juce.Colour.new(  0, 255,   0, 255)
local blue  = juce.Colour.new(  0,   0, 255, 255)
local grey  = juce.Colour.new( 25,  25,  25, 255)

function randomColor ()
  local r = random:nextInt(255)
  local g = random:nextInt(255)
  local b = random:nextInt(255)
  return juce.Colour.new(r, g, b, 255);
end

local lcomp = juce.LuaComp.new()
local btn_1 = juce.TextButton.new(juce.String.new("Foo"))
local btn_2 = juce.TextButton.new(juce.String.new("Bar"))
local btn_3 = juce.TextButton.new(juce.String.new("Baz"))

lcomp:addAndMakeVisible(btn_1, -1)
lcomp:addAndMakeVisible(btn_2, -1)
lcomp:addAndMakeVisible(btn_3, -1)
btn_1.onClick = function() print("Button 1") end
btn_2.onClick = function() print("Button 2") end
btn_3.onClick = function() lcomp:repaint() end

function lcomp:paint(g, txt)
  g:setColour(randomColor())
  local area = lcomp:getLocalBounds():reduced(random:nextInt(150))
  g:fillRoundedRectangle(area:toFloat(), 5)
end

function lcomp:resized()
  local b = juce.RectangleInt.new(10,10,40,40)
  btn_1:setBounds(b)
  btn_2:setBounds(10,200,250,150)
  btn_3:setBounds(400,200,250,150)
end

function construct(comp)
  comp:addAndMakeVisible(lcomp, -1)
end

function paint (comp, g)
  g:fillAll(black)
end

function resized(comp)
  local area = comp:getLocalBounds()
  lcomp:setBounds(area)
end

function mouseDown(comp, event)
end
