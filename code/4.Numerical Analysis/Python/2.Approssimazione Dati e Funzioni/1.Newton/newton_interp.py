def compute_newton_base(x,y):

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
    return f

def newton_eval_ruffini(x,F,X):
    n = len(F)-1
    s = F[n]

    #Itero sulla lunghezza dei nodi al contrario
    for j in range(n-1,-1,-1):
        s *= (x-X[j])
        s += F[j]
    return s