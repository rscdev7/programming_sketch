"""
@author           	:  rscalia
@version  		    :  1.0.0
@build-date         :  Sun 23/05/2021
@last_update        :  Sun 23/05/2021

Questo componente implementa l'algoritmo di Jacobi

"""

import numpy as np
from numpy import ndarray
from ls_checker import compute_residual

def jacobi (M:ndarray, b:ndarray , init_vector:ndarray ,max_iter:int, threshold:float=None) -> ndarray:

    print ("\n\n <<<<<<<<<< JACOBI >>>>>>>>>>> \n\n")

    dim = len(M[0])
    x   = init_vector.copy()

    #Scandisco le iterazioni da fare
    for i in range (max_iter):
        
        #Scandisco le incognite da Trovare
        for j in range(dim):
            sum_term = 0.0

            #Riduco iterativamente le righe della matrice ad eccezione del termine j-esimo
            for k in range(dim):
                if (j != k):
                    sum_term += M[j][k] * x[k]

            x[j] = (b[j] - sum_term)/M[j][j]


        print ("\n[!] Iteration: {} - Partial-Sol: {} \n".format(i+1,x))

        #Check basato su soglia
        if (threshold != None):
            response = compute_residual(M, x, b, threshold)

            if (response == True):
                return x
            else:
                continue
        

    return x