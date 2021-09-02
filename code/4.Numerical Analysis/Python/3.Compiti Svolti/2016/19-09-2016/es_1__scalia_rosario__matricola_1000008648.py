"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from functools import reduce
from numpy.linalg.linalg import LinAlgError
from matplotlib import pyplot as plt

SHAPE_RUNTIME_ERROR = -1


def build_jacobi_iter_fun (A,b):
    #Eq Jacobi: x = M^{-1}*N*x + M^{-1}*b
    # M = diag(A)
    # N = M - A
    #Lunghezza b
    dim     = len(b)

    #Costruzione Matrice M Jacobi
    #M = diag(A)
    M       = np.zeros(shape=(dim,dim))
    for i in range(dim):
        M[i][i] = A[i][i]

    #Costruzione Matrice N Jacobi
    #N      = M - A
    N       = M - A

    #Costruzione Matrice M Inversa
    M_inv  = np.zeros(shape=(dim,dim))
    for i in range(dim):
        M_inv[i][i] = 1/M[i][i]

    #Costruzione Matrice Iterazione Jacobi
    B       = matrix_matrix_mul(M_inv,N)
    c       = matVecMul(M_inv,b)

    #Costruzione Iterazione Funzionale Jacobi
    PHI     = lambda x: matVecMul(B,x) + c

    #Restituisco Output
    return PHI,B,M_inv


def build_gauss_heidel_iter_fun (A,b):
    #Eq Jacobi: x = M^{-1}*N*x + M^{-1}*b
    # M = D - E
    # N = F
    dim     = len(b)

    #Costruzione Matrice M
    D       = np.zeros(shape=(dim,dim))
    for i in range(dim):
        D[i][i] = A[i][i]

    E       = np.zeros(shape=(dim,dim))
    for i in range (dim):
        for j in range(i):
            E[i][j] = -A[i][j]
        
    M       = D-E


    #Costruzione Matrice N
    F       = np.zeros(shape=(dim,dim))
    for i in range(dim):
        for j in range(i+1,dim):
            F[i][j] = -A[i][j]
    N       = F

    #Costruzione Matrice Iterazione
    M_inv   = np.linalg.inv(M)
    B       = matrix_matrix_mul(M_inv,N)
    c       = matVecMul(M_inv,b)

    #Costruzione Iterazione Funzionale
    PHI     = lambda x: matVecMul(B,x) + c

    return PHI,B


def norm2 (x,y):
    xy_pairs        = list(zip(x,y))
    diff_xy         = list( map( lambda x: x[0]-x[1] , xy_pairs ) )
    power_diff_xy   = list( map( lambda x: x*x , diff_xy ) )
    l2_distance     = reduce (lambda x,y: x+y,power_diff_xy)

    return l2_distance

def dot (x,y):
    lin_comb        = [x[i]*y[i] for i in range(len(x)) ]
    result          = reduce(lambda x,y: x+y,lin_comb)

    return result

def matrix_matrix_mul(A,B):
    if (type(A) != np.ndarray):
        A = np.array(A)

    if (type(B) != np.ndarray):
        B = np.array(B)

    if (A.shape[1] != B.shape[0]):
        print ("[WARNING] ShapeRuntimeError, Inner dimension of Matrices to multiply must match !")
        raise LinAlgError


    n_rows_a    = A.shape[0]
    inner_dim   = A.shape[1]

    C           = np.zeros( shape=( A.shape[0] , B.shape[1] ) ,dtype=np.float64 )

    for i in range(n_rows_a):
        C[i] = np.array( [dot( A[i],B[:,j] ) for j in range(inner_dim) ] )

    return C

def matVecMul (A,x):
    return np.array( [dot(A[i],x) for i in range(len(x))] )


def iterative_matrix_methods_solver(A,b,x_0,PHI,max_iter , B=None, M_inv=None):
    i           = 0
    x           = x_0
    iterations  = []
    residuals   = []

    while (i<max_iter):

        if (type(B) != type(None) and type(M_inv) != type(None)):
            x = matVecMul(B,x) + matVecMul(M_inv,b)
        else:
            x = PHI(x)
            
        i+=1

        #Calcolo Residuo
        iterations.append(i)
        current_out     = matVecMul(A,x)
        residuals.append( norm2(current_out,b) )


    return x, iterations, residuals


