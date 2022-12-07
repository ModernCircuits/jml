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

local function setEmptyPropertiesToDefaults(spec)
    local defaults = {
        {"id", ""},
        {"padding", 0},
        {"margin", 0}
    }

    for k, v in pairs(defaults) do
        local id = v[1]
        local value = v[2]
        if spec[id] == nil then
            spec[id] = value
        end
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
    spec = setEmptyPropertiesToDefaults(spec)

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
    spec = setEmptyPropertiesToDefaults(spec)
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
    spec = setEmptyPropertiesToDefaults(spec)
    if spec["range"] == nil then
        spec["range"] = {
            ["start"] = 0.0,
            ["stop"] = 1.0,
            ["interval"] = 0.0
        }
    end

    spec["build"] = function()
        local s = juce.Slider.new()
        s:setComponentID(juce.String.new(spec["id"]))
        s:setRange(spec.range["start"], spec.range["stop"], spec.range["interval"])
        return s
    end

    return spec
end

function jml.build(ui)
    return ui.build(ui)
end

return jml
