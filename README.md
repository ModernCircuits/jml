# JUCE Meets LUA

[![Linux](https://github.com/ModernCircuits/jml/actions/workflows/linux.yml/badge.svg)](https://github.com/ModernCircuits/jml/actions/workflows/linux.yml)
[![macOS](https://github.com/ModernCircuits/jml/actions/workflows/macos.yml/badge.svg)](https://github.com/ModernCircuits/jml/actions/workflows/macos.yml)
[![Windows](https://github.com/ModernCircuits/jml/actions/workflows/windows.yml/badge.svg)](https://github.com/ModernCircuits/jml/actions/workflows/windows.yml)
[![Pre-Commit Hooks](https://github.com/ModernCircuits/jml/actions/workflows/pre-commit.yml/badge.svg)](https://github.com/ModernCircuits/jml/actions/workflows/pre-commit.yml)

> **WORK IN PROGRESS**: For license information please refer to [juce.com/get-juce](https://juce.com/get-juce)

## Issues

- Adding callbacks to "types" defined in Lua. [runtime functions](https://sol2.readthedocs.io/en/latest/api/usertype.html) are only allowed for types not instances.
- Inheritance. See [Issue #353](https://github.com/ThePhD/sol2/issues/353)
- `juce::Button` needs explicit `getBounds` while `LuaComponent` does not
- Destruction time & order. See `ListBox + ListBoxModel`
