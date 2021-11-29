local grey = juce.Colour.new(8,8,8,255);
local black = juce.Colour.new(0,0,0,255);

if active then
  g:fillAll(grey)
else
  g:fillAll(black)
end