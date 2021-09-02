"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

from math import sin,cos,pi,log,exp
import numpy as np
from matplotlib import pyplot as plt
from functools import reduce 


def es_1__inf_norm (M):

    dim         = len(M[0])
    row_sums    = []

    for i in range(dim):
        sum_term = 0.0

        for j in range(dim):
            sum_term += abs(M[i][j])

        row_sums.append(sum_term)

    inf_norm = max(row_sums)

    return inf_norm

def es_1__test():
    points      = {}
    intervals   = list(range(3,11))
    matrices    = {}

    #Build Sequence of Vectors
    for i in intervals:
        x   = np.linspace(1.0,2.0,i)
        points[i] = x

    #Building Matrices
    for i in intervals:
        M = np.zeros(shape=(i,i))
        p = points[i]

        #Fill Matrix
        for j in range(i):
            for k in range(i):
                M[j][k] = p[j]**(i-k)

        matrices[i] = M

    #Compute Cond Number
    cond_numbers = {}
    for i in intervals:
        M       = matrices[i]
        M_INV   = np.linalg.inv(M)

        inf_norm_M      = es_1__inf_norm(M)
        inf_norm_M_inv  = es_1__inf_norm(M_INV)

        cond_numbers[i] = inf_norm_M*inf_norm_M_inv

    
    plt.semilogx(intervals, cond_numbers.values())
    plt.show()


def build_newton_base (x,y):

    dim         = len(x)
    diff_div    = y.copy()

    #Itero sulle differenze divise da calcolare
    for j in range(1,dim):

        #Itero dall'Ultima differenza divisa fino a quella che sto calcolando attualmente
        for i in range(dim-1,j-1,-1):
            diff_div[i] = float(diff_div[i] - diff_div[i-1])/x[i]-x[i-j]

    return diff_div

def eval_newton (x,nodes,base):

    dim     = len(base)
    V       = base[dim-1]

    for i in range(dim-2,-1,-1):
        V *= (x-nodes[i])
        V += base[i]

    return V


def es_2__test():
    f = lambda x:1/1+log(x)
    a = 0.1
    b = 1.0

    intervals = [10,20,40,80]
    points      = {}
    f_points    = {  }

    #Building interpolation points
    for i in intervals:
        points[i] = np.linspace(a,b,i)
        f_points[i] = []
        
        for p in points[i]:
            f_points[i].append(f(p))

    errors = {}
    for i in intervals:
        p           = points[i]
        f_p         = f_points[i]

        base_i      = build_newton_base(p,f_p)
        eval_i      = list( map( lambda x: eval_newton(x,p,base_i) , p  ) )

        errors_i    = list( map ( lambda x: abs(x[0]-x[1]) , list( zip(f_p , eval_i )  ) ) )
        errors[i]   = reduce ( lambda x,y: x+y , errors_i )


    plt.plot(intervals,errors.values())
    plt.xlabel("N Nodi")
    plt.ylabel("Error")
    plt.show()


def es_3__trapezi_comp (f,a,b,N_SUD):

    H = (b-a)/N_SUD

    T = (f(a)+f(b))/2

    for i in range(N_SUD-1):
        n = a + (i+1)*H
        T+= f(n)

    T *= H

    return T

def es_3__test():
    f = lambda x: exp(x**2)
    a = 0.0
    b = 1.0
    N_SUD = [4,8,16,32,64]

    integrals = {}
    errors    = {}

    for i in N_SUD:
        integrals[i] = es_3__trapezi_comp(f,0.0,1.0,i)
        
    for i in range(len(N_SUD)):

        i_integrals             = integrals[ N_SUD[i] ]

        if ( i < (len(N_SUD)-1) ):
            i_2_integral        = integrals[ N_SUD[i+1] ]
        else:
            i_2_integral        = es_3__trapezi_comp(f,0.0,1.0,i*2)

        err_estrapolaz      = abs( (i_integrals - i_2_integral) /3 )                    
        errors[ N_SUD[i] ]  = err_estrapolaz


    div_errors = {}
    for i in range(len(N_SUD) ):
        en  = errors[ N_SUD[i] ]


        if ( i < len(N_SUD)-1):
            e2n = errors[ N_SUD[i+1]]
        else:
            e2n = en 

        div_errors[N_SUD[i]] = en / e2n
  


    log_errors = {}
    for i in N_SUD:
        e = div_errors[i]
        log_errors[i] = log(e)


    plt.plot(N_SUD, div_errors.values() , color="r")
    plt.plot(N_SUD, log_errors.values() , color="g")
    plt.xticks(N_SUD)
    plt.legend(["Errors","Log Errors"])
    plt.show()
         
    



es_1__test()
es_2__test()
es_3__test()