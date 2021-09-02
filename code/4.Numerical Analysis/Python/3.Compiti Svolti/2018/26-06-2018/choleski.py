"""
@author           	:  rscalia
@version  		    :  1.0.0
@build-date         :  Sun 02/05/2021
@last_update        :  Sun 02/05/2021

Questo componente serve per implementare la fattorizzazione di Choleski

"""


import numpy as np
from numpy import ndarray
import math


def check_sym (M:ndarray):
    """
    Controlla se una matrice è Simmetrica

    Args:
        M       (ndarray)       : matrice di input
    """
    for i in range( len(M[0]) ):
        for j in range ( len(M[1]) ):

            if ( M[i][j] != M[j][i] ):
                return False

    return True


def check_pos_def(M):
    """
    Controlla se una matrice è definitiva positiva

    Args:
        M       (ndarray)       : matrice di input
    """
    for i in range( len(M[0]) ):
        sub_matrix = M[0:i+1 , 0:i+1]
        determinant = np.linalg.det(sub_matrix)

        if (determinant == 0):
            return False

    return True


def check_choleski(M):
    """
    Controlla se una matrice è adattata ad essere fattorizzata con Choleski

    Args:
        M       (ndarray)       : matrice di input
    """

    res = check_sym(M)

    if (res == False):
        return False

    res = check_pos_def(M)
    if (res == False):
        return False

    return True


def choleski_fat (M):
    """
    Fattorizzazione di Choleski

    Args:
        M       (ndarray)       : matrice di input
    """
    dim     = len(M[0])

    R       = np.zeros( (dim,dim) )


    #Scorro le righe della Matrice di Choleski
    for i in range(dim):

        #Per ogni riga, mi posiziono nella cella dove sarà presente un elemento diverso da Zero
        for j in range(i,dim):

            if (i==j):
                sum_term = 0.0

                for k in range(i):
                    sum_term += R[k][i]**2

                R[i][i] = math.sqrt (M[i][i] - sum_term ) 
            else:
                sum_term = 0.0
                for k in range(i):
                    sum_term += R[k][i] * R[k][j]

                R[i][j] = (M[i][j] - sum_term) / R[i][i]

    
    return R