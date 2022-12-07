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
    spec =
        setEmptyProperties(
        spec,
        {
            {"fill", juce.Colour.new()},
            {"children", {}},
            {"layout", "vertical"}
        }
    )

    -- BUILD
    function spec.build()
        local component = juce.Component.new()
        component:setComponentID(juce.String.new(spec.id))

        -- CHILDREN
        for k, child in ipairs(spec.children) do
            child.component = child.build()
            component:addAndMakeVisible(child.component)
        end

        -- SIZE
        if spec["width"] ~= nil and spec["height"] ~= nil then
            component:setSize(spec["width"], spec["height"])
        end

        -- PAINT
        function component:paint(g)
            local area = component:getLocalBounds()
            g:setColour(spec.fill)
            g:fillRect(area)
        end

        -- RESIZED
        function component:resized()
            local area = component:getLocalBounds():reduced(spec.padding)

            local size = 0
            local numChildren = max(1, tableSize(spec.children))
            if spec["layout"] == "vertical" then
                size = area:getHeight() / numChildren
            else
                size = area:getWidth() / numChildren
            end

            for k in pairs(spec.children) do
                local child = spec.children[k].component
                local margin = spec.children[k].margin

                if spec["layout"] == "vertical" then
                    child:setBounds(area:removeFromTop(size):reduced(margin))
                else
                    child:setBounds(area:removeFromLeft(size):reduced(margin))
                end
            end
        end

        return component
    end

    return spec
end

function jml.TextButton(spec)
    spec = setEmptyProperties(spec, {{"text", ""}})

    -- BUILD
    function spec.build()
        local btn = juce.TextButton.new(juce.String.new(spec.text))
        btn:setComponentID(juce.String.new(spec.id))
        return btn
    end

    return spec
end

function jml.Slider(spec)
    spec = setEmptyProperties(spec, {})

    -- BUILD
    function spec.build()
        local slider = juce.Slider.new()
        slider:setComponentID(juce.String.new(spec.id))

        if spec["style"] ~= nil then
            slider:setSliderStyle(spec["style"])
        end

        if spec["range"] ~= nil then
            slider:setRange(spec.range["start"], spec.range["stop"], spec.range["interval"])
        end

        return slider
    end
    return spec
end

function jml.ComboBox(spec)
    spec = setEmptyProperties(spec, {{"choices", {}}})

    -- BUILD
    function spec.build()
        local cb = juce.ComboBox.new(juce.String.new(spec["name"]))
        cb:setComponentID(juce.String.new(spec.id))

        -- ADD CHOICES
        for k, v in ipairs(spec.choices) do
            cb:addItem(juce.String.new(v), k)
        end

        return cb
    end

    return spec
end

function jml.build(ui)
    return ui.build()
end

return jml
