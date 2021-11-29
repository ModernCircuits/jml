import clang.cindex
import clang
import clang.cindex as cl
from clang.cindex import CursorKind


cl.Config.set_library_file(
    'C:/Users/tobias/scoop/apps/llvm/13.0.0/bin/libclang.dll')


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


file = 'C:/Developer/lib/JUCE/modules/juce_gui_basics/juce_gui_basics.cpp'
idx = clang.cindex.Index.create()
compdb = clang.cindex.CompilationDatabase.fromDirectory(
    'C:/Developer/lib/JUCE/cmake-build-release')

file_args = compdb.getCompileCommands(file)
print(len(file_args))
tu = idx.parse(file, file_args)
for c in tu.cursor.walk_preorder():
    if c.kind == CursorKind.CLASS_DECL:
        print(fully_qualified(c.referenced))
    elif c.kind == CursorKind.CXX_METHOD:
        print(fully_qualified(c.referenced))
