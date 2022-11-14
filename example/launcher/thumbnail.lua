Theme = require("theme")

local thumbnail = {}

function thumbnail.new(name)
    local this = {}
    this.component = juce.Component.new()
    this.component:setComponentID(juce.String.new(name))

    this.tag1 = juce.TextButton.new(juce.String.new("tag1"))
    this.tag2 = juce.TextButton.new(juce.String.new("tag2"))
    this.tag3 = juce.TextButton.new(juce.String.new("tag3"))

    this.component:addAndMakeVisible(this.tag1)
    this.component:addAndMakeVisible(this.tag2)
    this.component:addAndMakeVisible(this.tag3)

    this.tag1:setComponentID(juce.String.new("tag1"))
    this.tag2:setComponentID(juce.String.new("tag2"))
    this.tag3:setComponentID(juce.String.new("tag3"))

    local imageArea = juce.RectangleInt.new(0, 0, 0, 0)

    function this.component:paint(g)
        g:setColour(Theme.black)
        g:fillRoundedRectangle(imageArea, 8.0)
    end

    function this.component:resized()
        local area = self:getLocalBounds()
        local buttonArea = area:removeFromBottom(40)
        imageArea = area:reduced(2)
        local width = buttonArea:getWidth() / 3
        this.tag1:setBounds(buttonArea:removeFromLeft(width):reduced(2))
        this.tag2:setBounds(buttonArea:removeFromLeft(width):reduced(2))
        this.tag3:setBounds(buttonArea:removeFromLeft(width):reduced(2))
    end

    return this
end

return thumbnail
