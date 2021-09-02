"""
- Nominativo. Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from math import cos,sin,pi,log,exp
from matplotlib import pyplot as plt

def newton (f,f1, x_0,tol,max_iter):
    dx  = 1.0
    i   = 0
    x   = x_0

    while( abs(dx) > tol and i < max_iter ):
        dx = -f(x)/f1(x)
        x += dx
        i +=1

    if (abs(dx) < tol):
        print("[NEWTON-FUN] La soluzione soddisfa la Soglia")

    return x,f(x),i



f   = lambda x: log(x)
g   = lambda x:-x+2

a   = 1.0
b   = 2.0

X   = np.linspace(1.0,2.0,1000)
fx  = list( map( lambda x:f(x),X ) )
gx  = list(map(lambda x:g(x),X))

plt.plot(X,fx,"r")
plt.plot(X,gx,"b")
plt.show()


aux_f = lambda x: f(x) - g(x)
aux_f1 = lambda x: 1/x + 1

auxx = list( map( lambda x:aux_f(x),X ) )

plt.plot(X,auxx,"b")
plt.axhline(color="g")
plt.show()


A = 1.5395
B = 1.5737
x_0 = A
if (aux_f(A)*aux_f(B)<0):
    print("Ok")

MAX_ITER = 100
TOL      = 10e-3

sol,fsol,iters = newton (aux_f,aux_f1, x_0, TOL,MAX_ITER)

print ("[!] Ascissa Soluzione {} - Ordinata Soluzione: {} - N Iteraz: {}".format(sol,fsol,iters))

plt.plot(X,fx,"r")
plt.plot(X,gx,"b")
plt.plot([sol],[f(sol)],"og")
plt.show()