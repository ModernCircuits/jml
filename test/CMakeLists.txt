project(test)

function(mc_add_lua_juce_test _name)
    add_test(
        NAME
            "lua: ${_name}"
        COMMAND
            $<TARGET_FILE:jml-cli> test -s "${_name}.lua"
        WORKING_DIRECTORY
            ${PROJECT_SOURCE_DIR}
    )
endfunction()

mc_add_lua_juce_test("core/Array")
mc_add_lua_juce_test("core/BigInteger")
mc_add_lua_juce_test("core/File")
mc_add_lua_juce_test("core/String")
