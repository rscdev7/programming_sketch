"""
- Nome: Rosario
- Cognome: Scalia
- Matricola: 1000008648
"""

import math
import numpy as np
from matplotlib import pyplot as plt

def es_1__jacobi(A,b,x_0 , max_iter):

    dim         = len(b)
    sol_old     = x_0
    sol_new     = x_0

    for i in range(max_iter):

        for j in range(dim):

            sum_term_1 = 0.0

            for k in range(j):
                sum_term_1 += A[j][k] * sol_old[k]

            sum_term_2      = 0.0

            for k in range(j+1,dim):
                sum_term_2 += A[j][k] * sol_old[k]

            sol_new[j]  = (b[j] - sum_term_1 - sum_term_2 ) / A[j][j]


        sol_old     = sol_new.copy()

        
        residual = 0.0

        result      = A.dot(sol_new)
        
        for z in range(dim):
            residual += (b[z] - result[z] )**2

        residual = math.sqrt(residual)

        print ("[!] Iterazione: {} - Termine Noto: {} - Soluzione Trovata: {} - CP: {} - Residuo: {}".format(i,b,sol_new,result,residual))


def es_1__gauss_heidel (A,b,x_o,max_iter):

    dim  = len(b)
    sol_new  = x_o
    sol_old  = x_o

    #Itero sulle Iterazioni Masssime
    for i in range(max_iter):

        #Itero sulle Incognite da trovare
        for j in range(dim):

            sum_term_1 = 0.0
            sum_term_2 = 0.0

            #Moltiplitoc Matrice e vettore soluzione dall'incognita da trovare + 1 fino alle fine
            for k in range(j+1,dim):
                sum_term_1 += A[j][k] * sol_old[k]

            #Moltiplitoc Matrice e vettore soluzione da 0 fino all'incognita da trovare - 1
            for k in range(j):
                sum_term_2 += A[j][k] * sol_new[k]

            sol_new[j] = (b[j] - sum_term_1 - sum_term_2) / A[j][j]

        sol_old =    sol_new
        current_out = A.dot(sol_new)

        residual    = 0.0

        #Calcolo Norma 2 del residuo
        for z in range(dim):
            residual += (b[z] - current_out[z])**2

        residual = math.sqrt(residual)

        #Print Risultati
        print("[!] Iterazione: {} - Soluzione: {} - Output: {} - Residuo: {} ".format( i , sol_new , current_out , residual ))
 


def es_1__test():
    A               = np.array( [ [4.0,3.0,-1.0] , [-2.0,-4.0,5.0] , [1.0, 2.0, 6.0]  ] )
    x_0             = np.array( [0.0,0.0,0.0] )
    b               = np.array( [1.0,2.0,3.0] )


    es_1__jacobi(A,b,x_0,10)

    es_1__gauss_heidel(A,b,x_0,10)


def es_2__newton_base(p,f):

    dim      = len(p)
    diff_div = f.copy()

    #Itero sulla Differenza Divisa da Calcolare
    for i in range(1,dim):

        for j in range(dim-1,i-1,-1):
            diff_div[j] = float(diff_div[j] - diff_div[j-1])/float( p[j] - p[j-i] )

    return diff_div


def es_2__newton_eval (x,nodes, base):

    dim   = len(nodes)
    value = base[dim - 1]

    for i in range(dim-2,-1,-1):
        value *= (x - nodes[i])
        value += base[i]

    return value


def es_2__test():

    points      = np.array( [0.0,1.0,2.0,3.0] )
    points_cp    = np.array( [2.0, 0.0, 1.0, 6.0] )


    base        = es_2__newton_base (points, points_cp)


    res         = []

    for i in range(len(points)):
        res.append( es_2__newton_eval(points[i] ,points , base ) )

    print (points_cp)
    print(res)

    plt.plot(points,points_cp,"or")
    plt.plot(points,res,"b")

    plt.legend(["Punti Tabulati","Punti Interpolati"])
    plt.xlim([0.0,3.0])
    plt.show()


def es__3_newton (init_p, f, f_der):
    tol     =   10e-5
    
    sol     = init_p
    sol_old = 0.0

    to_iter = True
    iter_count = 0
    
    while (to_iter == True):
        
        if (iter_count == 0 or iter_count%2==0):
            sol =  sol - f(sol)/f_der(sol)
            sol_old = sol
        else:
            sol =  sol - f(sol)/f_der(sol)

            if (abs(sol - sol_old) <= 10e-5):
                to_iter = False

        iter_count +=1


    return (iter_count, sol)


def es_3_test():
    fun         = lambda x: math.log(1/x) - math.exp(-x)*math.cos(x)
    fun_der     = lambda x: -1/x + math.exp(-x)*math.cos(x) + math.exp(-x)*math.sin(x)
    interval = [0.5,1.0]

    fun_a = fun(0.5)
    fun_b = fun(1.0)

    if (fun_a < 0 and fun_b < 0 or fun_b > 0 and f_a > 0):
        print ("Impossibile applicare Newton")
    else:
        print ("Newton OK - f(a): {} - f(b): {} ".format(fun_a,fun_b))

        points = np.linspace(0.5,1.0,1000)
        
        f_res  = np.array( list( map( lambda x: fun(x),points ) ) )

        plt.plot(points,f_res)
        plt.axhline(0.0,0.0)
        plt.show()

    res = es__3_newton(0.5,fun,fun_der)

    print (res[0],fun(res[1]))


def es_4__trapezi_comp(f,exact_integral, inf,sup, tol):

    #Itero sul Numero di Intervalli
    for N in range(1,50):

        h       = (sup - inf)/N
        nodes   = [0.0]*(N+1)

        for i in range(N+1):
            nodes[i]    = inf+ i*h

       
        approx_integral = 0.0
        for z in range(N):
            a  = nodes[z]
            b  = nodes[z+1]

            approx_integral += ((f(a)+f(b))/2)*h

        if (abs(approx_integral - exact_integral) < tol):
            print ("[!] Soluzione Integrale Approx: {} - Soluzione Esatta: {} - N Intervalli: {} ".format(approx_integral,exact_integral,N))
            break

    
def es_4__test():

    f                   =   lambda x:x**2*math.sin(x)
    exact_integral      = -39.43

    es_4__trapezi_comp(f,exact_integral,0.0,6.28,10e-3)


es_1__test()
es_2__test()
es_3_test()
es_4__test()