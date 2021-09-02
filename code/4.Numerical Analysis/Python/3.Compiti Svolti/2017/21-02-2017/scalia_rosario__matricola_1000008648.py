"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
- Data: 15/06/2021

"""

import numpy as np
from math import cos,sin,pi,log,exp
from matplotlib import pyplot as plt
from functools import reduce
from numpy.linalg import eig
from numpy.linalg import inv


def es_1__jacobi (A,b,max_iter,x_0):
    sol = x_0
    dim = len(b)
    
    for i in range(max_iter):
        
        for j in range(dim):
            
            sum_term_1 = 0.0
            
            for k in range(j):
                sum_term_1 += A[j][k] * sol[k]
                
            for k in range(j+1,dim):
                sum_term_1 += A[j][k] * sol[k]
                
            sol[j] = (b[j] - sum_term_1) / A[j][j]
        
        
        a_dot_sol = A.dot(sol)
        
        residual = []
        
        for j in range(dim):
            diff = b[j] - a_dot_sol[j]
            diff = diff**2
            residual.append(diff)
            
        residual_v = reduce (lambda a,b: a+b, residual)
        
        residual_v = residual_v**(1/2)
        
        print ("\n[!] Residuo Jacobi: {} - Iterazione: {}".format(residual_v, i+1))
        
        
def es_1__gauss (A,b,max_iter,x_0):
    sol         = x_0
    sol_old     = x_0
    dim = len(b)
    
    for i in range(max_iter):
        
        for j in range(dim):
            
            sum_term_1 = 0.0
            
            for k in range(j):
                sum_term_1 += A[j][k] * sol[k]
                
            sum_term_2 = 0.0
            for k in range(j+1,dim):
                sum_term_2 += A[j][k] * sol_old[k]
                
            sol[j] = (b[j] - sum_term_1 - sum_term_2) / A[j][j]
        
        
        sol_old = sol.copy()
        a_dot_sol = A.dot(sol)
        
        residual = []
        
        for j in range(dim):
            diff = b[j] - a_dot_sol[j]
            diff = diff**2
            residual.append(diff)
            
        residual_v = reduce (lambda a,b: a+b, residual)
        
        residual_v = residual_v**(1/2)
        
        print ("\n[!] Residuo Jacobi: {} - Iterazione: {}".format(residual_v, i+1))
        

def es_1__test():
    A = np.array( [ [3.0,-2.0,0.0], 
                    [-2.0, 4.0, 2.0],
                    [0.0, 2.0, 2.0]
                   ] )
    x_0 = np.array( [1.0,0.0,0.0] )
    b   = np.array( [1.0,4.0,4.0] )
    
    
    #Matrice Iterazione Jacobi
    M = np.array( [ [3.0,0.0,0.0], 
                    [0.0, 4.0, 0.0],
                    [0.0, 0.0, 2.0]
                   ] )
    M_inv = np.array( [ [1/3.0,0.0,0.0], 
                    [0.0, 1/4.0, 0.0],
                    [0.0, 0.0, 1/2.0]
                   ] )
    N = M - A
    
    B = N*M_inv  
    
    autoval,autovett = eig(B)
    
    print (autoval,autovett)
    
    
    #Matrice Iterazione Gauss
    E = np.array( [ [0.0,0.0,0.0], 
                    [2.0, 0.0, 0.0],
                    [0.0, -2.0, 0.0]
                   ] )
    D = np.array( [ [3.0,0.0,0.0], 
                    [0.0, 4.0, 0.0],
                    [0.0, 0.0, 2.0]
                   ] )
    F = np.array( [ [0.0,+2.0,0.0], 
                    [0.0, 0.0, -2.0],
                    [0.0, 0.0, 0.0]
                   ] )
    
    M = D - E
    N = -F
    M_inv = inv(M)
    
    B = N*M_inv  
    
    autoval,autovett = eig(B)
    
    print (autoval,autovett)
    
    
    es_1__jacobi(A,b,10,x_0)
    
    
def es_2__eval_lagrange(inp,x,y):
    
    lagrange_polynomials    = [1.0]*len(x)
    dim                     = len(x)
    
    for i in range(dim):
        for j in range(dim):
            if (i != j):
                lagrange_polynomials[i] *= ( (inp - x[j]) / (x[i] - x[j]) )
    
    res = 0.0
    for i in range(dim):
        res += y[i]* lagrange_polynomials[i]
        
    return res


def es_2__test():
    f = lambda a:sin(2*a)
    x = np.array([ 0.0 , pi/4 , pi/2 ] ) 
    y = list ( map( lambda a:f(a) , x ) )
    y_p = list ( map( lambda a: es_2__eval_lagrange(a,x,y) , x ) )
     
    wq = es_2__eval_lagrange(-pi/4,x,y)
    
    plt.plot(x,y,"ob")
    plt.plot(x,y_p,"g")
    plt.plot(-pi/4,wq,"or")
    plt.plot (-pi/4 , f(-pi/4), "og")
    plt.plot()


def es_3__newotn(f,f_der,start_p,tol,max_iter):
    
    dx = 1.0
    p = start_p
    i = 0
    while (abs(dx) > tol and i < max_iter):
        dx = - f(p)/f_der(p)
        p = p + dx
        i+=1
    
    if (abs(dx) < tol):
        print ("Uscito perchè la Soglia è stata d'errore è stata soddisfatta")
    
    return (p,f(p),i)
    
def es_3__test():
    f = lambda x: x + log(x+1)
    f_der = lambda x:1 + 1/(x + 1)
    a = -0.5
    b = 0.5
    
    
    print (f(a),f(b))
    
    _,fp,iters = es_3__newotn(f,f_der,-0.5,10e-8,5)
    
    print ("f(x):{} - Iter: {}".format(fp,iters))
    
    
def es_3__trapezi (f,a,b,N):
    
    h = (b-a)/N
    
    T = (f(a)+f(b))/2
    
    for i in range(N-1):
        p = a + (i+1)*h
        T += f(p)
        
    T *= h
    
    return T
    
def es_4__test():
    
    f = lambda x:x*exp(-x)
    
    a = 0.0
    b = 1.0
    N = 5
    tol = 10e-4
    T1 = es_3__trapezi(f,a,b,N)
    T2 = es_3__trapezi(f,a,b,N*2)
    
    print ( abs( (T1 - T2)/3 ) < tol )
    
es_2__test()