def jacobi_scalar (A,b,x0,max_iter):

    dim         = len(b)
    i           = 0
    sol         = x0
    iterations  = []
    residuals   = []
    
    while (i<max_iter):

        #Itero sulle Soluzioni da Trovare
        for j in range(dim):

            sum_term_1 = 0.0
            for k in range(j):
                sum_term_1 += A[j][k] * sol[k]

            sum_term_2 = 0.0
            for k in range(j+1,dim):
                sum_term_2 += A[j][k] * sol[k]
                

            sol[j] = (b[j] - sum_term_1 - sum_term_2)/A[j][j]

        i+=1

        #Calcolo Residuo
        iterations.append(i)
        current_out     = matVecMul(A,sol)
        residuals.append( norm2(current_out,b) ) 

    

    return sol,iterations, residuals


def gauss_heidel_scalar (A,b,x0,max_iter):

    dim         = len(b)
    i           = 0

    sol         = x0
    sol_old     = x0.copy()
    iterations  = []
    residuals   = []

    
    while (i<max_iter):

        #Itero sulle Soluzioni da Trovare
        for j in range(dim):

            sum_term_1 = 0.0
            for k in range(dim-1,j,-1):
                sum_term_1 += A[j][k]*sol_old[k]

            sum_term_2 = 0.0
            for k in range(j):
                sum_term_2 += A[j][k]*sol[k]

            sol[j] = (b[j] - sum_term_1 - sum_term_2)/A[j][j]

        sol_old = sol.copy()

        i+=1

        #Calcolo Residuo
        iterations.append(i)
        current_out     = matVecMul(A,sol)
        residuals.append( norm2(current_out,b) )


    return sol,iterations,residuals



#INPUT
A           = np.array( [ 
                [2.0,1.0,1.0],
                [1.0,2.0,1.0],
                [1.0,1.0,2.0]  ] , dtype=np.float64 )

x0          = np.array( [1.0,1.0,1.0] , dtype=np.float64 )
b           = np.array( [1.0,0.0,0.0] , dtype=np.float64 )
MAX_ITER    = 11
X_GT        = [3/4, -1/4, -1/4]


#Stampa Soluzione Esatta
print ("\n[DEF] Soluzione Esatta: {}".format(X_GT))


#Calcolo Matrice Iterazione Jacobi e il suo Autovalore Massimo
PHI_J, B_J, G_M_inv                             = build_jacobi_iter_fun(A,b)
max_autoval = max(np.linalg.eigvals(B_J))
print ("\n[!] Raggio Spettrale Matrice Iterazione Jacobi: {}".format(max_autoval))

#Calcolo Soluzione Jacobi MTR
sol,iterations_JM, residuals_JM                 = iterative_matrix_methods_solver(A, b, x0, PHI_J, MAX_ITER , B_J, G_M_inv)
print ("[JACOBI-MTR] Soluzione: {} ".format(sol))



#Calcolo Soluzioni Jacobi Scalar
sol_j, iterations_JS, residuals_JS     = jacobi_scalar(A,b,x0,MAX_ITER)
print ("\n[JACOBI-SCALAR] Soluzione: {} ".format(sol_j))


#Calcolo Matrice Iterazione Gauss e il suo Autovalore Massimo
PHI_G,B_G           = build_gauss_heidel_iter_fun(A,b)
max_autoval         = max(np.linalg.eigvals(B_G))
print ("\n[!] Raggio Spettrale Matrice Iterazione Gauss: {}".format(max_autoval))

#Calcolo Soluzione Gauss MTR
sol_g, iterations_GM, residuals_GM = iterative_matrix_methods_solver(A,b,x0,PHI_G,MAX_ITER)
print ("[GAUSS-MTR] Soluzione: {}  ".format(sol_g))


#Calcolo Soluzioni Gauss-Heidel Scalar
sol_gh, iterations_GS, residuals_GS          = gauss_heidel_scalar(A,b,x0,MAX_ITER)
print ("\n[GAUSS-SCALAR] Soluzione: {} \n".format(sol_gh))



#Plot Grafico
plt.plot(iterations_JS,residuals_JS, color="r")
plt.plot(iterations_GS, residuals_GS, color="b")
plt.plot(iterations_JM, residuals_JM,color="g")
plt.plot(iterations_GM, residuals_GM, color="black")

plt.title("Analisi Metodi Iterativi - Grafico Iterazioni vs Residuo")
plt.xlabel("Iterazioni")
plt.ylabel("Residuo")
plt.legend(["Jacobi Scalar","Gauss-Heidel Scalar","Jacobi Vector", "Gauss Vector"])

plt.xticks([1,2,3,4,5,6,7,8,9,10,11])
plt.show()