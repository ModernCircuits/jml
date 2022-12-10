jml = require("jml")

local eq = {}

function eq.Rotary(spec)
    return jml.Slider {
        id = spec.id,
        style = juce.SliderStyle.RotaryHorizontalVerticalDrag,
        textbox = juce.SliderTextEntryBoxPosition.NoTextBox,
        margin = 4
    }
end

function eq.Band(spec)
    return jml.Component {
        id = spec.id,
        margin = 4,
        fill = juce.Colours.black,
        layout = jml.VerticalLayout {},
        children = {
            jml.ComboBox {
                id = "Filter Types",
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
end

function eq.Analyzer(spec)
    return jml.Component {
        id = spec.id,
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
            id = "Analyzer"
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
