local function Content()
  local content = juce.Component.new()
  content:setComponentID(juce.String.new("Content"))

  function content:paint(g)
    g:setColour(juce.Colours.blue)
    g:fillAll()
  end

  return content
end

local function MainComponent()
  local mainComponent = juce.Component.new()
  mainComponent:setComponentID(juce.String.new("Main Window"))

  local content = Content()
  mainComponent:addAndMakeVisible(content)

  function mainComponent:paint(g)
    g:setColour(juce.Colours.red)
    g:fillAll()
  end

  function mainComponent:resized()
    content:setBounds(25, 25, 25, 25)
  end

  mainComponent:setSize(1024, 576)
  return mainComponent
end

return MainComponent()
