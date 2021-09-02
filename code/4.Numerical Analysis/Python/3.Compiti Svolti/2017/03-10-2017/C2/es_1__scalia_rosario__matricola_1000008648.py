"""
- Nominativo. Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from math import cos,sin,pi,log,exp,sqrt
from matplotlib import pyplot as plt
from numpy.linalg import det

def lu_fact (A):
    dim = len(A[0])
    L   = np.eye(dim,dim)

    for i in range(dim):

        for j in range(i+1,dim):
            m__ji = A[j][i]/A[i][i]

            L[j][i] = m__ji
            A[j][i] = 0.0
            for k in range(i+1,dim):
                A[j][k] = A[j][k] - m__ji*A[i][k]

    return L,A


def lower_triangular_solver (M,b):

    dim = len(b)
    sol = [0.0]*dim

    for i in range(dim):
        if (i == 0.0):
            sol[i] = b[i]/M[i][i]
        else:
            sum_term = 0.0
            for k in range(i):
                sum_term += M[i][k] * sol[k]

            sol[i] = (b[i]- sum_term)/M[i][i]

    return sol

def upper_triangular_solver (M,b):
    dim = len(b)
    sol = [0.0]*dim

    for i in range(dim-1, -1, -1 ):

        if (i == (dim-1)):
            sol[i] = b[i]/M[i][i]
        else:
            sum_term = 0.0

            for k in range(dim-1,i,-1):
                sum_term += M[i][k]*sol[k]

            sol[i] = (b[i] - sum_term)/M[i][i]

    return sol


k_bad   = (11/2)**(1/2)
print("Bad k: {}".format(k_bad))

k       = 2.0
A       = np.array( [[4.0,0.0,-1.0] , [0.0,2.0,k] , [-1.0, k, 3.0] ] )

b       = np.array([2.0,0.0,1.0])

L,U     = lu_fact(A.copy())

y       = lower_triangular_solver(L,b)
x       = upper_triangular_solver(U,y)
print(A.dot(x),b)