local int = juce.Array_int.new()
assert(int:isEmpty())
assert(int:size() == 0)
int:add(42)
assert(not int:isEmpty())
assert(int:size() == 1)
int:resize(143)
assert(int:size() == 143)

local float = juce.Array_float.new()
assert(float:isEmpty())
assert(float:size() == 0)

local double = juce.Array_double.new()
assert(double:isEmpty())
assert(double:size() == 0)

local String = juce.Array_String.new()
assert(String:isEmpty())
assert(String:size() == 0)

local File = juce.Array_File.new()
assert(File:isEmpty())
assert(File:size() == 0)

local var = juce.Array_var.new()
assert(var:isEmpty())
assert(var:size() == 0)
