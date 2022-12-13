.PHONY: format-cpp
format-cpp:
	@find modules -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i
	@find tool -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs clang-format -i

.PHONY: format-lua
format-lua:
	@find example -iname '*.lua' | xargs lua-format -c .lua-format -i
	@find test -iname '*.lua' | xargs lua-format -c .lua-format -i

.PHONY: format
format: format-cpp format-lua

.PHONY: check
check:
	@pre-commit run --all-files
