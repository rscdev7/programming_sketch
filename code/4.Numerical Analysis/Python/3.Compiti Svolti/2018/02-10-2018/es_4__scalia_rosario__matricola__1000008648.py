"""
- Nominativo: Rosario Scalia
- Matricola: 1000008648
"""

import numpy as np
from math import exp,log,cos,pi
from matplotlib import pyplot as plt


int_f           = lambda x: cos((pi/2)*x)
f               = 4/3*int_f(-1/2) - 2/3*int_f(0) + 4/3*int_f(1/2)
exact_integral  = 1.273239544735163

print(f,exact_integral)
print(abs(exact_integral-f))
print(10e-2)