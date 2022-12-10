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
        {"width", "auto"},
        {"height", "auto"},
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

function isPercentageString(str)
    if type(str) == "string" then
        return str:sub(-1) == "%"
    end
    return false
end

function parsePercentageToFraction(str)
    return tonumber(str:sub(1, -2)) / 100.0
end

function jml.VerticalLayout(spec)
    function spec.perform(area, children)
        local numChildren = tableSize(children)
        local parentHeight = area:getHeight()
        local explicitHeightUsed = 0
        local numExplicitHeight = 0

        local heights = {}
        for k in pairs(children) do
            local child = children[k]
            local height = child.height
            if isPercentageString(height) then
                local w = parentHeight * parsePercentageToFraction(height)
                heights[k] = w
                explicitHeightUsed = explicitHeightUsed + w
                numExplicitHeight = numExplicitHeight + 1
            end
        end

        local availableHeight = parentHeight - explicitHeightUsed
        for k in pairs(children) do
            if heights[k] == nil then
                heights[k] = availableHeight / (numChildren - numExplicitHeight)
            end
        end

        for k in pairs(children) do
            assert(heights[k] ~= nil)
            local child = children[k]
            local component = child.component
            local margin = child.margin
            component:setBounds(area:removeFromTop(heights[k]):reduced(margin))
        end
    end
    return spec
end

function jml.HorizontalLayout(spec)
    function spec.perform(area, children)
        local numChildren = tableSize(children)
        local parentWidth = area:getWidth()
        local explicitWidthUsed = 0
        local numExplicitWidth = 0

        local widths = {}
        for k in pairs(children) do
            local child = children[k]
            local width = child.width
            if type(width) == "string" and isPercentageString(width) then
                local w = parentWidth * parsePercentageToFraction(width)
                widths[k] = w
                explicitWidthUsed = explicitWidthUsed + w
                numExplicitWidth = numExplicitWidth + 1
            end
        end

        local availableWidth = parentWidth - explicitWidthUsed
        for k in pairs(children) do
            if widths[k] == nil then
                widths[k] = availableWidth / numChildren - numExplicitWidth
            end
        end

        for k in pairs(children) do
            assert(widths[k] ~= nil)
            local child = children[k]
            local component = child.component
            local margin = child.margin
            component:setBounds(area:removeFromLeft(widths[k]):reduced(margin))
        end
    end
    return spec
end

function jml.Component(spec)
    -- DEFAULT PROPERTIES
    local properties = {
        {"fill", juce.Colour.new()},
        {"children", {}},
        {"layout", jml.VerticalLayout {}}
    }
    spec = setEmptyProperties(spec, properties)

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
        if type(spec["width"]) == "number" and type(spec["width"]) == "number" then
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
            spec["layout"].perform(area, spec.children)
        end

        return component
    end

    return spec
end

function jml.TextButton(spec)
    -- DEFAULT PROPERTIES
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
    -- DEFAULT PROPERTIES
    spec = setEmptyProperties(spec, {})

    -- BUILD
    function spec.build()
        local slider = juce.Slider.new()
        slider:setComponentID(juce.String.new(spec.id))

        -- STYLE
        if spec["style"] ~= nil then
            slider:setSliderStyle(spec["style"])
        end

        -- TEXTBOX POSITION
        if spec["textbox"] ~= nil then
            local isEditable = slider:isTextBoxEditable()
            local width = slider:getTextBoxWidth()
            local height = slider:getTextBoxHeight()
            slider:setTextBoxStyle(spec["textbox"], isEditable, width, height)
        end

        -- RANGE
        if spec["range"] ~= nil then
            slider:setRange(spec.range["start"], spec.range["stop"], spec.range["interval"])
        end

        return slider
    end

    return spec
end

function jml.ComboBox(spec)
    -- DEFAULT PROPERTIES
    spec = setEmptyProperties(spec, {{"choices", {}}})

    -- BUILD
    function spec.build()
        local cb = juce.ComboBox.new(juce.String.new(spec["name"]))
        cb:setComponentID(juce.String.new(spec.id))

        -- CHOICES
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
