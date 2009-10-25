#!/usr/bin/env lua

function gcd(a, b)
  while b > 0 do
    a,b = b, a % b
  end
  return a
end

print(gcd(42, 56))
