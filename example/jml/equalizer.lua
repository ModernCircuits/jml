jml = require("jml")

local eq = {}

function eq.Rotary(spec)
    local custom = {}
    local root =
        jml.Slider {
        style = juce.SliderStyle.RotaryHorizontalVerticalDrag,
        textbox = juce.SliderTextEntryBoxPosition.NoTextBox,
        margin = 4
    }

    for k, v in pairs(spec) do
        if custom[k] == nil then
            root[k] = v
        end
    end

    return root
end

function eq.Band(spec)
    local custom = {}

    local root =
        jml.Component {
        margin = 4,
        fill = juce.Colours.black,
        layout = jml.VerticalLayout {},
        children = {
            jml.ComboBox {
                id = "Filter Types",
                height = "25%",
                margin = 4,
                choices = {
                    "Low Cut",
                    "Low Shelf",
                    "Peak",
                    "High Cut",
                    "High Shelf"
                }
            },
            jml.Component {
                id = "Gain & Quality",
                layout = jml.HorizontalLayout {},
                children = {
                    eq.Rotary {
                        id = "Gain"
                    },
                    eq.Rotary {
                        id = "Quality"
                    }
                }
            },
            eq.Rotary {
                id = "Frequency"
            }
        }
    }

    for k, v in pairs(spec) do
        if custom[k] == nil then
            root[k] = v
        end
    end

    return root
end

function eq.Analyzer(spec)
    local custom = {}

    local root =
        jml.Component {
        margin = 4,
        fill = juce.Colours.black,
        children = {
            jml.Component {
                id = "Red",
                margin = 4,
                fill = juce.Colours.white
            }
        }
    }

    for k, v in pairs(spec) do
        if custom[k] == nil then
            root[k] = v
        end
    end

    return root
end

local ui =
    jml.Component {
    id = "Equalizer",
    fill = juce.Colours.grey,
    width = 750,
    height = 560,
    padding = 8,
    layout = jml.VerticalLayout {},
    children = {
        eq.Analyzer {
            id = "Analyzer",
            height = "45%"
        },
        jml.Component {
            id = "Bands",
            layout = jml.HorizontalLayout {},
            children = {
                eq.Band {
                    id = "Band Low"
                },
                eq.Band {
                    id = "Band Low Mid"
                },
                eq.Band {
                    id = "Band Mid"
                },
                eq.Band {
                    id = "Band High Mid"
                },
                eq.Band {
                    id = "Band High"
                }
            }
        }
    }
}

return jml.build(ui)
