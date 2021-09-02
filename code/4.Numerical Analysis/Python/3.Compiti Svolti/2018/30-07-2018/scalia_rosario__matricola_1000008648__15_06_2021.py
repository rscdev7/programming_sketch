"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from math import cos,sin,pi,log,exp,sqrt
from matplotlib import pyplot as plt
from functools import reduce

def es_1__build_system_objects(x,y):
    
    M = np.zeros(shape=(3,3))
    b = np.zeros(shape=(3))
    
    n = len(x)
    
    
    x_cos       = list( map ( lambda a: cos(a),x ) )
    sum_cos     = reduce (lambda a,b: a+b , x_cos )
    
    x_sin       = list( map ( lambda a: sin(a),x ) )
    sum_sin     = reduce (lambda a,b: a+b , x_sin )
    
    x_cos_2     = np.power(x_cos,2)
    sum_cos_2   = reduce (lambda a,b: a+b , x_cos_2 )
    
    x_sin_cos   = list( map ( lambda a: cos(a)*sin(a),x ) )
    sum_sin_cos = reduce (lambda a,b: a+b , x_sin_cos )
    
    x_sin_2     = np.power(x_sin,2)
    sum_sin_2   = reduce (lambda a,b: a+b , x_sin_2 )
    
    M[0][0]     = n
    M[0][1]     = sum_cos
    M[0][2]     = sum_sin
    
    M[1][0]     = sum_cos
    M[1][1]     = sum_cos_2
    M[1][2]     = sum_sin_cos
    
    M[2][0]     = sum_sin
    M[2][1]     = sum_sin_cos
    M[2][2]     = sum_sin_2
    
    
    y_sum       = reduce (lambda a,b: a+b , y )
    
    y_cos       = list( map ( lambda a: a[0]*cos(a[1]) , list( zip(y,x) ) ) )
    y_cos_sum   = reduce (lambda a,b: a+b , y_cos )
    
    y_sin       = list( map ( lambda a: a[0]*sin(a[1]) , list( zip(y,x) ) ) )
    y_sin_sum   = reduce (lambda a,b: a+b , y_sin )
    
    b[0]        = y_sum
    b[1]        = y_cos_sum
    b[2]        = y_sin_sum
    
    return (M,b)

def es_1__gauss_naive (M,b):
    
    dim = len(b)
    
    
    for i in range(dim):
        
        for j in range(i+1,dim):
            
            m__j_i  = M[j][i]/M[i][i]
            
            M[j][i] = 0.0
            
            for k in range(j+1,dim):
                M[j][k] = M[j][k] - m__j_i*M[i][k]
                
            b[j]    = b[j] - m__j_i*b[i]
            
            
    return M,b

def es_1__upper_triangular_solver (M,b):
    
    dim = len(b)
    sol = np.zeros(shape=(3))
    
    #Itero sulle incognite da trovare al contrario
    for i in range(dim-1,-1,-1):
        
        if (i == dim-1):
            sol[i] = b[i]/M[i][i]
            
        else:
            
            sum_term = 0.0
            
            for j in range(dim-1,i,-1):
                sum_term += M[i][j]*sol[j]
                
            sol[i] = (b[i] -sum_term)/M[i][i]
            
    return sol
            
            
        
    

def es_1__test():
    
    print ("\n____________________________________________ESERCIZIO 1___________________________________________")
    x = np.array( [0.0, 1.2566, 2.5133, 3.7699 , 5.0265] )
    y = np.array( [0.8156, 1.0748 , 0.7298, 0.3317 , 0.3555] )

    M,b     = es_1__build_system_objects(x,y)
    
    M1,b1   = es_1__gauss_naive(M,b)
    
    params  = es_1__upper_triangular_solver(M1, b1)
    
    print("[!] Test M1*params=b1 \n-> Valore Prodotto: {} \n-> Termine Noto: {}".format(M1.dot(params) , b1 ))
    
    points_and_params = list(map (lambda a: (a,params) ,x))
    least_square_eval = list( map( lambda a: a[1][0] + a[1][1]*cos(a[0]) + a[1][2]*sin(a[0]) , points_and_params ) )
    
    
    plt.plot(x,y,"or")
    plt.plot(x,least_square_eval)
    plt.legend(["Points","LS"])
    plt.title ("Grafico punti VS interpolaz_minimi_quadrati")
    plt.show()
    
