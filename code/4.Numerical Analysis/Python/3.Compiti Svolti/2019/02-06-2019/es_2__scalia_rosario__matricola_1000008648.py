"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from matplotlib import pyplot as plt
from math import sin,cos,pi,exp,log


def newton (f,f1,max_iter , tol,x0):

    dx = 1.0
    i = 0
    x = x0

    while (abs(dx) > tol and i < max_iter ):
        dx = -f(x)/f1(x)
        x += dx
        i+=1

    if (abs(dx) < tol):
        print ("Lo Zero Trovato soddisfa la soglia")

    return x,f(x),i



f = lambda x:x
g = lambda x:exp(-x)
tol = 10e-6


X   = np.linspace(-1.0,1.0,1000)
f_p = list( map( lambda x:f(x),X ) )
g_p = list( map( lambda x:g(x),X ) )

#Plot Funzioni
plt.plot(X,f_p,"r")
plt.plot(X,g_p,"b")
plt.legend(["f(x)=x","f(x)=e^{-x}"])
plt.show()


aux_f = lambda x: f(x)-g(x)
aux_f1 = lambda x:1+exp(-x)

aux_f_p = list( map( lambda x:aux_f(x),X ) )
plt.plot(X,aux_f_p,"r")
plt.axhline(color="b")
plt.show()

x0 = 0.5008

x,fx,iters = newton(aux_f,aux_f1,100,tol,x0)

print ("[!] Punto di Intersezione fra le Curve: ({},{}) - N Iterazioni: {}".format(x,fx,iters))


plt.plot(X,f_p,"r")
plt.plot(X,g_p,"b")
plt.plot([x],[f(x)],"og")
plt.legend(["f(x)=x","f(x)=e^{-x}","Intersezione"])
plt.show()