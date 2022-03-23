// Main Class //
public class Main
{
         public int[][] multiply(int[][] A, int[][] B)
    {
        int n = A.length;
        int[][] R = new int[n][n];

        if (n == 1)
            R[0][0] = A[0][0] * B[0][0];
        else {
            // Strassen's Technique //
            int[][] A11 = new int[n / 2][n / 2];
            int[][] A12 = new int[n / 2][n / 2];
            int[][] A21 = new int[n / 2][n / 2];
            int[][] A22 = new int[n / 2][n / 2];
            int[][] B11 = new int[n / 2][n / 2];
            int[][] B12 = new int[n / 2][n / 2];
            int[][] B21 = new int[n / 2][n / 2];
            int[][] B22 = new int[n / 2][n / 2];

            split(A, A11, 0, 0);
            split(A, A12, 0, n / 2);
            split(A, A21, n / 2, 0);
            split(A, A22, n / 2, n / 2);
            
            split(B, B11, 0, 0);
            split(B, B12, 0, n / 2);
            split(B, B21, n / 2, 0);
            split(B, B22, n / 2, n / 2);
            
            int[][] M1 = multiply(add(A11, A22), add(B11, B22));
            int[][] M2 = multiply(add(A21, A22), B11);
            int[][] M3 = multiply(A11, sub(B12, B22));
            int[][] M4 = multiply(A22, sub(B21, B11));
            int[][] M5 = multiply(add(A11, A12), B22);
            int[][] M6 = multiply(sub(A21, A11), add(B11, B12));
            int[][] M7 = multiply(sub(A12, A22), add(B21, B22));
            
            int[][] C11 = add(sub(add(M1, M4), M5), M7);
            int[][] C12 = add(M3, M5);
            int[][] C21 = add(M2, M4);
            int[][] C22 = add(sub(add(M1, M3), M2), M6);

            join(C11, R, 0, 0);
            join(C12, R, 0, n / 2);
            join(C21, R, n / 2, 0);
            join(C22, R, n / 2, n / 2);
        }
        return R;
    }
    
    // Matrix Subtraction //
    public int[][] sub(int[][] A, int[][] B)
    {
        int n = A.length;
        int[][] C = new int[n][n];
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                C[i][j] = A[i][j] - B[i][j];
        return C;
    }

    // Matrix Addition //
    public int[][] add(int[][] A, int[][] B)
    {
        int n = A.length;
        int[][] C = new int[n][n];
        
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                C[i][j] = A[i][j] + B[i][j];
        return C;
    }
    
    public void split(int[][] P, int[][] C, int iB, int jB)
    {
        for (int i1 = 0, i2 = iB; i1 < C.length; i1++, i2++)
            for (int j1 = 0, j2 = jB; j1 < C.length; j1++, j2++)
                C[i1][j1] = P[i2][j2];
    }

    public void join(int[][] C, int[][] P, int iB, int jB)
    {
        for (int i1 = 0, i2 = iB; i1 < C.length; i1++, i2++)
            for (int j1 = 0, j2 = jB; j1 < C.length; j1++, j2++)
                P[i2][j2] = C[i1][j1];
    }
    
    // Main Function //
	public static void main(String[] args) {
		int N = 4;
		
		Main s = new Main();

        // Execution Time 4x4 matrix //
        long start = System.nanoTime();
        // Matrix A //
        int[][] A = { { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 } };
        // Matrix B //
        int[][] B = { { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 } };
        // Matrix C //
        int[][] C = s.multiply(A, B);
        long end = System.nanoTime();
        System.out.println("\n4 x 4 matrix : ");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                System.out.print(C[i][j] + " ");
            System.out.println();
        }
        long execution = end - start;
        System.out.println("Execution time: " + execution + " nanoseconds");
        
        // Execution Time 6x6 matrix//
        start = System.nanoTime();
        // Matrix A //
        int[][] AA = { { 2, 0, 4, 4, 9, 0 },
                    { 7, 8, 3, 4, 4, 7 },
                    { 9, 8, 8, 0, 4, 4 },
                    { 1, 2, 7, 6, 2, 0 },
                    { 5, 2, 7, 5, 6, 8 },
                    { 3, 5, 8, 1, 7, 4 } };
        // Matrix B //
        int[][] BB = { { 5, 2, 5, 4, 0, 7 },
                    { 1, 1, 3, 6, 3, 4 },
                    { 8, 7, 2, 3, 7, 3 },
                    { 3, 8, 7, 0, 0, 5 }, 
                    { 3, 4, 8, 3, 4, 1 },
                    { 6, 1, 6, 4, 8, 0 } };
        // Matrix C //
        int[][] CC = s.multiply(AA, BB);
        end = System.nanoTime();
        System.out.println("\n6 x 6 matrix : ");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                System.out.print(CC[i][j] + " ");
            System.out.println();
        }
        execution = end - start;
        System.out.println("Execution time: " + execution + " nanoseconds");
        
        // Execution Time 8x8 matrix//
        start = System.nanoTime();
        // Matrix A //
        int[][] AAA = { { 4, 3, 4, 7, 3, 5, 7, 7 },
                    { 5, 5, 5, 7, 6, 4, 6, 3 },
                    { 6, 0, 5, 5, 3, 8, 7, 9 },
                    { 8, 7, 4, 0, 5, 0, 0, 9 },
                    { 7, 7, 9, 9, 9, 0, 3, 6 },
                    { 5, 5, 4, 1, 6, 7, 1, 6 },
                    { 4, 0, 5, 0, 3, 0, 1, 7 },
                    { 9, 3, 7, 3, 9, 0, 0, 2 } };
        // Matrix B //
        int[][] BBB = { { 9, 2, 3, 0, 0, 6, 7, 1 },
                    { 2, 9, 7, 6, 6, 5, 3, 3 },
                    { 4, 9, 7, 5, 6, 3, 8, 7 },
                    { 6, 9, 4, 4, 2, 2, 7, 3 },
                    { 5, 0, 5, 6, 9, 4, 1, 5 },
                    { 3, 1, 1, 0, 5, 1, 3, 8 },
                    { 3, 8, 3, 2, 3, 9, 2, 9 },
                    { 1, 5, 0, 0, 1, 9, 2, 5 } };
        // Matrix C //
        int[][] CCC = s.multiply(AAA, BBB);
        end = System.nanoTime();
        System.out.println("\n8 x 8 matrix : ");
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                System.out.print(CCC[i][j] + " ");
            System.out.println();
        }
        execution = end - start;
        System.out.println("Execution time: " + execution + " nanoseconds");
	}
}
