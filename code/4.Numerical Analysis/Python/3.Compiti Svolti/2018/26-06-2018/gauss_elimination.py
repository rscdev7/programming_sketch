"""
@author           	:  rscalia
@version  		    :  1.0.0
@build-date         :  Sun 16/05/2021
@last_update        :  Sun 16/05/2021

Questo componente serve per risolvere sistemi lineari di equazioni che hanno una singola soluzione

"""

from triang_systems import upper_triangular_solver
import numpy as np


def gauss_naive (M, b) -> list:
    """
    Trasforma il sistema (M,b) in un sistema (M1,b1) equivalente e triangolare Superiore
    """
    dim = len(b)

    #Itero sulle Incognite da Trovare
    for i in range(dim):

        #Itero sulle righe su cui devo cancellare un elemento
        for j in range(i+1,dim):
            m__j_i      = M[j][i] / M[i][i]
            M[j][i]     = 0.0

            for k in range (i+1,dim):
                M[j][k] = M[j][k] - m__j_i * M[i][k]
            
            b[j]        = b[j] - m__j_i * b[i]

    return M,b


def lu_factorization (M) -> list:
    """
    Fattorizzazione LU della Matrice M
    """
    dim = len(M)
    L   = np.eye(dim)

    #Itero sulle Incognite da Trovare
    for i in range(dim-1):

        #Itero sulle righe su cui devo cancellare un elemento
        for j in range(i+1,dim):
            m__j_i      = M[j][i] / M[i][i]
            L[j][i]     = m__j_i
        
            M[j][i]     = 0.0

            for k in range (i+1,dim):
                M[j][k] = M[j][k] - m__j_i * M[i][k]
            

    return M,L


def gauss_naive_row_pivoting (M, b) -> list:
    """
    Trasforma il sistema (M,b) in un sistema (M1,b1) equivalente e triangolare Superiore
    Sfrutta il row-pivoting per evitare instabilità numeriche
    """
    dim = len(b)

    #Itero sulle Incognite da Trovare
    for i in range(dim):
        
        M,b     = row_pivoting(M,b,i)

        #Itero sulle righe su cui devo cancellare un elemento
        for j in range(i+1,dim):
            m__j_i      = M[j][i] / M[i][i]
            M[j][i]     = 0.0

            for k in range (i+1,dim):
                M[j][k] = M[j][k] - m__j_i * M[i][k]
            
            b[j]        = b[j] - m__j_i * b[i]

    return M,b


def row_pivoting (M,b, target_col):
    """
    Implementa la strategia di Row-Pivoting
    """

    dim = len(b)


    #Find Pivot
    actual_pivot = abs(M[target_col][target_col])
    pivot_idx    = target_col

    for j in range(target_col+1,dim):
        if ( abs(M[j][target_col]) > actual_pivot):
            actual_pivot = M[j][target_col]
            pivot_idx    = j


    #Scambio Righe < target_col , pivot_idx >
    if (pivot_idx != target_col):

        for k in range(dim):
            tmp_pivot_idx       = M[pivot_idx][k]

            M[pivot_idx][k]     = M[target_col][k]
            M[target_col][k]    = tmp_pivot_idx


        tmp_b                   = b[pivot_idx]
        b[pivot_idx]            = b[target_col]
        b[target_col]           = tmp_b


    return M,b


def row_pivoting_full (M,b):
    """
    Implementa una strategia Full-Pivoting
    """

    dim = len(b)

    #Itero sulle colonne dei moltiplicatori
    for i in range(dim-1):

        #Find Pivot
        actual_pivot = abs(M[i][i])
        pivot_idx    = i

        for j in range(i+1,dim):
            if ( abs(M[j][i]) > actual_pivot):
                actual_pivot = M[j][i]
                pivot_idx    = j


        #Scambio Righe < i , pivot_idx >
        if (pivot_idx != i):

            for k in range(dim):
                tmp_pivot_idx       = M[pivot_idx][k]

                M[pivot_idx][k]     = M[i][k]
                M[i][k]             = tmp_pivot_idx


            tmp_b                   = b[pivot_idx]
            b[pivot_idx]            = b[i]
            b[i]                    = tmp_b


        return M,b