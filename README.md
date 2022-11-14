# JUCE Lua Bindings

## Issues

- Adding callbacks to "types" defined in Lua. [runtime functions](https://sol2.readthedocs.io/en/latest/api/usertype.html) are only allowed for types not instances.
- Inheritance. See [Issue #353](https://github.com/ThePhD/sol2/issues/353)
- `juce::Button` needs explicit `getBounds` while `LuaComponent` does not
