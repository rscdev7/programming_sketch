import numpy as np



def lu_F(A):
    dim = len(A[0])
    sol = [0.0]*dim
    L   = np.eye(dim)

    for i in range(dim):
        for j in range(i+1,dim):
            m__ji       = A[j][i]/A[i][i]

            L[j][i]     = int(m__ji)
            A[j][i]     = 0.0

            for k in range(j+1,dim):
                A[j][k] = A[j][k] - m__ji * A[i][k]

    return (L,A)



def upper_triangular_solver (A,b):

    dim = len(b)
    sol = np.zeros(shape=(dim))

    for i in range(dim-1,-1,-1):

        if (i== dim-1):
            sol[i] = b[i]/A[i][i]
        else:
            sum_term = 0.0
            for j in range(dim-1,i,-1):
                sum_term += A[i][j]*sol[j]

            sol[i] = (b[i] - sum_term)/A[i][i]

    return sol

def lower_triangular_solver(A,b):
    dim = len(b)
    sol = np.zeros(shape=(dim))

    for i in range(dim):

        if (i==0):
            sol[i] = b[i] / A[i][i]
        else:

            sum_term = 0.0
            for j in range(i):
                sum_term += A[i][j]*sol[j]

            sol[i] = (b[i] - sum_term) / A[i][i]

    return sol

def es_1__test():
    A = np.array([
                 [4.0,0.0,-1.0],
                 [0.0,2.0,1.0],
                 [-1.0,1.0,3.0]
    ])
    b = np.array([2.0,0.0,1.0])
    
    L,U = lu_F(A)   
    
    y = lower_triangular_solver(L,b)
    sol = upper_triangular_solver (U,y)

    print(A.dot(sol),b)

es_1__test()