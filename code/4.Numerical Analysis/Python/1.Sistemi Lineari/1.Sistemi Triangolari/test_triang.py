import numpy as np
from triang_systems import upper_triangular_solver


def test_upper_triangular_systems():
    """
    Funzione di test per i Sistemi Triangolari Superiori
    """
    A = [ [24.0, 9.0, 2.0], [0, -5., 13.666666666] , [0.0, 0.0, 39.33333333333] ]
    b = [ -3.0, 2.0, 2.0 ] 

    solution    = upper_triangular_solver(A,b)

    A_n         = np.array(A)
    solution_n  = np.array(solution)
    b_n         = np.array(b)

    assert np.array_equal(A_n.dot(solution_n) , b_n)