Theme = require("theme")
PluginThumbnail = require("thumbnail")

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

local content = {}

function content.new()
  local function callback()
    print("txt")
  end

  local component = juce.Component.new()
  local header = ContentHeader()
  local dynamic = PluginThumbnail.new("ASIC Dynamic")
  local filter = PluginThumbnail.new("ASIC Filter")
  local shape = PluginThumbnail.new("ASIC Shape")
  local space = PluginThumbnail.new("ASIC Space")

  local listModel = juce.ListBoxModel.new()
  function listModel:getNumRows()
    return 24
  end

  function listModel:paintListBoxItem(rowNumber, g, width, height, rowIsSelected)
    g:setColour(juce.Colours.black)
    g:fillRect(juce.RectangleInt.new(0, 0, width, height):reduced(2))
  end

  local list = juce.ListBox.new()
  list:setModel(listModel)

  dynamic.tag1.onClick = function()
    print("Dynamic: 1")
  end
  dynamic.tag2.onClick = function()
    print("Dynamic: 2")
  end
  dynamic.tag3.onClick = function()
    print("Dynamic: 3")
  end

  filter.tag1.onClick = function()
    print("filter: 1")
  end
  filter.tag2.onClick = function()
    print("filter: 2")
  end
  filter.tag3.onClick = function()
    print("filter: 3")
  end

  shape.tag1.onClick = function()
    print("shape: 1")
  end
  shape.tag2.onClick = function()
    print("shape: 2")
  end
  shape.tag3.onClick = function()
    print("shape: 3")
  end

  space.tag1.onClick = function()
    print("space: 1")
  end
  space.tag2.onClick = function()
    print("space: 2")
  end
  space.tag3.onClick = function()
    print("space: 3")
  end

  component:setComponentID(juce.String.new("Content"))
  component:addAndMakeVisible(header)
  component:addAndMakeVisible(dynamic.component)
  component:addAndMakeVisible(filter.component)
  component:addAndMakeVisible(shape.component)
  component:addAndMakeVisible(space.component)
  component:addAndMakeVisible(list)

  function component:paint(g)
    g:setColour(Theme.grey)
    g:fillRoundedRectangle(component:getLocalBounds(), 8.0)
  end

  function component:resized()
    local area = self:getLocalBounds():reduced(16)
    header:setBounds(area:removeFromTop(75):reduced(8))

    local height = area:getHeight() / 2.5
    local width = area:getWidth() / 4
    local thumbnailArea = area:removeFromTop(height):reduced(8)
    dynamic.component:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    filter.component:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    shape.component:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    space.component:setBounds(thumbnailArea:removeFromLeft(width):reduced(8))
    list:setBounds(area)
  end

  return component
end

return content
