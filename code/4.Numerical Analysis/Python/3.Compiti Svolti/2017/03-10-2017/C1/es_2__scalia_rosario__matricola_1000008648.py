"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

from math import sin,cos,pi,exp,log
import numpy as np
from matplotlib import pyplot as plt


def newton (f,f_1 , x_0, max_iter, tol):

    x = x_0
    dx = 1.0
    i = 0

    while( abs(dx) > tol and i < max_iter ):
        dx = - f(x)/f_1(x)
        x = x + dx
        i+=1

    if (abs(dx) < tol):
        print ("-> Lo Zero trovato rispetta la Tolleranza prefissata")

    return x, f(x), i



MAX_ITER    = 100
TOL         = 10e-6
X           = np.linspace(1.0,100.0,1000)

f           = lambda x:log(x)
g           = lambda x:-x+2
aux_f       = lambda x:f(x) - g(x)
aux_f1      = lambda x: 1/x + 1


f_x         = list( map( lambda x:f(x)      , X ) )
g_x         = list( map( lambda x:g(x)      , X ) )
aux_f_x     = list( map( lambda x:aux_f(x)  , X ) )



#Scelta Intervallo Newton
a = 1.00
b = 4.37
x_0 = a

plt.plot(X,aux_f_x)
plt.plot([a],[aux_f(a)],"ob")
plt.plot([b],[aux_f(b)],"or")
plt.axhline(y=0,color="r")
plt.show()


#Verifica Intervallo con THM degli Zeri+
# Se f(a)*f(b) < 0 ---> C'è uno zero in [a,b]
if (aux_f(a)*aux_f(b)<0):
    print ("[!] L'intervallo selezionato contiene uno Zero !")
else:
    print ("[!] L'intervallo Selezionato NON contiene uno Zero :(")
    exit(-1)


x,fx,i = newton(aux_f, aux_f1, x_0, MAX_ITER, TOL)
print ("[!] Ascissa Soluzione: {} - Ordinata Soluzione: {} - N Iterazioni: {}".format(x,fx,i))
print (aux_f(x))

plt.plot(X,f_x,"g")
plt.plot(X,g_x,"b")
plt.plot([x],[f(x)],"or")
plt.plot([x],[g(x)] ,"or")
plt.show()