local black = juce.Colour.new(0, 0, 0, 255)
local grey = juce.Colour.new(53, 54, 59, 255)
local lightViolet = juce.Colour.new(93, 152, 255, 255)
local lightBlue = juce.Colour.new(82, 178, 225, 255)
local lightGreen = juce.Colour.new(120, 192, 206, 255)

local function PluginThumbnail(name, onTagClick)
  local component = juce.Component.new()
  component:setComponentID(juce.String.new(name))

  local tag1 = juce.TextButton.new(juce.String.new("tag1"))
  local tag2 = juce.TextButton.new(juce.String.new("tag2"))
  local tag3 = juce.TextButton.new(juce.String.new("tag3"))

  component:addAndMakeVisible(tag1)
  component:addAndMakeVisible(tag2)
  component:addAndMakeVisible(tag3)

  tag1:setComponentID(juce.String.new("tag1"))
  tag2:setComponentID(juce.String.new("tag2"))
  tag3:setComponentID(juce.String.new("tag3"))

  tag1.onClick = function()
    onTagClick(string.format("%s: 1", name))
  end
  tag2.onClick = function()
    onTagClick(string.format("%s: 2", name))
  end
  tag3.onClick = function()
    onTagClick(string.format("%s: 3", name))
  end

  local imageArea = juce.RectangleInt.new(0, 0, 0, 0)

  function component:paint(g)
    g:setColour(juce.Colours.black)
    g:fillRoundedRectangle(imageArea, 8.0)
  end

  function component:resized()
    local area = self:getLocalBounds()
    local buttonArea = area:removeFromBottom(40)
    imageArea = area:reduced(2)
    local width = buttonArea:getWidth() / 3
    tag1:setBounds(buttonArea:removeFromLeft(width):reduced(2))
    tag2:setBounds(buttonArea:removeFromLeft(width):reduced(2))
    tag3:setBounds(buttonArea:removeFromLeft(width):reduced(2))
  end

  return component
end

local function Sidebar()
  local component = juce.Component.new()

  local plug = juce.TextButton.new(juce.String.new("Plug"))
  local music = juce.TextButton.new(juce.String.new("Music"))
  local rocket = juce.TextButton.new(juce.String.new("Rocket"))
  local star = juce.TextButton.new(juce.String.new("Star"))
  component:setComponentID(juce.String.new("Sidebar"))

  plug:setComponentID(juce.String.new("Plug"))
  music:setComponentID(juce.String.new("Music"))
  rocket:setComponentID(juce.String.new("Rocket"))
  star:setComponentID(juce.String.new("Star"))

  component:addAndMakeVisible(music)
  component:addAndMakeVisible(plug)
  component:addAndMakeVisible(rocket)
  component:addAndMakeVisible(star)

  function component:paint(g)
    g:setColour(black)
    g:fillAll()
  end

  function component:resized()
    local area = self:getLocalBounds():reduced(4)
    star:setBounds(area:removeFromBottom(60):reduced(4))
    rocket:setBounds(area:removeFromBottom(60):reduced(4))
    music:setBounds(area:removeFromBottom(60):reduced(4))
    plug:setBounds(area:removeFromBottom(60):reduced(4))
  end

  return component
end

local function ContentHeader()
  local component = juce.Component.new()
  component:setComponentID(juce.String.new("Content component"))

  local titleText = juce.String.new("Installed Products")
  local title = juce.Label.new(titleText, titleText)
  title:setComponentID(titleText)
  title:setFont(juce.Font.new(24.0))
  component:addAndMakeVisible(title)

  local searchText = juce.String.new("Search")
  local search = juce.Label.new(searchText, searchText)
  search:setComponentID(searchText)
  search:setJustificationType(juce.Justification.new(juce.JustificationFlags.centred))
  search:setFont(juce.Font.new(24.0))
  component:addAndMakeVisible(search)

  local music = juce.TextButton.new(juce.String.new("Music"))
  music:setComponentID(juce.String.new("Music"))
  component:addAndMakeVisible(music)

  local chat = juce.TextButton.new(juce.String.new("Chat"))
  chat:setComponentID(juce.String.new("Chat"))
  component:addAndMakeVisible(chat)

  local user = juce.TextButton.new(juce.String.new("User"))
  user:setComponentID(juce.String.new("User"))
  component:addAndMakeVisible(user)

  function component:resized()
    local area = self:getLocalBounds():reduced(16)
    title:setBounds(area:removeFromLeft(200))

    user:setBounds(area:removeFromRight(50):reduced(2))
    chat:setBounds(area:removeFromRight(50):reduced(2))
    music:setBounds(area:removeFromRight(50):reduced(2))
    area:removeFromRight(50)

    search:setBounds(area)
  end

  return component
end

local function MainContent()
  local function callback(txt)
    print(txt)
  end

  local component = juce.Component.new()
  local header = ContentHeader()
  local dynamic = PluginThumbnail("ASIC Dynamic", callback)
  local filter = PluginThumbnail("ASIC Filter", callback)
  local shape = PluginThumbnail("ASIC Shape", callback)
  local space = PluginThumbnail("ASIC Space", callback)

  component:setComponentID(juce.String.new("Content"))
  component:addAndMakeVisible(header)
  component:addAndMakeVisible(dynamic)
  component:addAndMakeVisible(filter)
  component:addAndMakeVisible(shape)
  component:addAndMakeVisible(space)

  function component:paint(g)
    g:setColour(grey)
    g:fillRoundedRectangle(component:getLocalBounds(), 8.0)
  end

  function component:resized()
    local area = self:getLocalBounds():reduced(16)
    header:setBounds(area:removeFromTop(75):reduced(8))

    local height = area:getHeight() / 2.5
    local width = area:getWidth() / 4
    local thumbnailArea = area:removeFromTop(height):reduced(8)
    dynamic:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    filter:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    shape:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    space:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
  end

  return component
end

local function MainWindow()
  local lnf = juce.LookAndFeel_V4.new()
  function lnf:drawButtonBackground(g, btn, color, isHighlighted, isDown)
    g:setColour(isHighlighted and lightGreen or lightBlue)
    g:fillRoundedRectangle(btn:getLocalBounds(), 8.0)
  end

  local component = juce.Component.new()
  component:setComponentID(juce.String.new("Zentrale"))

  local sidebar = Sidebar()
  component:addAndMakeVisible(sidebar)

  local content = MainContent()
  component:addAndMakeVisible(content)

  component:setLookAndFeel(lnf)
  component:setSize(1152, 648)

  function component:paint(g)
    g:setColour(black)
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
