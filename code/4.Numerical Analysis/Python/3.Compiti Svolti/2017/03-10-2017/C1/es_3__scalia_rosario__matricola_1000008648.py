"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

from math import sin,cos,pi,exp,log
import numpy as np
from matplotlib import pyplot as plt


def trapezi_comp (f,a,b,NS):

    h = (b-a)/NS
    T = (f(a)+f(b))/2

    for i in range(NS-1):
        x = a + (i+1)*h
        T += f(x)

    T*= h

    return T

f = lambda x: 1/x
a = 1.0
b = 2.0
tol = 10e-6
NS = 277

ris1 = trapezi_comp(f,a,b,NS)
ris2 = trapezi_comp(f,a,b,NS*2)

print(abs( (ris1-ris2)/3 ) <tol, ris1 )

integrale_esatto = 0.6931471805599453

print(integrale_esatto)