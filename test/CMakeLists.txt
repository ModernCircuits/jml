project(test)

add_test(
    NAME
        core/BigInteger
    COMMAND
        $<TARGET_FILE:jml-cli> test -s core/BigInteger.lua
    WORKING_DIRECTORY
        ${PROJECT_SOURCE_DIR}
)
