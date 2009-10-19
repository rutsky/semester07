#!/usr/bin/env python
# -*- coding: utf-8 -*-

def GCD(a, b):
    while b > 0:
        a,b = b,a%b
    return a

print GCD(42, 56)
