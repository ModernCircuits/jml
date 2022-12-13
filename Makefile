CLANG_FORMAT_BIN ?= clang-format
CLANG_REPLACEMENTS_BIN ?= clang-apply-replacements
CLANG_TIDY_BIN ?= clang-tidy
CLANG_TIDY_ARGS = python3 $(shell which run-clang-tidy) -clang-tidy-binary ${CLANG_TIDY_BIN} -clang-apply-replacements-binary ${CLANG_REPLACEMENTS_BIN} -j ${shell nproc}

.PHONY: tidy-check
tidy-check:
	${CLANG_TIDY_ARGS} -quiet -p $(BUILD_DIR) -header-filter $(shell realpath ./tool) $(shell realpath ./tool)

.PHONY: tidy-fix
tidy-fix:
	${CLANG_TIDY_ARGS} -fix -quiet -p $(BUILD_DIR) -header-filter $(shell realpath ./tool) $(shell realpath ./tool)

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
