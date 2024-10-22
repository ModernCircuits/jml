# JUCE Meets LUA

[![Linux](https://github.com/ModernCircuits/jml/actions/workflows/linux.yml/badge.svg)](https://github.com/ModernCircuits/jml/actions/workflows/linux.yml)
[![macOS](https://github.com/ModernCircuits/jml/actions/workflows/macos.yml/badge.svg)](https://github.com/ModernCircuits/jml/actions/workflows/macos.yml)
[![Windows](https://github.com/ModernCircuits/jml/actions/workflows/windows.yml/badge.svg)](https://github.com/ModernCircuits/jml/actions/workflows/windows.yml)
[![Pre-Commit Hooks](https://github.com/ModernCircuits/jml/actions/workflows/pre-commit.yml/badge.svg)](https://github.com/ModernCircuits/jml/actions/workflows/pre-commit.yml)

> **WORK IN PROGRESS**: For license information please refer to [juce.com/get-juce](https://juce.com/get-juce)

## Projects

### Bindings

In your `CMakeLists.txt`:

```cmake
find_package(sol2 REQUIRED)
add_subdirectory(path/to/jml/modules)

target_link_libraries(YourApplication
    PRIVATE
        # This includes all JUCE modules for which bindings have been created
        mc::mc_lua_juce

        # You could also only link to individual modules
        # mc::mc_lua_juce_core
        # mc::mc_lua_juce_events
        # ...
    PUBLIC
        # Required for bindings
        sol2::sol2
)
```

In your source code:

```cpp
#include <mc_lua_juce/mc_lua_juce.hpp>

auto state = sol::state{};
state.open_libraries(sol::lib::base, sol::lib::package, sol::lib::string);
mc::lua::bindings::allJuceModules(state);
```

### Tools

#### jml-cli

- Run unit tests. See [Test.hpp](./tool/jml-cli/Command/Test.hpp)
- Create component snapshot images. See [Snapshot.hpp](./tool/jml-cli/Command/Snapshot.hpp)

#### jml-viewer

- ToDo

#### jml-designer

- ToDo
