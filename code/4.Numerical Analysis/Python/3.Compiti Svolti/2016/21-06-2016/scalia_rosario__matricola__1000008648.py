import numpy as np
from matplotlib import pyplot as plt
from functools import reduce
from math import exp,sqrt,pi

A = np.array( [[2.0,1.0,1.0], 
               [1.0,2.0,1.0],
               [1.0,1.0,2.0] ] )




def norm2 (x):
    norm_x = 0.0
    for i in range(len(x)):
        norm_x += x[i]**2
        
    return norm_x

def power_method (A,max_iter,x,tol):
    
    i     = 0
    check = 1.0
    
    while i < max_iter and check > tol:
        
        #Normalizzo Vettore x
        maxx   = np.max(x)
        x_norm = np.zeros(shape=(len(x)))
        for i in range(len(x)):
            x_norm[i] = x[i] / maxx 
            
        
        #Calcolo A*x
        for i in range(len(x)):
            x[i] = 0.0
            for j in range(len(x)):
                x[i] += A[i][j] * x_norm[j]
                
        #Calcolo Quoziente di Raylength  
        yx = 0.0
        for i in range(len(x)):
            yx += x_norm[i]*x[i]
        
        yy = 0.0
        for i in range(len(x)):
            yy += x_norm[i]*x_norm[i]
            
        eigenvalue = yx/yy
        
        numerator   = norm2(x - eigenvalue*x_norm)
        denominator = norm2(x)
        
        if (denominator != 0.0):
            check = numerator/denominator
        else:
            check = 0.0
            
        i += 1
        
    if (check < tol):
        print ("Uscito perchè superata tolleranza")
        
    return eigenvalue


def gauss_heidel (A,x_0,b,max_iter):
    
    dim = len(b)
    sol = x_0
    sol_old = x_0
    
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
        
        ax = A.dot(sol)
        
        diff = list ( map( lambda a: a[0]-a[1] , list(zip(b,ax)) ) )
        
        pow_diff = list(map ( lambda a: a**2, diff ))
        
        sum_pow_diff = reduce (lambda x,y : x+y,pow_diff)
        
        residual    = sum_pow_diff*(1/2)
        
        print ("[Gauss] Residuo: {} - Iterazione: {}".format(residual,i+1))
        
        print (A.dot(sol),b)
        
        
def jacobi (A,x_0,b,max_iter):
    
    dim = len(b)
    sol = x_0
    
    for i in range(max_iter):
        
        for j in range(dim):
            
            sum_term_1 = 0.0
            for k in range(j):
                sum_term_1 += A[j][k] * sol[k]
                
                
            sol[j] = (b[j] - sum_term_1 ) / A[j][j]
            
                    
        ax = A.dot(sol)
        
        diff = list ( map( lambda a: a[0]-a[1] , list(zip(b,ax)) ) )
        pow_diff = list(map ( lambda a: a**2, diff ))
        sum_pow_diff = reduce (lambda x,y : x+y,pow_diff) 
        residual    = sum_pow_diff*(1/2)
        
        print ("[Jacobi] Residuo: {} - Iterazione: {}".format(residual,i+1))
        
        print (A.dot(sol),b)
        

def es_1__test ():
    #Jacobi Iteration Matrix
    M    =np.array( [
                    [2.0,0.0,0.0], 
                    [0.0,2.0,0.0],
                    [0.0,0.0,2.0] 
                    ] )
    N    = M - A
    
    I = np.array( [[1.0,0.0,0.0], 
                   [0.0,1.0,0.0],
                   [0.0,0.0,1.0] ] )
    
    B_J = I-np.linalg.inv(M)*N
    x_0 = [1.0,1.0,1.0]
    eig_j = power_method(B_J,1000,x_0,10e-5)
    print ("Jacobi Eig: {} - Jacobi Matrix: {}".format(eig_j , B_J))
    
    
    
    D    =np.array( [
                    [2.0,0.0,0.0], 
                    [0.0,2.0,0.0],
                    [0.0,0.0,2.0] 
                    ] )
    E    =np.array( [
                    [0.0,0.0,0.0], 
                    [-1.0,0.0,0.0],
                    [-1.0,-1.0,0.0] 
                    ] )
        
    M  = D-E
    F  = np.array( [
                    [0.0,-1.0,-1.0], 
                    [0.0,0.0,-1.0],
                    [0.0,0.0,0.0] 
                   ] )
    N = -F
    
    B_G = np.linalg.inv((D-E))*N
    
    x_0 = [1.0,1.0,1.0]
    eig_g = power_method(B_G,1000,x_0,10e-5)
    print ("Gauss Eig: {} - Gauss Matrix: {}".format(eig_g , B_G))
    
    
    x_0 = [1.0, 0.0, 0.0] 
    b   = [1.0, 4.0, 4.0]
    gauss_heidel (A,x_0,b,10)
    jacobi(A,x_0,b,10)
    
    
def es_2__newton_compute_base(x,y):
    dim = len(x)
    diff_div = y.copy()
    
    for i in range(1,dim):
        
        for j in range(dim-1, i-1 , -1):
            diff_div[j] = (diff_div[j] - diff_div[j-1]) / (x[j] - x[j-i])
    
    return diff_div


def es_2__newton_eval(p,base,nodes):
    lgh = len(nodes) - 1
    y = base[lgh]
    
    for i in range(lgh-1, -1,-1):
        y *= (p-nodes[i])
        y += base[i]
        
    return y
    
    
    
def es_2__test():
    x = np.array( [ -2.0 , 1.0, 4.0 , -1.0 ] )
    y = np.array ( [ -1.0, 2.0 , 59.0 , 4.0 ] )
    
    
    base = es_2__newton_compute_base(x, y)
    
    interp_x = list ( map( lambda a: es_2__newton_eval(a, base, x), x ) )
    
    plt.plot(x,y,"ob")
    plt.plot(x,interp_x,"r")
    plt.show()
    
    
def es_3__newton(f,f_der, p, max_iter, tol):
    dx = 1.0
    i  = 0
    x  = p
    
    while (abs(dx) > tol and i < max_iter ):
        dx = - f(x)/f_der(x)
        x = x+ dx
        i+=1
        
    if (abs(dx) < tol):
        print ("x: {} - f(x): {} - dx<tol - Iter: {}".format(x,f(x),i))
    else:
        print ("x: {} - f(x): {} - dx>tol - Iter: {}".format(x,f(x),i))

    
def es_3__test():
    f = lambda a:exp(a) - 3*a**3
    f_1 = lambda a:-9*a**2 + exp(a)
    x_0 = 1.0
    
    es_3__newton(f,f_1,x_0,1000,10e-2)
    
    
es_3__test()
    
          
          
        
        