Theme = require("theme")

local sidebar = {}

function sidebar.new()
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
        g:setColour(Theme.black)
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

return sidebar
