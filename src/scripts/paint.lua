grey = juce.Colour.new(8,8,8,255);
black = juce.Colour.new(0,0,0,255);
white = juce.Colour.new(255,255,255,255);

function randomColor ()
  local r = random:nextInt(255)
  local g = random:nextInt(255)
  local b = random:nextInt(255)
  return juce.Colour.new(r, g, b, 255);
end

btn_1 = juce.TextButton.new(juce.String.new("Foo"))
btn_2 = juce.TextButton.new(juce.String.new("Bar"))
btn_3 = juce.TextButton.new(juce.String.new("Baz"))

function construct(comp)
  btn_1.onClick = function() print("Button 1") end
  btn_2.onClick = function() print("Button 2") end
  btn_3.onClick = function() comp:repaint() end
  comp:addAndMakeVisible(btn_1, -1)
  comp:addAndMakeVisible(btn_2, -1)
  comp:addAndMakeVisible(btn_3, -1)
end

function paint (comp, g)
  g:fillAll(black)

  g:setColour(randomColor())
  local area = comp:getLocalBounds():reduced(random:nextInt(150))
  g:fillRoundedRectangle(area:toFloat(), 5)
end

function resized(comp)
  local area = comp:getLocalBounds()
  local b = juce.RectangleInt.new(10,10,150,150)
  btn_1:setBounds(b)
  btn_2:setBounds(10,200,250,150)
  btn_3:setBounds(400,200,250,150)
end

function mouseDown(comp, event)
end

function test_BigInteger()
  local bigInt = juce.BigInteger.new()
  assert(bigInt:isZero())
  assert(not bigInt:isOne())

  assert(bigInt:getHighestBit() == -1)
  bigInt:setBit(0)
  assert(bigInt:getHighestBit() == 0)
  bigInt:setBit(1)
  assert(bigInt:getHighestBit() == 1)

  local other = juce.BigInteger.new()
  other:swapWith(bigInt)

  assert(bigInt:isZero())
  assert(not bigInt:isOne())
  assert(not other:isZero())
  assert(not other:isOne())
  assert(other:getHighestBit() == 1)

end

function unit_tests()
  test_BigInteger()
end