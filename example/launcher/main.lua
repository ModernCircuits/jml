Theme = require("color")
Content = require("content")
Sidebar = require("sidebar")

local function MainWindow()
  local lnf = juce.LookAndFeel_V4.new()
  function lnf:drawButtonBackground(g, btn, c, isHighlighted, isDown)
    g:setColour(isHighlighted and Theme.lightGreen or Theme.lightBlue)
    g:fillRoundedRectangle(btn:getLocalBounds(), 8.0)
  end

  local component = juce.Component.new()
  component:setComponentID(juce.String.new("Zentrale"))

  local sidebar = Sidebar.new()
  component:addAndMakeVisible(sidebar)

  local content = Content.new()
  component:addAndMakeVisible(content)

  component:setLookAndFeel(lnf)
  component:setSize(1152, 648)

  function component:paint(g)
    g:setColour(Theme.black)
    g:fillAll()
  end

  function component:resized()
    local area = self:getLocalBounds()
    sidebar:setBounds(area:removeFromLeft(75))
    content:setBounds(area:reduced(8))
  end

  return component
end

return MainWindow()
