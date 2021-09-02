"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

from math import sin,cos,pi,exp,log
import numpy as np
from matplotlib import pyplot as plt


def gauss_elimination_naive (M,b):

    dim = len(b)

    #Itero sulle Incognite da Eliminare
    for i in range(dim):

        #Itero sulle Righe dove devo cancellare l'incognita i-esima 
        for j in range(i+1,dim):
            m_ji = M[j][i]/M[i][i]
            M[j][i] = 0.0

            #Itero sugli elementi della riga J che vengono dopo l'elemento cancellato
            for k in range(i+1,dim):
                M[j][k] = M[j][k] - m_ji*M[i][k]

            b[j] = b[j] - m_ji*b[i] 

    return M,b

def upper_triangular_solver (M,b):

    dim = len(b)
    sol = [0.0]*dim

    for i in range(dim-1,-1,-1):

        if (i == (dim-1)):
            sol[i] = b[i]/M[i][i]
        else:
            sum_term = 0.0
            for k in range(dim-1, i, -1):
                sum_term += (M[i][k] * sol[k])

            sol[i] = (b[i] - sum_term)/M[i][i]

    return sol


X = [ -2.0,-1.0, 1.0, 3.0 ]
Y = [ 4.0, 3.0, 2.0 , 1.0 ]

M_V = np.zeros(shape=(4,4))
for counter,scalar in enumerate(X):
    M_V[counter][0] = 1.0
    M_V[counter][1] = scalar
    M_V[counter][2] = scalar**2
    M_V[counter][3] = scalar**3

M1,b1 = gauss_elimination_naive(M_V.copy(),Y.copy())

sol   = upper_triangular_solver(M1,b1)

#Verifica
print (M_V.dot(sol) , Y)


f = lambda x,a: a[0] + a[1]*x + a[2]*x**2 + a[3]*x**3

interp_p = list( map( lambda x: f(x,sol) , X ) )
plt.plot(X,Y,"or")
plt.plot (X, interp_p, "b")
plt.show()
