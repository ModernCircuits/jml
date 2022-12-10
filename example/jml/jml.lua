local jml = {}

local function isNumber(v)
    return type(v) == "number"
end

local function isString(v)
    return type(v) == "string"
end

local function isTable(v)
    return type(v) == "table"
end

local function getTableSize(t)
    assert(isTable(t))
    local count = 0
    for k in pairs(t) do
        count = count + 1
    end
    return count
end

local function max(lhs, rhs)
    assert(isNumber(lhs))
    assert(isNumber(rhs))

    if lhs > rhs then
        return lhs
    end

    return rhs
end

local function setEmptyProperties(spec, properties)
    assert(isTable(spec))
    assert(isTable(properties))

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
    assert(isString(str))
    return tonumber(str:sub(1, -2)) / 100.0
end

function calculatePercentageBasedSize(parentSize, children, property)
    assert(isNumber(parentSize))
    assert(isTable(children))
    assert(isString(property))

    local explicitSizeUsed = 0
    local numExplicit = 0

    -- Calculate sizes, if explicitly set
    local sizes = {}
    for k in pairs(children) do
        local child = children[k]
        local size = child[property]
        if isPercentageString(size) then
            sizes[k] = parentSize * parsePercentageToFraction(size)
            explicitSizeUsed = explicitSizeUsed + sizes[k]
            numExplicit = numExplicit + 1
        end
    end

    -- Split available space to components without explicit size property
    local withoutExplicitSize = getTableSize(children) - numExplicit
    if withoutExplicitSize > 0 then
        local available = parentSize - explicitSizeUsed
        local size = available / withoutExplicitSize
        for k in pairs(children) do
            if sizes[k] == nil then
                sizes[k] = size
            end
        end
    end

    return sizes
end

function jml.VerticalLayout(spec)
    function spec.perform(area, children)
        local heights = calculatePercentageBasedSize(area:getHeight(), children, "height")
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
        local widths = calculatePercentageBasedSize(area:getWidth(), children, "width")
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

        -- EXPLICIT SIZE
        if isNumber(spec["width"]) and isNumber(spec["height"]) then
            component:setSize(spec["width"], spec["height"])
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
