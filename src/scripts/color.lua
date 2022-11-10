local color = {}

function color.randomWithAlpha(alpha)
    local r = juce.Random.getSystemRandom():nextInt(255)
    local g = juce.Random.getSystemRandom():nextInt(255)
    local b = juce.Random.getSystemRandom():nextInt(255)
    return juce.Colour.new(r, g, b, alpha)
end

function color.random()
    return color.randomWithAlpha(255)
end

return color
