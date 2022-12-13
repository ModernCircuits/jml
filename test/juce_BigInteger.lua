local int = juce.BigInteger.new()
assert(int:isZero())
assert(not int:isOne())

assert(int:getHighestBit() == -1)
int:setBit(0)
assert(int:getHighestBit() == 0)
int:setBit(1)
assert(int:getHighestBit() == 1)

local other = juce.BigInteger.new()
other:swapWith(int)

assert(int:isZero())
assert(not int:isOne())
assert(not other:isZero())
assert(not other:isOne())
assert(other:getHighestBit() == 1)
