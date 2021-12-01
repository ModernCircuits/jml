.PHONY: format
format:
	@find src -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs clang-format-13 -i
	@find src -iname '*.lua' | xargs lua-format -c .lua-format -i

.PHONY: format-check
format-check:
	@find src -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs -P 1 -I{} -t sh -c 'clang-format-13 -style=file {} | diff - {}'
	@find src -iname '*.lua' | xargs -P 1 -I{} -t sh -c 'lua-format -c .lua-format {} | diff - {}'
