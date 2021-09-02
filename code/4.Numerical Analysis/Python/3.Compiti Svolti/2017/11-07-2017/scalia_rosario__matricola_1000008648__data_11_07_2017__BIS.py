import numpy as np
from math import exp,log
from matplotlib import pyplot as plt
    
def es__3():
    
    f   = lambda a:exp(a)
    g   = lambda a:a+1
    p   = np.linspace(0.0,1.0,1000)
    
    f_p = list( map( lambda a:f(a) , p ) )
    g_p = list( map( lambda a:g(a) , p ) )
    
    
    PHI_1 = lambda a:log(a+1)
    PHI_2 = lambda a:exp(a)-1
    
    phi_1_p = [0.278]
    phi_2_p = [0.278]
        
    
    start_p = 0.015
    for i in range(1000):
        start_p = PHI_1(start_p)
        phi_1_p.append(start_p)
        
    start_p = 0.015
    for i in range(100):
        start_p = PHI_2(start_p)
        phi_2_p.append(start_p)
    
    #f_pp = list(map(lambda a:f(a),phi_1_p))
    f_ppp = list(map(lambda a:f(a),phi_2_p))
    
    plt.plot(p,f_p)
    plt.plot(p,g_p)
    #plt.plot(phi_1_p,f_pp,"or")
    plt.plot(phi_2_p,f_ppp,"ob")
    plt.axhline(color="red")
    plt.legend(["f(x)","g(x)","PHI1","PHI2"])
    plt.show()
    
    
    
    
    
es__3()