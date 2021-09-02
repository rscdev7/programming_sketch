"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from math import exp
from matplotlib import pyplot as plt


def computeNewtonBase (X,Y):

    diff_div = Y.copy()
    dim      = len(X)

    for i in range( 1 , dim ):
        for j in range( dim-1 , i-1 , -1 ):
            diff_div[j] = (diff_div[j] - diff_div[j-1])/(X[j] - X[j-i])

    return diff_div

def newtonEval(p, X, base):

    dim = len(base)
    E   = base[dim-1]

    for i in range(dim-2 , -1 , -1):
        E *= (p-X[i])
        E += base[i]

    return E

X = np.array( [-1.0, -0.5 , 0.0, 0.5 , 1.0] , dtype=float )
f = lambda x: exp(x**2-1)
Y = np.array( list( map ( lambda x: f(x) , X )  ) , dtype=float )

base = computeNewtonBase(X,Y)

eval_n = list( map ( lambda x: newtonEval(x,X,base),X ) )

plt.plot(X,Y,"ob")
plt.plot(X,eval_n,"r")
plt.show()


