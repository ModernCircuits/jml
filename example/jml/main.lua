jml = require("jml")

return jml.build(
    jml.Component {
        id = "Main Window",
        fill = juce.Colours.black,
        width = 500,
        height = 500,
        padding = 8,
        layout = "vertical",
        children = {
            jml.TextButton {
                id = "TextButton",
                text = "Button",
                margin = 4
            },
            jml.Slider {
                id = "Slider",
                range = {
                    start = 0.0,
                    stop = 500.0,
                    interval = 10.0
                }
            },
            jml.Component {
                id = "Canvas",
                margin = 4,
                fill = juce.Colours.green,
                layout = "horizontal",
                children = {
                    jml.Component {
                        id = "Canvas",
                        margin = 4,
                        fill = juce.Colours.blue
                    },
                    jml.Component {
                        id = "Canvas",
                        margin = 4,
                        fill = juce.Colours.red
                    }
                }
            }
        }
    }
)
