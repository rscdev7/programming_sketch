import numpy as np
from math import cos,sin,pi,sqrt
import math

A = np.array( [
                [3.0,-1.0,2.0],
                [-1.0,4.0,3.0],
                [2.0,3.0,6.0]
              ] )

b = np.array( [0.0,4.0,7.0] )


def is_symmetric(A):
    dim = len(A[0])
    
    for i in range(dim):
        for j in range(dim):
            if (A[i][j] != A[j][i]):
                return False
            
    return True

def check_definite_positive(A):
    dim = len(A[0])
    
    for i in range(1,dim):
        sub_matrix = A[0:i+1,0:i+1]
        
        det = np.linalg.det(sub_matrix)
        
        if (det == 0):
            return False
        
    return True

def choleski_fat(A):
    dim = len(A[0])
    R = np.zeros(shape=(dim,dim))
    
    for i in range(dim):
        
        for j in range(i,dim):
            
            if (i==j):
                sum_r = 0.0
                
                #Sommo la colonna j-esima delle righe 0-i
                for k in range(i):  
                    sum_r += R[k][j]**2
                    
                R[i][i] = sqrt(A[i][i] - sum_r)
            else:
                sum_r = 0.0
                
                #Per ogni riga, faccio il prodotto dell'elemento i con quello j
                for k in range(i):  
                    sum_r += R[k][i] * R[k][j]
                    
                R[i][j] = (A[i][j] - sum_r)/R[i][i]
                
    return R

def upper_triangular_solver (A,b):
    
    dim = len(b)
    sol = np.array([0.0]*dim)
    
    #Itero sulle soluzioni
    for i in range(dim-1,-1,-1):
        
        if (i==dim-1):
            sol[i] = b[i]/A[i][i]
        else:
            sum_term = 0.0
            for j in range(dim-1,i,-1):
                sum_term += A[i][j]*sol[j]
                
            sol[i] = (b[i] -sum_term)/A[i][i]
            
    return sol

def lower_triangular_solver(A,b):
    dim = len(b)
    sol = np.zeros(shape=(dim))
    
    for i in range(dim):
        
        if (i==0):
            sol[i] = b[i]/A[i][i]
        else:
            sum_term=0.0

            for j in range(i):
                sum_term += A[i][j]*sol[j]

            sol[i] = (b[i] - sum_term)/A[i][i]

    return sol   



def es_1__test():
    print(is_symmetric(A))
    print(check_definite_positive(A))
    
    R = choleski_fat(A)
    
    
    #Solve R*y=b
    y = lower_triangular_solver(R.T,b)
    
    x = upper_triangular_solver(R,y)
    print (A.dot(x),b)
    
    
def es_4__trapezi_comp (f,a,b,N):
    h = (b-a)/N
    
    T = (f(a)+f(b))/2
    
    for i in range(N-1):
        p = a + (i+1)*h
        T += f(p)
        
    T += h
    
    return T

def es_4__test():
    f = lambda x:sin(x)
    f_int = -cos(1.0) + cos(0.0)
    
    
    N1 = 1
    T1 = es_4__trapezi_comp(f,0.0,1.0,N1)
    print (T1)
    
    N1 = 2
    T1 = es_4__trapezi_comp(f,0.0,1.0,N1)
    print (T1)
    
    N1 = 3
    T1 = es_4__trapezi_comp(f,0.0,1.0,N1)
    print (T1)
    
    print ("Integrale Esatto: {}".format(f_int))
    
    
    

es_4__test()


