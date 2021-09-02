"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from math import exp
from matplotlib import pyplot as plt


def simpson (f,a,b,NS):

    S = (f(a)+f(b))
    h = (b-a)/NS

    for i in range(NS-1):
        p = a+(i+1)*h
        S += 4.0*f(p)

    for i in range(NS):
        p = a+(i+0.5)*h
        S += 2.0*f(p)

    S *= (h/6)

    return S


f = lambda x: x*exp(-x)

a = 0.0
b = 1.0

tol = 10e-4
N   = 674

ris  = simpson(f,a,b,N)
ris2 = simpson(f,a,b,N*2)

print (abs( (ris-ris2)/15 ) < tol )

print (round(ris,4))