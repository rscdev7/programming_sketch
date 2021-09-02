"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from matplotlib import pyplot as plt
from math import sin,cos,pi,exp,log


def compute_newton_base (X,Y):

    dim     = len(X)
    diff_div = Y.copy()

    for i in range(1,dim):
        for j in range(dim-1,i-1,-1):
            diff_div[j] = ( diff_div[j] - diff_div[j-1] )/( X[j] - X[j-i] )

    return diff_div

def eval_newton(p,nodes,base):

    dim =   len(nodes)
    E   = base[dim-1]

    for i in range(dim-2,-1,-1):
        E *= (p-nodes[i])
        E += base[i]

    return E

f = lambda x:exp(-x)

X = np.array(   [-1.0,-0.5,0.0,1.0]  ,dtype=np.float64 )
Y = list( map( lambda x:f(x),X ) )

base = compute_newton_base(X,Y)
Y_int = list( map( lambda x:eval_newton(x,X,base),X ) )

plt.plot(X,Y,"or")
plt.plot(X,Y_int,"b")

plt.show()