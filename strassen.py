# Import Modules #
import numpy as np
import time

# Strassen's Technique #
def strassen_algorithm(x, y):
    if x.size == 1 or y.size == 1:
        return x * y

    n = x.shape[0]

    if n % 2 == 1:
        x = np.pad(x, (0, 1), mode='constant')
        y = np.pad(y, (0, 1), mode='constant')

    m = int(np.ceil(n / 2))
    a = x[: m, : m]
    b = x[: m, m:]
    c = x[m:, : m]
    d = x[m:, m:]
    e = y[: m, : m]
    f = y[: m, m:]
    g = y[m:, : m]
    h = y[m:, m:]
    p1 = strassen_algorithm(a, f - h)
    p2 = strassen_algorithm(a + b, h)
    p3 = strassen_algorithm(c + d, e)
    p4 = strassen_algorithm(d, g - e)
    p5 = strassen_algorithm(a + d, e + h)
    p6 = strassen_algorithm(b - d, g + h)
    p7 = strassen_algorithm(a - c, e + f)
    result = np.zeros((2 * m, 2 * m), dtype=np.int32)
    result[: m, : m] = p5 + p4 - p2 + p6
    result[: m, m:] = p1 + p2
    result[m:, : m] = p3 + p4
    result[m:, m:] = p1 + p5 - p3 - p7

    return result[: n, : n]

# Main Function #
if __name__ == "__main__":
    start = time.time_ns()
    x = np.array([[ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ]])
    y = np.array([[ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ] , [ 1 , 2 , 3 , 4 ]])
    print('4 x 4 matrix', strassen_algorithm(x, y))
    end = time.time_ns()
    print("Execution time :", end - start)
    
    start = time.time_ns()
    x = np.array([[2, 0, 4, 4, 9, 0], [7, 8, 3, 4, 4, 7], [9, 8, 8, 0, 4, 4], [1, 2, 7, 6, 2, 0], [5, 2, 7, 5, 6, 8], [3, 5, 8, 1,7, 4]])
    y = np.array([[5, 2, 5, 4, 0, 7], [1, 1, 3, 6, 3, 4], [8, 7, 2, 3, 7, 3], [3, 8, 7, 0, 0, 5], [3, 4, 8, 3, 4, 1], [6, 1, 6, 4, 8, 0]])
    print('6 x 6 matrix', strassen_algorithm(x, y))
    end = time.time_ns()
    print("Execution time :", end - start)
    
    start = time.time_ns()
    x = np.array([[4, 3, 4, 7, 3, 5, 7, 7], [5, 5, 5, 7, 6, 4, 6, 3], [6, 0, 5, 5, 3, 8, 7, 9], [8, 7, 4, 0, 5, 0, 0, 9], [7, 7, 9, 9, 9, 0, 3, 6], [5, 5, 4, 1, 6, 7, 1, 6], [4, 0, 5, 0, 3, 0, 1, 7], [9, 3, 7, 3, 9, 0, 0, 2]])
    y = np.array([[9, 2, 3, 0, 0, 6, 7, 1], [2, 9, 7, 6, 6, 5, 3, 3], [4, 9, 7, 5, 6, 3, 8, 7], [6, 9, 4, 4, 2, 2, 7, 3], [5, 0, 5, 6, 9, 4, 1, 5], [3, 1, 1, 0, 5, 1, 3, 8], [3, 8, 3, 2, 3, 9, 2, 9], [1, 5, 0, 0, 1, 9, 2, 5]])
    print('8 x 8 matrix', strassen_algorithm(x, y))
    end = time.time_ns()
    print("Execution time :", end - start)
