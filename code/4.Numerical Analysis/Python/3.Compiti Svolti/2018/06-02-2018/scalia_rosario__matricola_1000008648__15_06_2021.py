"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
- Data: 15-06-2021

"""

import numpy as np
from math import log,exp, sin,cos,pi
from matplotlib import pyplot as plt


def es_1__find_newton_interp_base(x,y):
    
    dim = len(x)
    diff_div = y.copy()
    
    for i in range( 1,dim):
        
        for j in range(dim-1 , i-1 , -1):
            diff_div[j] = (diff_div[j] - diff_div[j-1] ) / (x[j] - x[j - i])
            
    return diff_div

def es_1__pol_eval (p,x,base):
    
    dim = len(x)
    
    ev = base[dim-1]
    
    for i in range(dim - 2, -1,-1):
        ev *= (p - x[i])
        ev += base[i]
        
    return ev

def es_1__test():
    x = np.array( [-1.0,-0.5,0.0,0.5,1.0] )
    f = lambda a:exp(a**2-1)
    y = list ( map( lambda a: f(a) , x ) )
    
    base = es_1__find_newton_interp_base(x,y)
    
    interp = list ( map ( lambda a: es_1__pol_eval(a, x, base) , x ) )
    
    plt.plot(x,y,"or")
    plt.plot(x,interp,"b")
    plt.legend(["Punti","Newton_Interp"])
    plt.show()
    
    
def es_2__newton (f,f_der, p, max_iter,tol):
    
    dx = 1.0
    i = 0
    while abs(dx) > tol and i < max_iter:
        
        dx = -f(p) / f_der(p)
        
        p = p + dx
        i += 1
        
    return (p , dx)
    
    
def es_2__test():
    
    f   = lambda a: sin(1/a) - a
    f_1 = lambda a : -1 - cos(1/a)/a**2
    
    
    x = np.linspace (0.00000001,1.0,1000)
    y = list ( map( lambda a: f(a) , x ) )
    tol = 10e-8
    
    plt.plot(x,y)
    plt.axhline(color="r")
    plt.show()
    
    
    start_p = 0.90184
    max_iter = 300
    sol, dx = es_2__newton(f,f_1,start_p, max_iter,tol)
    
    print ("[!] Soluzione Newton: {} - f(sol): {} - dx > tol : {} ".format(sol,f(sol),abs(dx)>tol))
    
es_1__test()
es_2__test()