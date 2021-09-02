#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Tue Jun  8 11:29:18 2021
Es. 1 del 21/06/2016
@author: MacBookPro
"""

import math

from scipy import linalg

def norm2(x):
    z = 0.0
    for q in x:
        z = z+q**2
    return math.sqrt(z)

def scal_prod(x,y):
    n = len(x)
    p = 0.0
    for i in range(n):
        p = p + x[i]*y[i]
    return p

    
#a = [[-30, 10, 20],[10, 40, 20],[20,20,-10]]
#x = [1,0,0]
a = [[8, -2, 1, 0], [-2, 2,-1, 1],[1, -1, 3, -1], [0, 1, -1,-5]]
x = [1,1,1,1]
N = len(x)

y = N*[0.0]

err = 1.0
tol = 1e-4

n = 0
max_iter = 100
while err>tol and n<max_iter:
    # Normalizzazione del vettore x
    z = norm2(x)
    for i in range(N):
        y[i] = x[i]/z
    # Calcoliamo A*y
    for i in range(N):
        x[i] = 0.0
        for j in range(N):
            x[i] = x[i]+a[i][j]*y[j]
    sigma = scal_prod(x,y)/scal_prod(y,y)
    sy = N*[0.0]
    for i in range(N):
        sy[i] = sigma*y[i]
    #print('x = ', x)
    #print('sy = ',sy)
    delta = N*[0.0]
    for i in range(N):
        delta[i] = x[i]-sigma*y[i]
    err = norm2(delta)/norm2(x)
    print('errore = ',err)
    n = n+1
print('Numero di iterazioni = ', n)
            
    
    