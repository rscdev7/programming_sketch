from jacobi import jacobi
from gauss_heidel import gauss_heidel
from ls_checker import check_matrix_for_iterative_methods
import numpy as np
from numpy import ndarray
from gauss_elim_solver import gauss_elim,upper_triangular_solver


def test_lin_iterative ():

    M           = np.array( [
                    [5.0, 2.0, 1.0], 
                    [2.0, 10.0, -4.0], 
                    [-1.0, -3.0, 8.0]
                   ] )

    b           = np.array( [8.0 , -1.0 , 2.0] )
    init_vec    = np.array([0.0,1.0,0.0])


    #Test Convergenza Jacobi
    response = check_matrix_for_iterative_methods(M)
    if (response == True):
        print ("Matrix is ready for Iterative Methods !")
    else:
        print("Sorry, your matrix isn't ready for iterative Methods")


    mtr = gauss_elim(M,b)
    res = upper_triangular_solver(mtr,b)
    print("\nGauss-Elim Solution: {}- Product Value: {} - Term Note: {} ".format(res,mtr.dot(res),b ) )


    #Calcolo Soluzione Jacobi con 2 Iterazioni
    solution = jacobi(M,b,init_vec,2)
    print ("\n[!] Jacobi 2-it Solution: {} - Product Value: {} - Note Term: {} \n".format(solution, M.dot(solution), b ))

    #Calcolo Soluzione Heidel con 2 Iterazioni
    solution = gauss_heidel(M,b,init_vec,2)
    print ("\n[!] Gauss-Heidel 2-it Solution: {} - Product Value: {} - Note Term: {} \n".format(solution, M.dot(solution), b ))

    #Calcolo Soluzione Jacobi con soglia 10 E-6
    solution_th = jacobi(M,b,init_vec,50, 0.00001)
    print ("\n[!] Jacobi TH Solution: {} - Product Value: {} - Note Term: {} \n".format(solution_th, M.dot(solution_th), b ))