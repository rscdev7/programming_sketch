import numpy as np
from matplotlib import pyplot as plt
from math import sin,cos,pi,log,exp
from functools import reduce

def es_1__29_09_2016():

    A           = np.array( [ [6.0,2.0,1.0],[2.0,3.0,1.0] , [1.0,1.0,1.0] ] )
    dim         = len(A[0])

    rays        = [ reduce( lambda x,y: x+y, np.delete(A[i],i) ) for i in range(dim) ]

    real_gen    = lambda c,i,t:c+rays[i]*cos(t)
    img_gen     = lambda c,i,t:c+rays[i]*sin(t)
    ticks       = np.linspace(0.0,2*pi)


    d1_real     = list( map( lambda x: real_gen(6.0,0,x)    ,  ticks ) )
    d1_img      = list( map( lambda x: img_gen(0.0,0,x)     , ticks  ) )

    d2_real     = list( map( lambda x: real_gen(3.0,1,x)    ,  ticks ) )
    d2_img      = list( map( lambda x: img_gen(0.0,1,x)     , ticks  ) )

    d3_real     = list( map( lambda x: real_gen(1.0,2,x)    ,  ticks ) )
    d3_img      = list( map( lambda x: img_gen(0.0,2,x)     , ticks  ) )

    
    plt.fill(d1_real,d1_img,color="r")
    plt.plot([6.0],[0.0],"ow")
    plt.fill(d2_real,d2_img,"blue")
    plt.plot([3.0],[0.0],"ow")
    plt.fill(d3_real,d3_img,"green")
    plt.plot([1.0],[0.0],"ow")
    
    plt.axhline(color="black")
    plt.axvline(color="black")

    plt.xlim([-10,10])
    plt.ylim([-6,6])
    plt.xlabel("Real")
    plt.ylabel("Img")
    plt.show()

    


es_1__29_09_2016()