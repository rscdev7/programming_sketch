"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from math import exp
from matplotlib import pyplot as plt



def newton(f, f1,x_0 , tol,max_iter):

    dx = 1.0
    i  = 0
    x  = x_0

    while( abs(dx) > tol and i < max_iter):

        dx = -f(x)/f1(x)
        x = x + dx
        i+=1

    if (abs(dx) < tol):
        print ("-> L'approssimazione dello Zero della f soddisfa la Soglia !")
    
    return x,f(x)


f = lambda x: 1/x- 1
f_1 = lambda x: -1/x**2

a = 0.5
b = 1.5

if (f(a)*f(b)<0):
    print ("[!] Le condizioni del THM degli Zeri sono rispettate")
else:
    print ("[!] Le condizioni del THM degli Zeri NON sono rispettate")
    exit(-1)

X = np.linspace(0.5,1.5,1000)
Y = list( map( lambda x: f(x),X ) )

x_0 = 0.2

x,y = newton(f,f_1,x_0,10e-6,100)

print ("[!] La funzione f ha uno zero nell'ascissa {} - f(alpha) = {} ".format(x,y))

plt.plot(X,Y)
plt.plot(x,y,"or")
plt.show()



