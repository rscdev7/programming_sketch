"""
- Nome: Rosario
- Cognome: Scalia
- Matricola: 1000008648
"""
import numpy as np
import math
from functools import reduce
from gauss_elimination import *
from triang_systems import *
from matplotlib import pyplot as plt
from choleski import *
from newton_interp import *

def es_1__build_lx_system(x,y):

    exp_x   = np.power(x,2)
    a_00    = reduce (lambda a,b: a+b,exp_x)
    a_01    = reduce (lambda a,b: a+b,x)
    a_10 = a_01
    a_11 = len(x)

    A    = np.array ( [ [a_00 , a_01] , [a_10,a_11] ] )

    prod_x_y    = list(map( lambda a: a[0]*a[1] , list(zip(y,x)) ) )
    b_0  = reduce (lambda a,b: a+b , prod_x_y )
    b_1  = reduce (lambda a,b: a+b,y)
    b    = np.array( [b_0 , b_1] )

    return A,b

def es_2__build_px_system(x,y):

    exp_x_4 = np.power(x,4)
    a_00    = reduce (lambda x,y: x+y,exp_x_4)
    
    exp_x_3 = np.power(x,3)
    a_01    = reduce (lambda x,y: x+y,exp_x_3)

    exp_x_2 = np.power(x,2)
    a_02    = reduce (lambda x,y: x+y,exp_x_2)

    a_10    = a_01
    a_11    = a_02
    a_12    = reduce (lambda x,y: x+y,x)

    a_20    = a_02
    a_21    = a_12
    a_22    = len(x)

    A           = np.array( [ [a_00 , a_01 , a_02] , [a_10, a_11, a_12] , [a_20, a_21, a_22] ] )

    prod_y_exp_x_2    = list(map( lambda a: a[0]*a[1] , list(zip(y,exp_x_2)) ) )
    b_0             = reduce (lambda a,b: a+b ,prod_y_exp_x_2)

    prod_y_x    = list(map( lambda a: a[0]*a[1] , list(zip(y,x)) ) )
    b_1         = reduce (lambda a,b: a+b ,prod_y_x)

    b_2         = reduce (lambda x,y: x+y,y)

    b           = np.array([b_0,b_1,b_2])

    return A,b
 
    


def es_1__test():
    x           = np.array ( [-1.2,-1.0,-0.5,0.0,0.5,1.0,1.1] )
    y           = np.array( [0.1,0.4,0.8,1.0,1.2,1.35,1.4] )

    #Parametri Polinomio 1
    A,b         = es_1__build_lx_system(x,y)
    A1,b1       = gauss_naive(A,b)
    sol         = upper_triangular_solver(A1,b1)
    pre_interp  = list( map( lambda x: (x,sol)   ,x ) )
    p_interp    = list( map ( lambda x: x[0]*x[1][0] + x[1][1] , pre_interp ) )

    #Derivazione Matriciale
    PHI_1       = np.zeros(shape=(7,2))
    for i in range(len(x)):
        PHI_1[i][0] = 1
        PHI_1[i][1] = x[i]


    MTR_SYS    = PHI_1.T.dot(PHI_1)
    NOTE_TERM  = PHI_1.T.dot(y)



    #Parametri Polinomio 2
    A_2,b_2         = es_2__build_px_system(x,y)
    res             = check_choleski(A_2)

    if (res ==True):
        R               = choleski_fat(A_2)
        R_T             = R.T

        ps_sol          = lower_triangular_solver(R_T,b_2)
        sol2            = upper_triangular_solver(R,ps_sol)

        pre_interp      = list( map( lambda x: (x,sol2)   ,x ) )
        p_interp2       = list( map ( lambda x: x[1][0]*x[0]**2 + x[1][1]*x[0] + x[1][2] , pre_interp ) )

    #Derivazione Matriciale
    PHI_2           = np.zeros(shape=(7,3))
    for i in range(len(x)):
        PHI_2[i][0] = x[i]**2
        PHI_2[i][1] = x[i]
        PHI_2[i][2] = 1

    MTR_SYS         = PHI_2.T.dot(PHI_2)
    NOTE_TERM       = PHI_2.T.dot(y)

    
    #Plot
    plt.plot(x,y,"or")
    plt.plot(x,p_interp)
    plt.plot(x,p_interp2)
    plt.legend(["points","interp_1_grad","interp_grad_2"])
    plt.show()

    return True

def es_2__test():
    x = np.array([0.0,0.4,0.6,1.0])
    f = lambda x: x* math.exp(-x)

    f_x = list(map(lambda a:f(a),x))

    base = compute_newton_base(x,f_x)
    print (base)

    ev      = newton_eval_ruffini(0.8,base,x)
    ev_gt   = f(0.8)

    print (ev)
    print(ev_gt)

def es_3__newton(f,f_der,a,b,tol):

    dx = 1.0
    x  = a

    while (abs(dx) > tol):
        dx = - f(x)/f_der(x)
        x = x + dx

    print ("Soluz: {} Valore f: {} ".format(x,f(x)))
    

def es_3__test():
    diff_fun = lambda x:math.sin(x)**2 - math.exp(-x)
    diff_der = lambda x: math.sin(2*x) + math.exp(-x)

    points   = np.linspace(0.0,2*math.pi,1000000)
    f_p      = list(map( lambda x:diff_fun(x) ,points ))

    plt.plot(points,f_p)
    plt.axhline(y=0,color="r")
    plt.show()

    es_3__newton (diff_fun , diff_der,6.01,2*math.pi,10e-6)


def es_4__trapezi_composita_estrapolaz(f,a,b, NP , NS):

    #Trapezi
    T = (f(a)+f(b))/2
    h = (b-a)/NP

    for i in range(NP-1):
        current_node = a + i*h
        T += f(current_node)

    T *= h
    

    #Simpson
    H = (b-a)/NS
    S = f(a) + f(b)

    for i in range(NS-1):
        current_node = a+i*H
        S += 2.0*f(current_node)

    for i in range(NS):
        current_node = a+(i+0.5)*H
        S += f(current_node)*4.0

    S *= H/6

    diff = abs (S-T)

    print ("Approx Integrale con Estrapolazione- Trapezi: {} - Simpson: {} - Diff: {} ".format(T,S,diff))



def es_4__test():
    f   = lambda x: math.exp(-x)
    a   = 0.0
    b   = 1.0
    NP  = 10000000
    NS  = 100000

    es_4__trapezi_composita_estrapolaz(f,a,b,NP,NS)
    



es_1__test()
es_2__test()
es_3__test()
es_4__test()