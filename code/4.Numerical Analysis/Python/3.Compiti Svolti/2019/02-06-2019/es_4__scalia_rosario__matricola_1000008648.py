"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from matplotlib import pyplot as plt
from math import sin,cos,pi,exp,log
from functools import reduce


def trapezi_comp (f,a,b,N):

    h = (b-a)/N

    T = (f(a)+f(b))/2

    for i in range(N-1):
        p = a + (i+1)*h
        T += f(p)

    T *= h

    return T

def simpson_comp (f,a,b,N):

    h = (b-a)/N
    S = f(a)+f(b)

    for i in range(N-1):
        p = a + (i+1)*h
        S += 2.0*f(p)

    for i in range(N):
        p = a + (i+0.5)*h
        S += 4.0*f(p)

    S *= (h/6)

    return S




# ANALISI CALCOLO MASSIMO DERIVATE SECONDE E QUARTE
f   = lambda x:log(x)/x
f2  = lambda x:(2*log(x)-3)/x**3
f4  = lambda x:2*(12*log(x)-25)/x**5
p   = np.linspace(1.0,2.0,1000)


#Caso Trapezi - Ricerca Massimo
f2_p    = list(map(lambda x:f2(x),p))
p_f2_p  = list(zip(p,f2_p))

max_f2 = reduce (lambda x,y: x if x[1] >= y[1] else y , p_f2_p)

print("[!] Massimo Derivata Seconda f: ({},{})".format(max_f2[0],max_f2[1]))


#Plot
plt.plot(p,f2_p)
plt.plot([max_f2[0]] , [ f2( max_f2[0] ) ],"or" )
plt.show()



#Caso Simpson - Ricerca Massimo
f4_p    = list(map(lambda x:f4(x),p))
p_f4_p  = list(zip(p,f4_p))

max_f4 = reduce (lambda x,y: x if x[1] >= y[1] else y , p_f4_p)

print("[!] Massimo Derivata Quarta f: {}".format(max_f4[1]))

#Plot
plt.plot(p,f4_p)
plt.plot([ max_f4[0] ] , [ f4( max_f4[0] ) ],"og" )
plt.show()



#Approx Integrale
NT = 109
NS = 24

a = 2.0
b = 1.0

trapez          = trapezi_comp(f,a,b,NT)
print ("[!] Approx Integrale Trapezi: {}".format(abs(trapez)))

simp            = simpson_comp(f,a,b,NS)
print ("[!] Approx Integrale Simpson: {}".format(abs(simp)))

exact_integra   = 0.2402265069591007
print ("[!] Exact Integral: {} ".format( abs(exact_integra) ))