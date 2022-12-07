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

local function buildComponent(spec)
    local c = juce.Component.new()
    c:setComponentID(juce.String.new(spec["name"]))

    local children = {}
    -- add children
    for k, v in ipairs(spec.children) do
        local child = v.build()
        children[#children + 1] = child
        c:addAndMakeVisible(child)
    end

    -- set size
    if spec["width"] ~= nil and spec["height"] ~= nil then
        c:setSize(spec["width"], spec["height"])
    end

    -- paint
    function c:paint(g)
        local area = c:getLocalBounds():reduced(spec.padding)
        g:setColour(spec.color)
        g:fillRect(area)
    end

    -- resized
    function c:resized()
        local area = c:getLocalBounds():reduced(spec.padding)
        local height = area:getHeight() / max(1, tableSize(children))
        for k in pairs(children) do
            children[k]:setBounds(area:removeFromTop(height))
            print("resize child")
        end
    end

    return c
end

local function fillComponentDefaults(spec)
    if spec["name"] == nil then
        spec["name"] = ""
    end

    if spec["color"] == nil then
        spec["color"] = juce.Colours.new()
    end

    if spec["padding"] == nil then
        spec["padding"] = 0
    end

    if spec["children"] == nil then
        spec["children"] = {}
    end

    return spec
end

function jml.Component(spec)
    spec["type"] = "Component"
    spec = fillComponentDefaults(spec)

    spec["build"] = function()
        return buildComponent(spec)
    end

    return spec
end

function jml.build(ui)
    return ui.build(ui)
end

-- EXAMPLE

return jml.build(
    jml.Component {
        ["name"] = "Main Window",
        ["color"] = juce.Colours.black,
        ["width"] = 500,
        ["height"] = 500,
        ["padding"] = 0,
        ["children"] = {
            jml.Component {
                ["name"] = "C1",
                ["padding"] = 4,
                ["color"] = juce.Colours.red
            },
            jml.Component {
                ["name"] = "C2",
                ["padding"] = 4,
                ["color"] = juce.Colours.green
            },
            jml.Component {
                ["name"] = "C2",
                ["padding"] = 4,
                ["color"] = juce.Colours.blue
            }
        }
    }
)
