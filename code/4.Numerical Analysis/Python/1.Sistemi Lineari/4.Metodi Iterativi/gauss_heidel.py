"""
@author           	:  rscalia
@version  		    :  1.0.0
@build-date         :  Sun 23/05/2021
@last_update        :  Sun 23/05/2021

Questo componente implementa l'algoritmo di Gauss-Heidel

"""

import numpy as np
from numpy import ndarray
from ls_checker import compute_residual


def gauss_heidel (M:ndarray, b:ndarray, vec_init:ndarray, max_iter:int , threshold:float = None) -> ndarray:

    print ("\n <<<<<<<< GAUSS-HEIDEL >>>>>>>>>> \n")
    dim     = len(M[0])
    x_old   = vec_init.copy()
    x_new   = vec_init.copy()

    #Itero sulle Iterazioni Massime
    for i in range(max_iter):

        #Itero sulle Incognite da Trovare
        for j in range(dim):
            sum_old     = 0.0
            sum_new     = 0.0

            #Sommatoria Termini OLD
            for k in range(j+1,dim):
                sum_old += M[j][k] * x_old[k]

            #Sommatoria Termini NEW
            for k in range(j):
                sum_new += M[j][k] * x_new[k] 

            x_new[j]    = (b[j] - sum_new - sum_old)/M[j][j]

        x_old           = x_new.copy()

        print ("\n[!] Iteration: {} - Partial-Sol: {} \n".format(i+1,x_new))


        #Check basato sulla Soglia
        if (threshold != None):
            response        = compute_residual(M,x_new,b,threshold)

            if (response == True):
                return x_new
            else:
                continue

    
    return x_new