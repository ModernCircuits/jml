grey = juce.Colour.new(8,8,8,255);
black = juce.Colour.new(0,0,0,255);
white = juce.Colour.new(255,255,255,255);

lastX = 10
lastY = 10

function paint (comp, g)
  g:fillAll(black)
  g:setColour(white)
  g:fillRoundedRectangle(lastX, lastY, 20, 20, 5)
end

function mouseDown(comp, event)
  lastX = event.x
  lastY = event.y
  comp:repaint()
end