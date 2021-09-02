"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from matplotlib import pyplot as plt
from math import cos,sin,pi,log,exp


def newton (f,f1, max_iter, tol, x0):
    dx = 1.0
    i  = 0
    x  = x0

    while( abs(dx) > tol  and  i < max_iter):
        dx = -f(x)/f1(x)
        x += dx
        i+=1

    if (abs(dx) < tol):
        print ("[!] Starting Point: {} - Soluzione: {} - f(sol): {} - Iterazioni: {}".format(x0,x,f(x),i))
    else:
        print ("[WARNING] Starting Point: {} - FUNZIONE NON CONVERGE ALLO ZERO - Iterazioni: {}".format(x0,i))

    return x,f(x),i

f           = lambda x:exp(-x)-x
f1          = lambda x:-exp(-x) - 1
a           = 0.0
b           = 1.0
TOL         = 10e-10
MAX_ITER    = 100

if ( f(a)*f(b) < 0 ):
    print ("[!] La funzione rispetta le ipotesi del Teorema degli Zeri")
else:
    print ("[WARNING] La funzione NON rispetta le ipotesi del Teorema degli Zeri")
    exit(-1)

X   = np.linspace(a,b,1000)
Y   = list( map( lambda x:f(x),X ) )

x0_0 = 0.0
x1_0 = 1.0

plt.plot(X,Y,"r")
plt.axhline(color="b")

plt.plot([x0_0],[0.0],"o-b")
plt.plot([x0_0],[f(x0_0)],"o-b")

plt.plot([x1_0],[f(x1_0)],"og")
plt.plot([x1_0],[0.0],"og")
plt.show()


x0_sol , f_x0_sol,i = newton(f,f1,MAX_ITER,TOL,x0_0)
x1_sol , f_x1_sol,i = newton(f,f1,MAX_ITER,TOL,x1_0)


plt.plot(X,Y,"r")
plt.axhline(color="b")

plt.plot([x0_0],[0.0],"o-b")
plt.plot([x0_0],[f(x0_0)],"o-b")
plt.plot([x1_0],[f(x1_0)],"og")
plt.plot([x1_0],[0.0],"og")

plt.plot([x0_sol], [f(x0_sol)] ,"or" )
plt.plot([x1_sol], [f(x1_sol)] ,"og" )
plt.show()