grey = juce.Colour.new(8,8,8,255);
black = juce.Colour.new(0,0,0,255);
white = juce.Colour.new(255,255,255,255);

function randomColor ()
  local r = random:nextInt(255)
  local g = random:nextInt(255)
  local b = random:nextInt(255)
  return juce.Colour.new(r, g, b, 255);
end

button = juce.TextButton.new(juce.String.new("Test"))

function construct(comp)
  comp:addAndMakeVisible(button, -1)
end

function paint (comp, g)
  g:fillAll(black)

  g:setColour(randomColor())
  local area = comp:getLocalBounds():reduced(random:nextInt(150))
  g:fillRoundedRectangle(area:toFloat(), 5)
end

function resized(comp)
  button:setBounds(comp:getLocalBounds():reduced(160))
end

function mouseDown(comp, event)
  comp:repaint()
end