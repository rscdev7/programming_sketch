import numpy as np
from numpy import ndarray


def gauss_elim (M:ndarray, b:ndarray):

    dim  = len(b)

    #Itero sul Numero di Incognite
    for i in range(dim):

        #Itero sulle righe della matrice
        for j in range(i+1,dim):
            mult        = M[j][i]/M[i][i]
            M[j][i]     = 0.0

            for k in range(i+1,dim):
                M[j][k] = M[j][k] - mult*M[i][k]

    return M


def upper_triangular_solver (M,b):

    dim = len(b)
    x   = np.zeros(dim, dtype=float)

    #itero sulle incognite da Trovare al Contrario
    for i in range(dim-1 , -1 , -1 ):

        if (i == dim-1):
            x[i] = b[i] / M[i][i]
        else:
            sum_term = 0.0

            for k in range(dim-1,i,-1):
                sum_term    =  sum_term + M[i][k] * x[k]
 
            x[i]            = (b[i] - sum_term) / M[i][i]
    
    return x



    