"""
- Nome           :               Rosario
- Cognome        :               Scalia
- Matricola      :               1000008648
- Data           :               15-06-2021

"""

import numpy as np
from matplotlib import pyplot as plt
import math


def es_1__model(t,g):
    return 1/2 * g * (t**2)

def es_1__transform (x):
    return 1/2*x**2

def es_1__test():
    
    print ("\n_______________ESERCIZIO 1_______________\n")
    #Dati Iniziali Problema
    t               = np.array (     [0.2, 0.4, 0.6, 0.8, 1.0                ]   )
    d               = np.array (     [0.1960, 0.7850, 1.7665, 3.1405, 4.907  ]   )


    #Applicazione Minimi Quadrati
    PHI         = es_1__transform(t)
    PHI_T__PHI  = PHI.T.dot(PHI)
    note_term   = PHI.T.dot(d)

    solution    = note_term / PHI_T__PHI


    #Stampo Soluzione
    print ("[!] Soluzione Trovata: {} ".format(solution))


    #Applico Modello ai Dati
    approx_d    = []
    for data_point in t:
        approx_d.append( es_1__model( data_point, solution) )


    #Grafico Fitting
    plt.title("Plot Fitting Modello")
    plt.plot(t,d,"o")
    plt.plot(t,approx_d,"r")

    plt.xlim([0.1,1.1])
    plt.ylim([0.0000,5.0000])

    plt.xlabel("Tempo")
    plt.ylabel("Distanza")

    plt.legend(['Dati','Modello'])
    plt.show()

    print ("\n-------------------------------------------\n")


def es_2__lagrange_eval(x,y,nodes):
    l                   = np.array( [1.0]*len(nodes) )
    normal_idx_range    = set( range( len(nodes) ) )


    #Determinazione Base Polinomio Lagrange
    for i in range(len(nodes)):
        
        current_idx         = set( [i] )
        right_idx_range     = normal_idx_range.difference(current_idx)

        for j in right_idx_range:
            l[i] *= ( (x-nodes[j]) / (nodes[i]-nodes[j]) )


    #Valutazione Polinomio
    output = 0.0
    for i in range(len(nodes)):
        output += y[i] * l[i]

    return output
    
def es_2__compute_newton_base(x,y):

    #Numero di Nodi
    n = len(x)

    #Vettore Differenze Divise, lungo quanto il numero di Nodi
    f = [0]*n

    #Inizializzo il vettore delle differenze divise coi valori della Funzione nei Nodi
    for k in range(0,n):
        f[k]=y[k]
    
    #Itero sulla Differenza Divisa da Calcolare [itero sull'ordine]
    for j in range(1,n):

        #Itero dall'ultima differenza Divisa fino alla Differenza Divisa da Calcolare
        for i in range(n-1, j-1, -1):
            f[i] = float(f[i]-f[i-1])/float(x[i]-x[i-j])
            #print(i,i-1,f[i],f[i-1],x[i]-x[i-j])
    return f

def es_2__newton_eval_ruffini(x,F,X):
    n = len(F)-1
    s = F[n]

    #Itero sulla lunghezza dei nodi al contrario
    for j in range(n-1,-1,-1):
        s *= (x-X[j])
        s += F[j]
    return s
            
def es_2__test():
    print ("\n_______________ESERCIZIO 2_______________\n")

    nodes               = np.array( [ 0, 1, 2, 3 ] )
    computed_points     = np.array( [ 0 , 2, -1, 0] )


    #Test Polinomio Lagrange
    output_lagrange         = np.array([0.0] * 4)
    for i in range(4):
        output_lagrange[i]  = es_2__lagrange_eval(nodes[i],computed_points,nodes)
    print ("[!] Original Out: {}\n[!] LAGRANGE Out: {} ".format(computed_points,output_lagrange))


    #Test Polinomio Newton
    ris                     = es_2__compute_newton_base(nodes,computed_points)

    output_newton           = np.array([0.0] * 4)
    for i in range(4):
        #output_newton[i] = es_2__compute_newton_eval(nodes[i],nodes , ris)
        output_newton[i] = es_2__newton_eval_ruffini(nodes[i],ris,nodes)
    print ("\n[!] Original Out: {}\n[!] NEWTON Out: {} ".format(computed_points,output_newton))

    print ("\n-------------------------------------------\n")


def es_3_newton (init_p, f, f_der):
    tol     =   10e-5
    sol     = 0.0
    to_iter = True
    iter_count = 0
    x = init_p

    while (to_iter == True):
        
        x =  x - f(x)/f_der(x)
        out_fun = f(x)
        iter_count +=1

        if (abs(out_fun) <= 10e-5):
            to_iter = False

    return (iter_count, x)

def es_3__test():
    print ("\n_______________ESERCIZIO 3_______________\n")
    points  = np.linspace(-1.5,1.5,1000)

    #Compute Fun at points
    fun_out =   []
    for p in points:
        compute = math.tan(p) - 2*p
        fun_out.append( compute )

    function    = lambda x: math.tan(x) - 2*x
    der_fun     = lambda x: 1/math.cos(x)**2 - 2

    plt.title("Function View")
    plt.plot(points,fun_out)
    plt.axhline(y=0, c="black", label="y=0")
    plt.show()

    result = es_3_newton(1.3,function,der_fun)

    print ("[!] Soluzione Newton: {} - Valore Funzione: {} - Iterazioni: {} ".format(result[1] , function(result[1]) , result[0] ))

    plt.title("Function View")
    plt.plot(points,fun_out)
    plt.axhline(y=0, c="black", label="y=0")
    plt.plot(result[1],function(result[1]),"or")
    plt.show()
    print ("\n-------------------------------------------\n")


def es_4__trapezi_compositi(f,a,b,tol):

    for N in range(1,30):
        width_interval                  = (b-a)/N
        intervals                       = [0.0]*(N+1)
        integrale_esatto                = 0.22324
        valore_numerico_integrale       = 0.0

        #Costruisco la suddivisione dell'intervallo originale in N intervalli
        for i in range(N+1):
            intervals[i] =  a+i*width_interval 

        #Applico formula trapezi composita
        for i in range(N):
            inf   = intervals[i]
            sup   = intervals[i+1]

            valore_numerico_integrale = valore_numerico_integrale + width_interval* ( ( f(inf)+f(sup) ) / 2)


        if (abs(valore_numerico_integrale - integrale_esatto) <  tol):
            print("[!] Numero Suddivisioni: {} - Soluzione Approssimata Integrale: {} ".format(N,valore_numerico_integrale))
            break

    return True


def es_4__test():
    print("\n__________ESERCIZIO 4_______\n")

    function    = lambda x:x**2 * math.sin(x)
    tol         = 10e-3

    es_4__trapezi_compositi(function,0,1,tol)

    print("\n--------------------------------\n")



es_1__test()
es_2__test()
es_3__test()
es_4__test()