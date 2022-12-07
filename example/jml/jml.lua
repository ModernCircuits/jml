local jml = {}

local function tableSize(t)
    local count = 0
    for k in pairs(t) do
        count = count + 1
    end
    return count
end

local function max(lhs, rhs)
    if lhs > rhs then
        return lhs
    end
    return rhs
end

local function setEmptyProperties(spec, properties)
    local common = {
        {"id", ""},
        {"name", ""},
        {"padding", 0},
        {"margin", 0}
    }

    local addProperty = function(k, v)
        local id = v[1]
        local value = v[2]
        if spec[id] == nil then
            spec[id] = value
        end
    end

    for k, v in pairs(common) do
        addProperty(k, v)
    end

    for k, v in pairs(properties) do
        addProperty(k, v)
    end

    return spec
end

function jml.Component(spec)
    local properties = {
        {"fill", juce.Colour.new()},
        {"children", {}},
        {"layout", "vertical"}
    }
    spec = setEmptyProperties(spec, properties)

    -- BUILD
    spec.build = function()
        local c = juce.Component.new()
        c:setComponentID(juce.String.new(spec.id))

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

            local size = 0
            local numChildren = max(1, tableSize(spec.children))
            if spec["layout"] == "vertical" then
                size = area:getHeight() / numChildren
            else
                size = area:getWidth() / numChildren
            end

            for k in pairs(spec.children) do
                local c = spec.children[k].component
                local margin = spec.children[k].margin

                if spec["layout"] == "vertical" then
                    c:setBounds(area:removeFromTop(size):reduced(margin))
                else
                    c:setBounds(area:removeFromLeft(size):reduced(margin))
                end
            end
        end

        return c
    end

    return spec
end

function jml.TextButton(spec)
    local properties = {{"text", ""}}
    spec = setEmptyProperties(spec, properties)

    -- BUILD
    spec.build = function()
        local btn = juce.TextButton.new(juce.String.new(spec.text))
        btn:setComponentID(juce.String.new(spec.id))
        return btn
    end

    return spec
end

function jml.Slider(spec)
    local properties = {}
    spec = setEmptyProperties(spec, properties)

    -- BUILD
    spec.build = function()
        local s = juce.Slider.new()
        s:setComponentID(juce.String.new(spec.id))

        if spec["range"] ~= nil then
            s:setRange(spec.range["start"], spec.range["stop"], spec.range["interval"])
        end

        return s
    end
    return spec
end

function jml.ComboBox(spec)
    local properties = {}
    spec = setEmptyProperties(spec, properties)

    -- BUILD
    spec.build = function()
        local cb = juce.ComboBox.new(juce.String.new(spec["name"]))
        cb:setComponentID(juce.String.new(spec.id))
        return cb
    end

    return spec
end

function jml.build(ui)
    return ui.build()
end

return jml
