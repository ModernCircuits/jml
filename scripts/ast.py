from pathlib import Path

import clang
import clang.cindex
from clang.cindex import CursorKind


def fully_qualified(c):
    if c is None:
        return ''
    elif c.kind == CursorKind.TRANSLATION_UNIT:
        return ''
    else:
        res = fully_qualified(c.semantic_parent)
        if res != '':
            return res + '::' + c.spelling
    return c.spelling


clang.cindex.Config.set_library_file('/usr/lib/llvm-13/lib/libclang.so')


file = '/home/tobante/Developer/tobanteAudio/lua-juce/3rd_party/JUCE/modules/juce_gui_basics/juce_gui_basics.cpp'
idx = clang.cindex.Index.create()
compdb = clang.cindex.CompilationDatabase.fromDirectory(
    Path('/home/tobante/Developer/tobanteAudio/lua-juce/build'))
print(compdb)
file_args = compdb.getCompileCommands(file)
print(compdb)
print(len(file_args))
for x in file_args:
    print(x)

idx.read
tu = idx.parse(file, "-DDEBUG=1 -DJUCE_APPLICATION_NAME_STRING=\"\\\"JUCE Lua\\\"\" -DJUCE_APPLICATION_VERSION_STRING=\\\"0.0.1\\\" -DJUCE_GLOBAL_MODULE_SETTINGS_INCLUDED=1 -DJUCE_MODULE_AVAILABLE_juce_core=1 -DJUCE_MODULE_AVAILABLE_juce_data_structures=1 -DJUCE_MODULE_AVAILABLE_juce_events=1 -DJUCE_MODULE_AVAILABLE_juce_graphics=1 -DJUCE_MODULE_AVAILABLE_juce_gui_basics=1 -DJUCE_MODULE_AVAILABLE_juce_gui_extra=1 -DJUCE_STANDALONE_APPLICATION=1 -DJUCE_USE_CURL=0 -DJUCE_WEB_BROWSER=0 -DLINUX=1 -DLUA_USE_DLOPEN -DLUA_USE_POSIX -D_DEBUG=1 -IJuceLuaTest_artefacts/JuceLibraryCode -I../3rd_party/JUCE/modules -I/usr/include/freetype2 -I/usr/include/libpng16 -isystem /home/tobante/.conan/data/lua/5.3.5/_/_/package/be27726f9885116da1158027505be62e913cd585/include -isystem /home/tobante/.conan/data/sol2/3.2.3/_/_/package/5ab84d6acfe1f23c4fae0ab88f26e3a396351ac9/include -g -fPIE -g -O0 -Wall -Wextra -Wstrict-aliasing -Wuninitialized -Wunused-parameter -Wsign-compare -Woverloaded-virtual -Wreorder -Wsign-conversion -Wunreachable-code -Wzero-as-null-pointer-constant -Wcast-align -Wno-implicit-fallthrough -Wno-maybe-uninitialized -Wno-missing-field-initializers -Wno-ignored-qualifiers -Wswitch-enum -Wredundant-decls -Wpedantic -Wno-strict-overflow -std=c++17".split())
for c in tu.cursor.walk_preorder():
    # if c.kind == CursorKind.CLASS_DECL:
    #     print(fully_qualified(c.referenced))
    if c.kind == CursorKind.CLASS_TEMPLATE:
        print(fully_qualified(c.referenced))
    elif c.kind == CursorKind.CXX_METHOD:
        print(fully_qualified(c.referenced))
