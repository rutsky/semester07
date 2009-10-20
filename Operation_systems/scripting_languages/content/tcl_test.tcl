#!/usr/bin/tclsh

set x 0
while { $x < 10 } {
  puts $x
  incr x
}

set a 10
set b 3
set c [expr $a + $b]
puts $c

set long_string "a b c d"
puts $long_string

set string_list {a b c d}
puts $string_list

set map_var(one) 1
set map_var(two) 2
puts $map_var(two)

