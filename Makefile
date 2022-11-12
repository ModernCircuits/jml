.PHONY: format-cpp
format-cpp:
	@find src -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i

.PHONY: format-lua
format-lua:
	@find src -iname '*.lua' | xargs lua-format -c .lua-format -i

.PHONY: format
format: format-cpp format-lua


