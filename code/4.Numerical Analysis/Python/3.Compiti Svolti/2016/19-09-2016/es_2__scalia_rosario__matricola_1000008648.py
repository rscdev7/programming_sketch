"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from matplotlib import pyplot as plt
from math import cos,sin,pi,log,exp


def compute_newton_base(X,Y):

    dim         = len(X)
    diff_div    = Y.copy()

    #Itero sulle Differenze Divise da Calcolare
    for i in range(1,dim):
        
        #Calcolo le differenze divise di Ordine i, dall'Ultima fino alla i-esima
        for j in range(dim-1 , i-1, -1):
            diff_div [j] = ( diff_div[j] - diff_div[j-1] ) / (X[j] - X[j-i])

    return diff_div


def newton_pol_eval (p,base,nodes):

    dim = len(base)
    R   = base[dim-1]

    for i in range(dim-2, -1 , -1):
        R *= (p - nodes[i])
        R += base[i]

    return R

X = np.array( [0.5,1.0,1.5,2.0] , dtype=np.float64 )
f = lambda x:1/x
Y = list( map( lambda x:f(x) , X ) )

base    = compute_newton_base(X,Y)

Y_p = list(map(lambda x:newton_pol_eval(x,base, X) , X))

plt.plot(X,Y,"or")
plt.plot(X,Y_p,"b")
plt.show()