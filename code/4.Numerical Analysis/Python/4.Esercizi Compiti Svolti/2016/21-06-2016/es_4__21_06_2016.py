from matplotlib import pyplot as plt
from math import sin,pi
import numpy as np


def trapezi (f,a,b,NS):

    h = (b-a)/NS

    T = (f(a)+f(b))/2

    for i in range(NS-1):
        x = a + (i+1)*h
        T += f(x)

    T *= h

    return T


f = lambda x:sin(x)

TOL = 10e-4
NS  = 15
a   = 0.0
b   = pi/2

res = trapezi(f,a,b,NS)

print (abs(1.0-res)<TOL)
print (abs(1.0-res))
