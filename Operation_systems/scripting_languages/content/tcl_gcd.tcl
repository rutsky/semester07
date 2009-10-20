#!/usr/bin/tclsh

proc gcd { a b } {
  while { $b > 0 } {
    set t $b
    set b [expr $a % $b]
    set a $t
  }
  return $a
}

puts [gcd 42 56]