def es_2__newton(aux_f,aux_f1,start_p,max_iter,tol):
    
    dx  = 1.0
    i   = 0
    p   = start_p
    
    while (abs(dx) > tol and i < max_iter):
        dx = -aux_f(p)/aux_f1(p)
        p = p + dx
        i+=1
        
    assert dx < tol
    
    return p
        
    
def es_2__test():
    print ("\n____________________________________________ESERCIZIO 2___________________________________________")
    f = lambda x: exp( -10*( sin(x)**2 ) )
    g = lambda x: exp ( -((x-pi)/2)**2 )
    
    points = np.linspace(0.0,pi,1000)
    f_p    = list( map( lambda x:f(x),points ) )
    g_p    = list( map( lambda x:g(x),points ) )
    
    
    plt.plot(points,f_p)
    plt.plot(points,g_p)
    plt.legend(["f(x)","g(x)"])
    plt.title ("Grafico f(x) e g(x)")
    plt.show()
    
    
    #Funzione dove trovare gli Zeri 
    aux_f   = lambda x: exp( -10*( sin(x)**2 ) ) - exp ( -((x-pi)/2)**2 )
    aux_f1  = lambda x:20*exp(-10*sin(x)**2)*sin(x)*cos(x)
    max_iter = 1000
    
    aux_p  = list( map( lambda x:aux_f(x),points ) )
    plt.plot(points,aux_p)
    
    a       = 0.44114
    b       = 0.46
    assert (aux_f(a)*aux_f(b)<0.0)
    
    plt.plot([a,b],[aux_f(a),aux_f(b)],"og")
    plt.axhline(y=0,color="r")
    plt.legend(["aux_f(x)"])
    plt.title ("Grafico aux_f(x) = f(x)-g(x)")
    plt.show()
    
    
    #Ricerca Primo Zero    
    start_p = a
    tol     = 10e-6
    
    s1      = es_2__newton(aux_f,aux_f1,start_p,max_iter,tol)
    print ("[!] Primo Zero: [a,b] = [{},{}] - x={} - f(x)={}".format(a,b,s1,aux_f(s1)))
    print ("[!] Secondo Zero: [a,b] = [{},{}] - x={} - f(x)={}".format(0.0,pi,pi,aux_f(pi)))
    
    
def es_3__trapezi(f,NT,a,b):
    
    h = (b-a)/NT
    
    T = (f(a)+f(b))/2
    
    for i in range(NT-1):
        p = a + (i+1)*h
        T+= f(p)
        
    T *= h
    
    return T
    
def es_3__test():
    print ("\n____________________________________________ESERCIZIO 3___________________________________________")
    f  = lambda x: exp(-10*sin(x)**2)
    f_2 = lambda x: 400*exp(-10*sin(x)**2)*sin(x)**2*cos(x)**2 + 20*exp(-10*sin(x)**2)*sin(x)**2 - 20*exp(-10*sin(x)**2)*cos(x)**2
    tol = 10e-6
    
    
    p = np.linspace(0.0,pi,1000)
    f_2_p = list ( map(lambda x: f_2(x) , p ) )
    

    plt.plot(p,f_2_p)
    plt.plot ([2.76], [f_2(2.76)] , "or")
    plt.legend(["f^2(x)","max f^2(x)"])
    plt.plot("Grafico e(-10*sin(x)**2)")
    plt.show()
    
    
    denominator = 10e-6 * 12
    numerator   = pi * 2.76
    N_T = int(sqrt(numerator/denominator)+1)
    
    
    print ("[!] Numero Minimo intervalli per soddisfare la tolleranza: {}".format(N_T))
    TN  = es_3__trapezi(f,N_T,0.0,pi)
    T2N = es_3__trapezi(f,N_T*2,0.0,pi)
    
    diff = abs( (T2N-TN)/3 ) < tol
    print("[!] L'errore di Approssimazione dell'integrale è inferiore alla Soglia: {} \n-> Errore: {} \n-> Soglia: {}".format(diff,abs( (T2N-TN)/3 ),tol))   
    
    
es_1__test()
es_2__test()
es_3__test()
