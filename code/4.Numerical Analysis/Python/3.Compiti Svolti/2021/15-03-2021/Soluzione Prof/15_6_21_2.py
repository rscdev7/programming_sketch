#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Thu Jun 10 14:59:39 2021

@author: MacBookPro
"""

#import math

import matplotlib.pyplot as plt


# Exercise n. 2
p = [1,1,-2.0/3.0,4.0/27];
X = [0,3]
Y = [1,2]
N = 1000
h = 3.0/N
x = []
y = []
for i in range(N+1):
    x.append(h*i)
    pol = p[0]+p[1]*x[i]+p[2]*x[i]**2+p[3]*x[i]**3
    y.append(pol)
plt.plot(X,Y,'*')
plt.plot(x,y)
