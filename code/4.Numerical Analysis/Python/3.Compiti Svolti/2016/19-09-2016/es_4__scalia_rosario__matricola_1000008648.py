"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from matplotlib import pyplot as plt
from math import cos,sin,pi,log,exp


def simpson_composita (f,a,b,NS):

    h = (b-a)/NS

    S = f(a)+f(b)

    for i in range(NS-1):
        x = a + (i+1)*h
        S += 2.0*f(x)

    for i in range(NS):
        x = a +(i+0.5)*h
        S += 4.0*f(x)

    S *= (h/6)

    return S


def trapzei_composita (f,a,b,NS):

    h = (b-a)/NS
    T = (f(a)+f(b))/2

    for i in range(NS-1):
        x = a + (i+1)*h
        T += f(x)

    T *= h

    return T



f   = lambda x: x**3*exp(1-x**4)
a   = 0.0
b   = 1.0

NT  = 35
tol = 10e-4

trap_nt         = trapzei_composita(f,a,b,NT)
trap_nt_double  = trapzei_composita(f,a,b,NT*2)

if ( abs( (trap_nt - trap_nt_double) / 3 ) < tol ):
    print ("Formula dei Trapezi Rispetta la Tolleranza !")

print ("[!] Soluzione Trapezi: {} - N Intervalli: {}".format(trap_nt,NT))


NS              = 4
simp_nt         = simpson_composita(f,a,b,NS)
simp_double     = simpson_composita(f,a,b,NS*2)

if ( abs( 1/15*(simp_nt - simp_double)) < tol ):
    print ("Formula Simpson Rispetta la Tolleranza !")

print ("[!] Soluzione Simpson: {} - N Intervalli: {}".format(simp_nt,NS))
