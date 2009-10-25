#!/usr/bin/env lua

point = { x = 10, y = 20 }
print(point["x"])              -- "10"
print(point.x)                 -- "10"

array = { 1, 2, "three" }
print(array[1])                -- "1"

function Point(x, y)
  return { x = x, y = y }
end
array = { Point(10, 20), Point(30, 40), Point(50, 60) }
print(array[2].y)              -- "40"

