jml = require("jml")

local ui =
    jml.Component {
    id = "Main Window",
    fill = juce.Colours.grey,
    width = 500,
    height = 500,
    padding = 8,
    layout = jml.VerticalLayout {},
    children = {
        jml.TextButton {
            id = "TextButton",
            text = "Button",
            height = "10%",
            margin = 4
        },
        jml.ComboBox {
            id = "ComboBox",
            margin = 4,
            choices = {
                "Foo",
                "Bar",
                "Baz"
            }
        },
        jml.Slider {
            id = "Slider",
            style = juce.SliderStyle.LinearHorizontal,
            margin = 4,
            range = {
                start = 0.0,
                stop = 500.0,
                interval = 10.0
            }
        },
        jml.Component {
            id = "Yellow",
            margin = 4,
            fill = juce.Colours.yellow,
            layout = jml.HorizontalLayout {},
            children = {
                jml.Component {
                    id = "Blue",
                    margin = 4,
                    fill = juce.Colours.blue
                },
                jml.Component {
                    id = "Red",
                    margin = 4,
                    fill = juce.Colours.red
                }
            }
        }
    }
}

return jml.build(ui)
