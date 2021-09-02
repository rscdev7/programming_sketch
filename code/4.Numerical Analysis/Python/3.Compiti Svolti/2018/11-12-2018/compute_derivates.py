from sympy import *

x       = symbols("x")
init_printing(use_unicode=True)
f       = sin(x*pi) - 2*cos(pi*x) 

diff(f,x)
der = []
for i in range(1,5):
    f = diff(f,x)
    der.append(f)

f2,f4     = der[1],der[3]
print ("F2: {} \n\nF4: {} \n\n".format(f2,f4))


