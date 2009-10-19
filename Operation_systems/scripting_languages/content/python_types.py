#!/usr/bin/env python
# -*- coding: utf-8 -*-

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
