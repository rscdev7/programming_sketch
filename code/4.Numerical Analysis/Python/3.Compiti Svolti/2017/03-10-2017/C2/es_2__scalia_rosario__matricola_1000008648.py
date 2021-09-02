"""
- Nominativo. Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from math import cos,sin,pi,log,exp
from matplotlib import pyplot as plt


def computeNewtonBase (X,Y):

    dim         = len(X)
    diff_div    = Y.copy()

    for i in range( 1, dim ):
        for j in range( dim-1 , i-1 , -1 ):
            diff_div[j] = (diff_div[j] - diff_div[j-1])/(X[j] - X[j-i])

    return diff_div 

def eval_pol (p, X,B):
    dim = len(X)
    out = B[dim-1]

    for i in range(dim-2 , -1 , -1):
        out *= (p - X[i])
        out += B[i]

    return out


X = np.array( [-2.0,-1.0,1.0,3.0] , dtype=np.float64)
Y = np.array( [4.0,3.0,2.0,1.0] ,dtype=np.float64 )

base = computeNewtonBase(X,Y)

newton_eval = list( map ( lambda x: eval_pol(x,X,base), X ) )

plt.plot(X,Y,"or")
plt.plot(X,newton_eval,"b")
plt.show()