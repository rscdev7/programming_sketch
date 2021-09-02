"""
@author           	:  rscalia
@version  		    :  1.0.0
@build-date         :  Sun 23/05/2021
@last_update        :  Sun 23/05/2021

Questo componente serve per controllare se è possibile utilizzare un metodo iterativo per trovare la soluzione di un sistema lineare.

"""

import numpy as np
from numpy import ndarray


def compute_residual (M:ndarray,x:ndarray,b:ndarray,threshold:float):
    dim = len(M[0])
    res = np.zeros(3, dtype=float)

    #Itero sulle righe
    for i in range(dim):

        prod_sum = 0.0
        #Itero sulle Colonne
        for j in range(dim):
            prod_sum += M[i][j]*x[j]


        diff    = abs(b[i] - prod_sum)
        res[i]  = diff


    th_checker         = lambda x: True if x < threshold else False
    vect_th_checker    = np.vectorize(th_checker)
    response           = vect_th_checker(res).all()

    return response


def check_matrix_for_iterative_methods (M:ndarray) -> bool:

    for i in range(len(M[0])):
        d = M[i][i]
        sums = 0.0

        for j in range(len(M[0])):
            if (i != j):
                sums += abs(M[i][j])

        if (d <= sums):
            return False

    return True