"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from math import exp,log
from matplotlib import pyplot as plt


def fixed_p_method (f,max_iter,tol,x_o):

    i = 0
    x = x_o

    while (abs(x-1.0)>tol and i < max_iter ):
        x = f(x)
        i +=1

    if (abs(x-1.0)<tol):
        print ("[!] Trovato Punto Fisso")

    return x,f(x)

f = lambda x:x+1/2*(exp(2-2*x)-1)
f1 = lambda x:1-exp(2-2*x)
p = np.linspace(-50,50,10000)

fp = list( map( lambda x:f(x),p ) )
f1e = list( map( lambda x:f1(x),p ) )

f1p     = list( map( lambda x:(x,f1(x)),p ) )
f1p_fil = list( filter ( lambda x: x[1]<1.0,f1p ) )
f1p_x  = list(map (lambda x: x[0] , f1p_fil))
f1p_y  = list(map (lambda x: x[1] , f1p_fil))


x_0 = 0.4

plt.plot(p,fp,"b")
plt.plot([1.0],[f(1.0)],"or")
plt.plot(f1p_x,f1p_y,"g")
plt.show()

x,y = fixed_p_method(f,1000,10e-15,x_0)

print(x,y)