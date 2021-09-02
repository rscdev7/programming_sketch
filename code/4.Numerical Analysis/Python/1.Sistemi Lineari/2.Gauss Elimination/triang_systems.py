"""
@author           	:  rscalia
@version  		    :  1.0.0
@build-date         :  Sun 16/05/2021
@last_update        :  Sun 16/05/2021

Questo componente serve per risolvere sistemi Triangolari Superiori e Inferiori

"""

import numpy as np



def upper_triangular_solver (M , b) -> list:
    """
    Risolve sistemi triangolari superiori

    """
    dim         = len(b)
    solution    = [0.0]*dim

    for i in range(dim - 1 , -1 , -1):
        
        if (i < (dim - 1) ):
            accum       = 0.0
            
            for j in range(dim - 1 , i , -1):
                accum   = accum + ( M[i][j] * solution[j] )

            solution[i]     = (b[i] - accum) / M[i][i] 
        else:
            solution[i]     = b[i]/M[i][i] 

    return solution


def lower_triangular_solver (M,b) -> list:
    """
    Risolve sistemi triangolari inferiori

    """
    dim         = len(b)
    solution    = [0.0]*dim

    for i in range(0,dim):

        if (i==0):
            solution[i] = b[i] / M[i][i]
        else:
            accum       = 0.0

            for j in range(0,i):
                accum = accum + ( M[i][j] * solution[j] )

            solution[i] = (b[i] - accum) / M[i][i]

    return solution