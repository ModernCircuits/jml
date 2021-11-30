.PHONY: format
format:
	@find src -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs clang-format-13 -i

.PHONY: format-check
format-check:
	@find src -iname '*.hpp' -o -iname '*.h' -o -iname '*.cpp' | xargs -n 1 -P 1 -I{} -t sh -c 'clang-format-13 -style=file {} | diff - {}'
