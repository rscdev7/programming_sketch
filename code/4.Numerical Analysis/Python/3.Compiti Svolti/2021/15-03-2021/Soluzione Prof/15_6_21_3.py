#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jun 10 15:01:49 2021

@author: Giovanni Russo
"""

import math

def f(x):
    y = math.exp(x)-math.tan(x)
    return y

def f1(x):
    y = math.exp(x)-(1+math.tan(x)**2)
    return y

x = 1.5*math.pi-0.008
x = 4.7
delta = 1
n = 0
while abs(delta)>1e-8:
    delta = f(x)/f1(x)
    x = x -delta
    n = n+1
print(' x = ', x, 'f = ', f(x), ' n = ', n)
