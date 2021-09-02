from gauss_elimination import gauss_naive, lu_factorization, gauss_naive_row_pivoting, row_pivoting, row_pivoting_full
from triang_systems import upper_triangular_solver
import numpy as np

def test_gauss_naive ():
    """
    Test Gauss-Naive
    """
    A = [[8.0, 3.0, 40.0],[16.0, 1.0, 15.0], [24.0, 9.0, 2.0]]
    b = [1.0, 0.0, -3.0]

    M1,b1       = gauss_naive(A,b)
    solution    = upper_triangular_solver(M1,b1)

    A_n         = np.array(A)
    solution_n  = np.array(solution)
    b_n         = np.array(b)

    assert np.array_equal(A_n.dot(solution_n) , b_n)


def test_row_pivoting ():
    """
    Test Row-Pivoting
    """

    A           = [[8.0, 3.0, 40.0],[16.0, 1.0, 15.0], [24.0, 9.0, 2.0]]
    b           = [1.0, 0.0, -3.0]

    M1,b1       = gauss_naive_row_pivoting(A,b)
    solution    = upper_triangular_solver(M1,b1)

    A_n         = np.array(A)
    solution_n  = np.array(solution)
    b_n         = np.array(b)

    assert np.array_equal(A_n.dot(solution_n) , b_n)


def test_row_pivoting_full ():
    """
    Test row-pivoting-full
    """

    A           = [[8.0, 3.0, 40.0],[16.0, 1.0, 15.0], [24.0, 9.0, 2.0]]
    b           = [1.0, 0.0, -3.0]

    M_p,b_p     = row_pivoting_full(A,b)

    M1,b1       = gauss_naive(M_p,b_p)
    solution    = upper_triangular_solver(M1,b1)

    A_n         = np.array(A)
    solution_n  = np.array(solution)
    b_n         = np.array(b)

    assert np.array_equal(A_n.dot(solution_n) , b_n)


def test_lu_fact():
    """
    Test fattorizzazione LU
    """

    A           = [[8.0, 3.0, 40.0],[16.0, 1.0, 15.0], [24.0, 9.0, 2.0]]
    b           = [1.0, 0.0, -3.0]
    A_n         = np.array( A.copy() )

    #Compute LU Factorization
    U,L         = lu_factorization(A)
    U_n         = np.array(U)
    cp_lu       = L.dot(U_n)

    
    assert np.array_equal( A_n, cp_lu)    