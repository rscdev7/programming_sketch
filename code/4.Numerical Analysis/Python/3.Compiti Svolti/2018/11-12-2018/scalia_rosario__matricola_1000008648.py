"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""
import numpy as np
from math import pi, cos, sin
from matplotlib import pyplot as plt

def es_1__gauss_elim (M,b):
    dim = len(b)

    A   = M.copy()

    #Itero sulle Incognite da Cancellare 
    for i in range(dim):

        #Itero sulle restanti righe sotto l'incognita da trovare
        for j in range(i+1,dim):
            m__j_i  = M[j][i] / M[i][i]

            A[j][i] = 0.0
            for k in range(j+1,dim):
                A[j][k] -= M[i][k]*m__j_i

            b[j]    -= b[i]*m__j_i

    return (A,b) 

def es_1__upper_triangular_solver(M,b):

    dim = len(b)
    sol = np.zeros(shape=dim)

    #Itero sulle incognite da trovare 
    for i in range(dim-1 , -1, -1):

        if (i == dim-1):
            sol[i] = b[i]/M[i][i]
        else:
            sum_term = 0.0

            for j in range(dim-1,i,-1):
                sum_term += M[i][j]*sol[j]

            sol[i]  = (b[i] - sum_term)/M[i][i]

    return sol



def es__1_test():
    X       = np.array ( [1,2,3,4,5] )
    Y       = np.array( [0.5,0.0,-0.5,1.0,0.75] )
    dim_x   = 5


    """
    P1(x) = ax^2 + b*x + c
    P2(x) = ax^3 + b*x^2 + c*x + d
    """

    #P1 Computations

    #Build SYSTEM MATRIX AND note TEMR
    PHI_P1  = np.zeros(shape=(dim_x,3))
    for i in range(dim_x):
        PHI_P1[i][0] = 1.0
        PHI_P1[i][1] = X[i]
        PHI_P1[i][2] = X[i]**2

    PHI_P1_T = PHI_P1.T

    MTR_P1          = PHI_P1_T.dot(PHI_P1)
    NOTE_TERM_P1    = PHI_P1_T.dot(Y)

    #Solve linear system in order to get model params
    MG_P1,NTG_P1    = es_1__gauss_elim(MTR_P1,NOTE_TERM_P1)

    P1_PARAMS       = es_1__upper_triangular_solver(MG_P1,NOTE_TERM_P1)

    #Check System Solution
    print("P1_CHECK \nM*sol = {} \nNote Term = {}".format(MG_P1.dot(P1_PARAMS),NOTE_TERM_P1))

    #Compute P1 Least Square Error
    err_p1  = 0.0
    p1      = lambda x,p: p[0] + p[1]*x + p[2]*x**2
    for i in range(dim_x):
        pol_val = p1(X[i],P1_PARAMS)
        err_p1 += (pol_val - Y[i])**2

    err_p1 /=2

    print ("[!] Errore Parabola: {} ".format(err_p1))


    #P2 Computations

    #Build SYSTEM MATRIX AND note TEMR
    PHI_P2  = np.zeros(shape=(dim_x,4))
    for i in range(dim_x):
        PHI_P2[i][0] = 1.0
        PHI_P2[i][1] = X[i]
        PHI_P2[i][2] = X[i]**2
        PHI_P2[i][3] = X[i]**3

    PHI_P2_T        = PHI_P2.T

    MTR_P2          = PHI_P2_T.dot(PHI_P2)
    NOTE_TERM_P2    = PHI_P2_T.dot(Y)


    #Solve linear system in order to get model params
    MG_P2,NTG_P2    = es_1__gauss_elim(MTR_P2,NOTE_TERM_P2)
    P2_PARAMS       = es_1__upper_triangular_solver(MG_P2,NTG_P2)

    #Check System Solution
    print("P2_CHECK \nM*sol = {} \nNote Term = {}".format(MG_P2.dot(P2_PARAMS),NOTE_TERM_P2))

    #Compute P1 Least Square Error
    err_p2  = 0.0
    p2      = lambda x,p: p[0] + p[1]*x + p[2]*x**2 + p[3]*x**3
    for i in range(dim_x):
        pol_val = p2(X[i],P2_PARAMS)
        err_p1 += (pol_val - Y[i])**2

    err_p2 /=2

    print ("[!] Errore Cubica: {} ".format(err_p2))


def es_2__zero_fun_compute(f,p,tol,k, max_iter):

    dx = 1.0
    i = 0

    while (abs(dx) > tol and i < max_iter):
        dx      = - f(p)/k 
        p       = p + dx
        i+=1

    print ("K={} - Sol: {} - f(Sol): {} - Iterations: {}".format(k,p,f(p) , i ))


def es_2__test():
    f = lambda x:x**3 - 4*x

    points = np.linspace(1.5,2.5,1000)
    f_p    = list( map ( lambda x: f(x) , points ) )

    plt.plot(points,f_p)
    plt.axhline(y=0,color="r")
    plt.show()

    print ("Case K=4: \n")
    es_2__zero_fun_compute(f, 2.5, 10e-5, 4,100)

    print ("Case K=8: \n")
    es_2__zero_fun_compute(f, 2.5, 10e-5, 8,100)

def es_3__simpson_composita(f,a,b,NS):

    H = (b-a)/NS

    S = f(a) + f(b)

    for i in range(NS-1):
        node = a + (i+1)*H
        S += 2.0 * f(node)

    for j in range(NS):
        node = a + (0.5+i)*H
        S += 4.0 * f(node)

    S = S*H/6

    return S

def es_3__trapezi_composita(f,a,b,NT):

    T = (f(a)+f(b))/2
    h = (b-a)/NT


    for i in range(NT-1):
        node = a + (i+1)*h
        T += f(node)

    T *= h

    return T



def es_3__test():

    f = lambda x: sin(x*pi) - 2*cos(pi*a) 
    a   = 0.5
    b   = 1.5
    tol = 10e-2


    NT  = 5
    T1  = es_3__trapezi_composita(f,a,b,NT)
    T2  = es_3__trapezi_composita(f,a,b,NT*2)
    diff_trap = abs(T1 - T2/3)
    esito     = diff_trap < tol
    print ("[!] Errore Trapezi: {} - Esito: {}".format(diff_trap,esito))


    NS  = 29
    S1  = es_3__simpson_composita(f,a,b,NS)
    S2  = es_3__simpson_composita(f,a,b,NS*2)
    err_simpson = abs(1/15*(S1 - S2))
    esito_simp  = err_simpson < tol
    print ("[!] Errore Simpson: {} - Esito: {}".format(err_simpson,esito_simp)) 

es__1_test()
es_2__test()
es_3__test()