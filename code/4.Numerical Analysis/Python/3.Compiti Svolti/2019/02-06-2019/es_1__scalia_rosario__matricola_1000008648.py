"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from matplotlib import pyplot as plt
from math import sin,cos,pi,exp,log
from functools import reduce


def gauss_elim (A,b):

    dim = len(b)

    for i in range(dim):
        for j in range(i+1,dim):
            m__ji = A[j][i]/A[i][i]

            A[j][i] = 0.0

            for k in range(j+1,dim):
                A[j][k] -= m__ji*A[i][k]

            b[j] -= m__ji*b[i]

    return A,b


def upper_triangular_solver (A,b):

    dim = len(b)
    sol = np.zeros( shape=(dim) )

    for i in range(dim-1, -1 , -1):

        if (i == (dim-1)):
            sol[i] = b[i] / A[i][i]
        else:
            sum_term = 0.0
            for j in range(dim-1, i, -1):
                sum_term += A[i][j]*sol[j]

            sol[i] = (b[i] - sum_term)/A[i][i]

    return sol


def fill_least_square_system_grad_2(X,Y,shape):
    dim                 = shape

    PHI_T_DOT_PHI       = np.zeros( shape=(dim,dim) ,dtype=np.float64 ) 
    b                   = np.zeros( shape=(dim)     ,dtype=np.float64 ) 

    #Computing coeff Matrix Values
    power_4_x           = list( map( lambda x:x**4 , X ) )
    coeff_mtr_11        = reduce (lambda x,y: x+y, power_4_x)

    power_3_x           = list( map( lambda x:x**3 , X ) )
    coeff_mtr_12        = reduce (lambda x,y: x+y, power_3_x)

    power_2_x           = list( map( lambda x:x**2 , X ) )
    coeff_mtr_13        = reduce (lambda x,y: x+y, power_2_x)

    coeff_mtr_23        = reduce (lambda x,y: x+y, X)


    #Filling matrice coefficienti Sistema Lineare
    PHI_T_DOT_PHI[0][0] = coeff_mtr_11
    PHI_T_DOT_PHI[0][1] = coeff_mtr_12
    PHI_T_DOT_PHI[0][2] = coeff_mtr_13

    PHI_T_DOT_PHI[1][0] = coeff_mtr_12
    PHI_T_DOT_PHI[1][1] = coeff_mtr_13
    PHI_T_DOT_PHI[1][2] = coeff_mtr_23

    PHI_T_DOT_PHI[2][0] = coeff_mtr_13
    PHI_T_DOT_PHI[2][1] = coeff_mtr_23
    PHI_T_DOT_PHI[2][2] = len(X)


    #Computing and Filling Note Term Values 
    y_i_dot_x_i_power_2 = [Y[i]*power_2_x[i] for i in range(len(X))]
    b[0]                = reduce (lambda x,y : x+y , y_i_dot_x_i_power_2)

    y_i_dot_x_i         = [Y[i]*X[i] for i in range(len(X))]
    b[1]                = reduce (lambda x,y : x+y , y_i_dot_x_i)

    b[2]                = reduce (lambda x,y : x+y , Y)


    #Restituisco risultati
    return PHI_T_DOT_PHI,b


#Starting Points
X                           = np.array ( [0.0,1.0,2.0,4.0]  ,  dtype=np.float64 )
Y                           = np.array ( [4.0,3.0,2.0,1.0]  ,  dtype=np.float64 )


#Caso Polinomio Grado 2
A,b                         = fill_least_square_system_grad_2(X,Y,3)

A1,b1                       = gauss_elim(A,b)
theta                       = upper_triangular_solver(A1,b1)

inference                   = lambda x,params: params[0]*x**2 + params[1]*x + params[2]
Y_inference                 = list( map( lambda x: inference(x,theta), X ) )


#Caso Polinomio Grado 1
PHI                         = np.array( [ [0.0,1.0] , [1.0,1.0], [2.0,1.0], [4.0,1.0] ] )
A_grad_1                    = PHI.T.dot(PHI)
b_grad_1                    = PHI.T.dot(Y)

A1_grad_1,b1_grad_1         = gauss_elim(A_grad_1,b_grad_1)
theta_grad_1                = upper_triangular_solver(A1_grad_1,b1_grad_1)

inference_grad_1            = lambda x,params: params[0]*x + params[1]
Y_inference_grad_1          = list( map( lambda x: inference_grad_1(x,theta_grad_1), X ) )


#Plot
plt.plot(X,Y,"or")
plt.plot(X,Y_inference,"b")
plt.plot(X,Y_inference_grad_1,"g")

plt.legend(["Punti","P_2","P_1"])

plt.show()