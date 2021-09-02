"""
- Nominativo: Rosario Scalia


"""


from numpy.linalg import eig,inv
import numpy as np
from matplotlib import pyplot as plt
from math import sqrt,cos,pi,log



def diff_div (x,f_x):
    
    dim = len(x)
    diff_div = f_x.copy()
    
    #Itero sulle differenze divise da calcolare
    for i in range(1,dim):
        
        for j in range(dim-1 , i-1 , -1):
            
            diff_div[j] = (diff_div[j] - diff_div[j-1]) / (x[j] - x[j-i])
            
    return diff_div


def newton_eval (x,F,X):
    dim = len(X) - 1
    
    V = F[dim]
    
    for i in range(dim-1,-1,-1):
        V *= (x-X[i])
        V += F[i]
        
    return V


def es_1():
    A   = np.array([[2.0,1.0,1.0] , [1.0,2.0,1.0] , [1.0,1.0,2.0]])
    D   = np.array([ [2.0, 0.0, 0.0] , [0.0,2.0,0.0] , [0.0,0.0,2.0]])
    D_I = np.array([ [1/2.0, 0.0, 0.0] , [0.0,1/2.0,0.0] , [0.0,0.0,1/2.0]])
    
    mask   = np.zeros(shape=(3,3))
    mask_f = np.zeros(shape=(3,3))
    for i in range(3):
        for j in range(i,-1,-1):
            mask[i][j] = -1.0
            
    for i in range(3):
        for j in range(i+1):
            mask_f[i][j] = -1.0
            
    E = A*mask
    F = A*mask_f
    
    
    #Matrice Iterazione Jacobi
    B_J = np.eye(3,3) - D_I.dot(A)
    print ("\n[!] Matrice Iterazione Jacobi: \n{}\n".format(B_J))
    res = eig(B_J)
    print ("[!] Autovalore di Modulo Massimo Jacobi: {} \n".format(max(res[0])))
    
    
    #Matrice Iterazione Gauss-Seidel
    B_G = inv( (D-E) ).dot(F)
    print ("\n[!] Matrice Iterazione Gauss: \n{}\n".format(B_G))
    print(B_G)
    
    res = eig(B_G)
    print ("\n[!] Autovalore di Modulo Massimo Gauss-Seidel: {} \n".format(max(res[0])))
    
    
    
    f       = lambda k: (3/(2*k+2))**(1/k)
    
    points = list(range(1,10000000,2))
    f_p    = list( map( lambda a: f(a), points ) )
    
    
    
    plt.plot(points,f_p)
    plt.show()


def build_cheb_nodes (n_nodes):
    cheb = lambda a,n: (- cos( ( (a + 0.5 ) / n ) * pi  ) ) * 5
    cheb_nodes = np.zeros(shape=(n_nodes))
    
    for i in range(n_nodes):
        cheb_nodes[i] = cheb(i,n_nodes)
        
    return cheb_nodes
    
    
    
    
def es_2 ():
    f = lambda a:1 / (1 + a**2)
    
    n_6  = build_cheb_nodes(6)
    n_10 = build_cheb_nodes(10)
    n_30 = build_cheb_nodes(30)
    
    f_6  = list( map( lambda a:f(a) , n_6 ) )
    base_6 = diff_div(n_6,f_6)
    newton_6 = list( map ( lambda a: newton_eval(a,base_6,n_6) , n_6 ) )
    
    f_10  = list( map( lambda a:f(a) , n_10 ) )
    base_10 = diff_div(n_10,f_10)
    newton_10 = list( map ( lambda a: newton_eval(a,base_10,n_10) ,n_10  ) )
    
    
    
    f_30  = list( map( lambda a:f(a) , n_30 ) )
    base_30 = diff_div(n_30,f_30)
    newton_30 = list( map ( lambda a: newton_eval(a,base_30,n_30) , n_30 ) )
    
    
    plt.plot(n_6,f_6)
    plt.plot(n_6,newton_6)
    plt.plot(n_10,f_10)
    plt.plot(n_10,newton_10)
    plt.plot(n_30,f_30)
    plt.plot(n_30,newton_30)
    plt.legend(["f(x)_6","Newton_Interp_6" , "f(x)_10","Newton_Interp_10", "f(x)_30","Newton_Interp_30" ])
    plt.plot()
    
    
def simpson (f,N,a,b):
    
    h = (b-a)/N
    
    S = f(a)+f(b)
    
    for i in range(N-1):
        p = a + (i+1)*h
        S += 2*f(p)
        
    for i in range(N):
        p = a + (i+0.5)*h
        S+= 4*f(p)
        
    S *= (h/6)
    
    return S
    
def es_3 ():
    
    N = 2
    a = 5
    b = 10
    tol  = 10e-4
    f    = lambda x:log(x)
    res  = simpson(f,N,a,b)
    res2 = simpson(f,N*2,a,b)
    
    print(res)
    print ( abs (1/15 * (res - res2))<tol )
    
    
    exact_int = lambda a:a*log(a) - a
    exact_int_d =  exact_int(10) - exact_int(5)
    
    print(exact_int_d)
         
    
es_3 ()
    
