import numpy as np
from matplotlib import pyplot as plt


def gauss_elim (M,b):
    
    dim = len(b)
    
    for i in range(dim):
        
        for j in range(i+1,dim):
            
            m__ji = M[j][i]/M[i][i]
            M[j][i] = 0.0
            
            for k in range(j+1,dim):
                M[j][k] = M[j][k] - m__ji*M[i][k]
                
            b[j] = b[j] - b[i]
            
    return M,b

def upper_triangular_solver (A,b):
    
    dim = len(b)
    sol = np.zeros(shape=(dim))
    
    for i in range(dim-1,-1,-1):
        
        if (i == (dim-1)):
            sol[i] = b[i]/A[i][i]
        else:
            sum_term = 0.0
            
            for k in range(dim-1,i,-1):
                sum_term += A[i][k]*sol[k]
                
            sol[i] = (b[i] - sum_term)/A[i][i]
            
    return sol

def pol_eval(x,coeff):
    return coeff[0] + coeff[1]*x + coeff[2]*x**2 + coeff[3]*x**3
    
    
def es_1__test():
    x = np.array( [-2,-1,1,3] )
    y = np.array( [4,3,2,1]   )
    
    M = np.array( [
                    [1.0,-2,4,-8],
                    [1.0,-1,1,-1],
                    [1.0,1.0,1.0,1.0],
                    [1.0,3,9,27]
                    ] )
    
    A,b = gauss_elim(M,y)
    q = upper_triangular_solver(A,b)
    print (M.dot(q),y)
    
    x1 = M[0].dot(q)
    x2 = M[1].dot(q)
    x3 = M[2].dot(q)
    x4 = M[3].dot(q)
    po_p = [x1,x2,x3,x4]
    
    plt.plot(x,y,"or")
    plt.plot(x,po_p,"b")
    plt.show()
    
    
es_1__test()
    