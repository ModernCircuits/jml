local black = juce.Colour.new(0, 0, 0, 255)
local grey = juce.Colour.new(53, 54, 59, 255)
local lightViolet = juce.Colour.new(93, 152, 255, 255)
local lightBlue = juce.Colour.new(82, 178, 225, 255)
local lightGreen = juce.Colour.new(120, 192, 206, 255)

local function PluginThumbnail(name)
  local thumbnail = juce.Component.new()
  thumbnail:setComponentID(juce.String.new(name))

  local tag1 = juce.TextButton.new(juce.String.new("tag1"))
  local tag2 = juce.TextButton.new(juce.String.new("tag2"))
  local tag3 = juce.TextButton.new(juce.String.new("tag3"))

  thumbnail:addAndMakeVisible(tag1)
  thumbnail:addAndMakeVisible(tag2)
  thumbnail:addAndMakeVisible(tag3)

  tag1:setComponentID(juce.String.new("tag1"))
  tag2:setComponentID(juce.String.new("tag2"))
  tag3:setComponentID(juce.String.new("tag3"))

  local imageArea = juce.RectangleInt.new(0, 0, 0, 0)

  function thumbnail:paint(g)
    g:setColour(juce.Colours.black)
    g:fillRoundedRectangle(imageArea, 8.0)
  end

  function thumbnail:resized()
    local area = thumbnail:getLocalBounds()
    local buttonArea = area:removeFromBottom(40)
    imageArea = area:reduced(2)
    local width = buttonArea:getWidth() / 3
    tag1:setBounds(buttonArea:removeFromLeft(width):toNearestInt():reduced(2))
    tag2:setBounds(buttonArea:removeFromLeft(width):toNearestInt():reduced(2))
    tag3:setBounds(buttonArea:removeFromLeft(width):toNearestInt():reduced(2))
  end

  return thumbnail
end

local function Sidebar()
  local sidebar = juce.Component.new()

  local plug = juce.TextButton.new(juce.String.new("Plug"))
  local music = juce.TextButton.new(juce.String.new("Music"))
  local rocket = juce.TextButton.new(juce.String.new("Rocket"))
  local star = juce.TextButton.new(juce.String.new("Star"))
  sidebar:setComponentID(juce.String.new("Sidebar"))

  plug:setComponentID(juce.String.new("Plug"))
  music:setComponentID(juce.String.new("Music"))
  rocket:setComponentID(juce.String.new("Rocket"))
  star:setComponentID(juce.String.new("Star"))

  sidebar:addAndMakeVisible(music)
  sidebar:addAndMakeVisible(plug)
  sidebar:addAndMakeVisible(rocket)
  sidebar:addAndMakeVisible(star)

  function sidebar:paint(g)
    g:setColour(black)
    g:fillAll()
  end

  function sidebar:resized()
    local area = sidebar:getLocalBounds():reduced(4)
    star:setBounds(area:removeFromBottom(60):reduced(4))
    rocket:setBounds(area:removeFromBottom(60):reduced(4))
    music:setBounds(area:removeFromBottom(60):reduced(4))
    plug:setBounds(area:removeFromBottom(60):reduced(4))
  end

  return sidebar
end

local function ContentHeader()
  local header = juce.Component.new()
  header:setComponentID(juce.String.new("Content Header"))

  local titleText = juce.String.new("Installed Products")
  local title = juce.Label.new(titleText, titleText)
  title:setComponentID(titleText)

  local searchText = juce.String.new("Search")
  local search = juce.Label.new(searchText, searchText)
  search:setComponentID(searchText)

  header:addAndMakeVisible(title)
  header:addAndMakeVisible(search)

  function header:resized()
    local area = header:getLocalBounds():reduced(16)
    title:setBounds(area:removeFromLeft(150):toNearestInt())
    search:setBounds(area:removeFromLeft(150):toNearestInt())
  end

  return header
end

local function MainContent()
  local content = juce.Component.new()
  local header = ContentHeader()
  local dynamic = PluginThumbnail("ASIC Dynamic")
  local filter = PluginThumbnail("ASIC Filter")
  local shape = PluginThumbnail("ASIC Shape")
  local space = PluginThumbnail("ASIC Space")

  content:setComponentID(juce.String.new("Content"))
  content:addAndMakeVisible(header)
  content:addAndMakeVisible(dynamic)
  content:addAndMakeVisible(filter)
  content:addAndMakeVisible(shape)
  content:addAndMakeVisible(space)

  function content:paint(g)
    g:setColour(grey)
    g:fillRoundedRectangle(content:getLocalBounds(), 8.0)
  end

  function content:resized()
    local area = content:getLocalBounds():reduced(16)
    header:setBounds(area:removeFromTop(75):reduced(8):toNearestInt())

    local height = area:getHeight() / 2.5
    local width = area:getWidth() / 4
    local thumbnailArea = area:removeFromTop(height):reduced(8)
    dynamic:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    filter:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    shape:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    space:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
  end

  return content
end

local function MainWindow()
  local lnf = juce.LookAndFeel_V4.new()
  function lnf:drawButtonBackground(g, btn, color, isHighlighted, isDown)
    g:setColour(isHighlighted and lightGreen or lightBlue)
    g:fillRoundedRectangle(btn:getLocalBounds(), 8.0)
  end

  local mainComponent = juce.Component.new()
  mainComponent:setComponentID(juce.String.new("Zentrale"))

  local sidebar = Sidebar()
  mainComponent:addAndMakeVisible(sidebar)

  local content = MainContent()
  mainComponent:addAndMakeVisible(content)

  mainComponent:setLookAndFeel(lnf)
  mainComponent:setSize(1152, 648)

  function mainComponent:paint(g)
    g:setColour(black)
    g:fillAll()
  end

  function mainComponent:resized()
    local area = mainComponent:getLocalBounds()
    sidebar:setBounds(area:removeFromLeft(75):toNearestInt())
    content:setBounds(area:reduced( 8))
  end

  return mainComponent
end

return MainWindow()
