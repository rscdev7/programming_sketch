"""
@author           	:  rscalia
@version  		    :  1.0.0
@build-date         :  Thu 21/05/2021
@last_update        :  Thu 21/05/2021

Questo componente serve per testare la fattorizzazione di Choleski

"""


from choleski import choleski_fat, check_choleski
import numpy as np
import math 
from triang_systems import upper_triangular_solver, lower_triangular_solver


THRESHOLD       = 0.0000000005
TRUE_ARRAY      = np.array( [True]*3 ).all() 


def lu_fact(A):

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
    

def test_choleski ():

    #Starting Data
    A       = np.array([   [3.0, -1.0, 2.0],
            [-1.0, 4.0, 3.0],
            [2.0 , 3.0 , 6.0]  ])

    b       = np.array([0.0 , 4.0 , 7.0])


    #Controllo sulla fattibilità della Fattorizzazione
    ris     = check_choleski(A)
    if (ris == False):
        print ("Matrix isn't factorizable \n")
        exit(-1)


    #Fattorizzazione Choleski
    R                   = choleski_fat(A)
    th_array            = (abs(R.T.dot(R) -  A) <= THRESHOLD).all()
    assert ( R.T.dot(R).all() == A.all() or th_array == TRUE_ARRAY)


    #Risolvo per RT*y=b
    y_sol               = lower_triangular_solver(R.T , b)
    y_sol               = np.array(y_sol)
    th_array            = (abs(R.T.dot(y_sol) -  b) <= THRESHOLD).all()
    assert ( R.T.dot(y_sol).all() == b.all() or th_array  == TRUE_ARRAY )


    #Risolvo per R*x=y_sol
    x                   = np.array( upper_triangular_solver (R, y_sol) )  
    th_array            = (abs(A.dot(x) - b) <= THRESHOLD).all()
    assert ( A.dot(x).all() == b.all() or  th_array == TRUE_ARRAY )


def test_choleski_mtr ():
    #Starting Data
    A       = np.array([   [3.0, -1.0, 2.0],
            [-1.0, 4.0, 3.0],
            [2.0 , 3.0 , 6.0]  ])

    b       = np.array([0.0 , 4.0 , 7.0])


    #Controllo sulla fattibilità della Fattorizzazione
    ris     = check_choleski(A)
    if (ris == False):
        print ("Matrix isn't factorizable \n")
        exit(-1)


    D = np.eye(3,3)

    L,U = lu_fact(A.copy())
    for i in range(3):
        D[i][i] = (U[i][i])**(1/2)

    
    R = D.dot(L.T)
    RT = R.T