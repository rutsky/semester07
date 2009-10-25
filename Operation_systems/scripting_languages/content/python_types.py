#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random

number = 5
complex_number = 1.5 + 0.5j
print complex_number.imag # "0.5"
big_number = 2**1000
print len(str(big_number)) # "302"

string = "String"
multilined_string = """
Multilined string,
yep.
"""
unicode_string = u"Уникод"

list_var = [1, 2, 'three']
tuple_var = (1, 2, 'three')
print list_var[1] # "2"

dictionary = {'one': 1, 'two': 2}
print dictionary['one'] # "1"

set_var = set([1, 2, 'five'])
print 'five' in set_var # "True"

squares = [v ** 2 for v in range(0, 10) if random.randint(0, 1) == 1]
for i, v in enumerate(squares):
  print "%2d\t%2d" % (i, v)
# Вывод:
# 0       0
# 1       1
# 2       9
# 3      16
# 4      25
# 5      49
