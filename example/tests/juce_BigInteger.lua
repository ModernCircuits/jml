function test_BigInteger()
  local bigInt = juce.BigInteger.new()
  assert(bigInt:isZero())
  assert(not bigInt:isOne())

  assert(bigInt:getHighestBit() == -1)
  bigInt:setBit(0)
  assert(bigInt:getHighestBit() == 0)
  bigInt:setBit(1)
  assert(bigInt:getHighestBit() == 1)

  local other = juce.BigInteger.new()
  other:swapWith(bigInt)

  assert(bigInt:isZero())
  assert(not bigInt:isOne())
  assert(not other:isZero())
  assert(not other:isOne())
  assert(other:getHighestBit() == 1)
end
