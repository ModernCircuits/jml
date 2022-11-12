local black = juce.Colour.new(0, 0, 0, 255)
local grey = juce.Colour.new(53, 54, 59, 255)

local function makeSidebar()
  local this = juce.LuaComponent.new()

  local btn_1 = juce.TextButton.new(juce.String.new("Foo"))
  local btn_2 = juce.TextButton.new(juce.String.new("Bar"))
  local btn_3 = juce.TextButton.new(juce.String.new("Baz"))
  this:setComponentID(juce.String.new("Sidebar"))

  btn_1:setComponentID(juce.String.new("Foo"))
  btn_2:setComponentID(juce.String.new("Bar"))
  btn_3:setComponentID(juce.String.new("Baz"))

  this:addAndMakeVisible(btn_1)
  this:addAndMakeVisible(btn_2)
  this:addAndMakeVisible(btn_3)

  function this:paint(g)
    g:setColour(black)
    g:fillAll()
  end

  function this:resized()
    local area = this:getLocalBounds()
    btn_1:setBounds(area:removeFromBottom(75):reduced(4))
    btn_2:setBounds(area:removeFromBottom(75):reduced(4))
    btn_3:setBounds(area:removeFromBottom(75):reduced(4))
  end

  return this
end

local function makeContent()
  local content = juce.LuaComponent.new()
  content:setComponentID(juce.String.new("Content"))

  function content:paint(g)
    g:setColour(grey)
    g:fillAll()
  end

  function content:resized()
    local area = content:getLocalBounds()
  end

  return content
end

local function makeMainComponent()
  local mainComponent = juce.LuaComponent.new()
  local sidebar = makeSidebar()
  local content = makeContent()

  mainComponent:addAndMakeVisible(sidebar)
  mainComponent:addAndMakeVisible(content)
  mainComponent:setComponentID(juce.String.new("Zentrale"))
  mainComponent:setSize(1280, 720)

  function mainComponent:paint(g)
    g:setColour(black)
    g:fillAll()
  end

  function mainComponent:resized()
    local area = mainComponent:getLocalBounds()
    sidebar:setBounds(area:removeFromLeft(75):toNearestInt())
    content:setBounds(area:reduced(8))
  end

  return mainComponent
end

return makeMainComponent()
