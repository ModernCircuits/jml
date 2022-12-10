local function Canvas(name, color)
  local content = juce.Component.new()
  content:setComponentID(juce.String.new(name))

  function content:paint(g)
    g:setColour(color)
    g:fillAll()
  end

  return content
end

local function MainComponent()
  local mainComponent = juce.Component.new()
  mainComponent:setComponentID(juce.String.new("juce.Grid Example"))

  local red = Canvas("RED", juce.Colours.red)
  local green = Canvas("GREEN", juce.Colours.green)
  local blue = Canvas("BLUE", juce.Colours.blue)

  mainComponent:addAndMakeVisible(red)
  mainComponent:addAndMakeVisible(green)
  mainComponent:addAndMakeVisible(blue)

  function mainComponent:paint(g)
    g:setColour(juce.Colours.white)
    g:fillAll()
  end

  function mainComponent:resized()
    local grid = juce.Grid.new()
    grid:setGap(juce.Grid.Px.new(8.0))

    grid.templateRows:add(juce.Grid.TrackInfo.new(juce.Grid.Fr.new(1)))
    grid.templateRows:add(juce.Grid.TrackInfo.new(juce.Grid.Fr.new(2)))
    grid.templateRows:add(juce.Grid.TrackInfo.new(juce.Grid.Fr.new(1)))
    grid.templateColumns:add(juce.Grid.TrackInfo.new(juce.Grid.Fr.new(1)))

    grid.items:add(juce.GridItem.new(red))
    grid.items:add(juce.GridItem.new(green))
    grid.items:add(juce.GridItem.new(blue))

    grid:performLayout(mainComponent:getLocalBounds())
  end

  mainComponent:setSize(720, 480)
  return mainComponent
end

return MainComponent()
