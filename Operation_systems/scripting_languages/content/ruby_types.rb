#!/usr/bin/env ruby

array_var = [1, 2, 'three']
puts array_var[1] # "2"

hash_var = {'one' => 1, 'two' => 2}
puts hash_var['one'] # "1"

# Range от 0 до 9
(0...10). 
  # новый Range из квадратов
  collect{|v| v ** 2 }.
  # новый Range из некоторых элементов старого
  select{ rand(2) == 1 }. 
  # для каждого элемента печать индекса и самого элемента
  each_with_index{|v,i| printf "%2d\t%2d\n", i, v }
# Вывод:
# 0       0
# 1       4
# 2       9
# 3      16
# 4      64
