# JUCE Lua Bindings

## Issues

- Adding callbacks to "types" defined in Lua. `runtime functions` are only allowed for types not instances. [More info](https://sol2.readthedocs.io/en/latest/api/usertype.html)
- Inheritance. See [Issue #353](https://github.com/ThePhD/sol2/issues/353)
- `juce::Button` needs explicit `getBounds` while `LuaComponent` does not
