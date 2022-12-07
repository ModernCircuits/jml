-- JML
local jml = {}

local function tableSize(t)
    local count = 0
    for k in pairs(t) do
        count = count + 1
    end
    return count
end

local function min(lhs, rhs)
    if lhs < rhs then
        return lhs
    end
    return rhs
end

local function max(lhs, rhs)
    if lhs > rhs then
        return lhs
    end
    return rhs
end

local function setDefaultProperties(spec, t)
    spec["type"] = t

    if spec["id"] == nil then
        spec["id"] = ""
    end

    if spec["padding"] == nil then
        spec["padding"] = ""
    end

    if spec["margin"] == nil then
        spec["margin"] = 0
    end

    return spec
end

local function buildComponent(spec)
    local c = juce.Component.new()
    c:setComponentID(juce.String.new(spec["id"]))

    -- add children
    for k, v in ipairs(spec.children) do
        v.component = v.build()
        c:addAndMakeVisible(v.component)
    end

    -- set size
    if spec["width"] ~= nil and spec["height"] ~= nil then
        c:setSize(spec["width"], spec["height"])
    end

    -- paint
    function c:paint(g)
        local area = c:getLocalBounds()
        g:setColour(spec.fill)
        g:fillRect(area)
    end

    -- resized
    function c:resized()
        local area = c:getLocalBounds():reduced(spec.padding)
        local height = area:getHeight() / max(1, tableSize(spec.children))
        for k in pairs(spec.children) do
            local c = spec.children[k].component
            local margin = spec.children[k].margin
            local childArea = area:removeFromTop(height):reduced(margin)
            c:setBounds(childArea)
        end
    end

    return c
end

function jml.Component(spec)
    spec = setDefaultProperties(spec, "Component")

    if spec["fill"] == nil then
        spec["fill"] = juce.Colours.new()
    end

    if spec["children"] == nil then
        spec["children"] = {}
    end

    spec["build"] = function()
        return buildComponent(spec)
    end

    return spec
end

function jml.TextButton(spec)
    spec = setDefaultProperties(spec, "TextButton")
    if spec["text"] == nil then
        spec["text"] = ""
    end

    spec["build"] = function()
        local btn = juce.TextButton.new(juce.String.new(spec["text"]))
        btn:setComponentID(juce.String.new(spec["id"]))
        return btn
    end

    return spec
end

function jml.Slider(spec)
    spec = setDefaultProperties(spec, "Slider")

    spec["build"] = function()
        local slider = juce.Slider.new()
        slider:setComponentID(juce.String.new(spec["id"]))
        return slider
    end

    return spec
end

function jml.build(ui)
    return ui.build(ui)
end

-- EXAMPLE

local ui =
    jml.Component {
    ["id"] = "Main Window",
    ["fill"] = juce.Colours.black,
    ["width"] = 500,
    ["height"] = 500,
    ["padding"] = 8,
    ["children"] = {
        jml.TextButton {
            ["id"] = "C1",
            ["text"] = "Button",
            ["margin"] = 4
        },
        jml.Component {
            ["id"] = "C2",
            ["margin"] = 4,
            ["fill"] = juce.Colours.green
        },
        jml.Slider {
            ["id"] = "C2"
        },
        jml.Component {
            ["id"] = "C2",
            ["margin"] = 4,
            ["fill"] = juce.Colours.blue
        }
    }
}

return jml.build(ui)
