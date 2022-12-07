local function Content(name)
  local content = juce.Component.new()
  content:setComponentID(juce.String.new(name))

  function content:paint(g)
    g:setColour(juce.Colours.red)
    g:fillAll()
  end

  return content
end

local function MainComponent()
  local mainComponent = juce.Component.new()
  local c1 = Content("C1")
  local c2 = Content("C2")
  local c3 = Content("C3")

  mainComponent:setComponentID(juce.String.new("Main Window"))
  mainComponent:addAndMakeVisible(c1)
  mainComponent:addAndMakeVisible(c2)
  mainComponent:addAndMakeVisible(c3)

  function mainComponent:paint(g)
    g:setColour(juce.Colours.blue)
    g:fillAll()
  end

  function mainComponent:resized()
    c1:setBounds(25, 25, 25, 25)
    c2:setBounds(50, 50, 25, 25)
    c3:setBounds(75, 75, 25, 25)
  end

  mainComponent:setSize(640, 480)
  return mainComponent
end

return MainComponent()
