local mainComponent = juce.LuaComponent.new()
local btn_1 = juce.TextButton.new(juce.String.new("Foo"))
local btn_2 = juce.TextButton.new(juce.String.new("Bar"))
local btn_3 = juce.TextButton.new(juce.String.new("Baz"))

mainComponent:addAndMakeVisible(btn_1, -1)
mainComponent:addAndMakeVisible(btn_2, -1)
mainComponent:addAndMakeVisible(btn_3, -1)
btn_1.onClick = function() print("Button 1") end
btn_2.onClick = function() print("Button 2") end
btn_3.onClick = function() mainComponent:repaint() end

function mainComponent:paint(g, txt)
  g:setColour(juce.Colours.cadetblue)
  local area = mainComponent:getLocalBounds():reduced(random:nextInt(150))
  g:fillRoundedRectangle(area:toFloat(), 5)
end

function mainComponent:resized()
  local b = juce.RectangleInt.new(10, 10, 40, 40)
  btn_1:setBounds(b)
  btn_2:setBounds(10, 200, 250, 150)
  btn_3:setBounds(400, 200, 250, 150)
end

function construct(comp) comp:addAndMakeVisible(mainComponent, -1) end

function paint(comp, g) g:fillAll(juce.Colours.black) end

function resized(comp)
  local area = comp:getLocalBounds()
  mainComponent:setBounds(area)
end

function mouseDown(comp, event) end
