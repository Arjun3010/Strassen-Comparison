// Import Modules // 
#include <algorithm>
#include <iostream>
#include <bits/stdc++.h>
#include <chrono>
using namespace std::chrono;
using namespace std;

int nextpowerof2(int k){
    return pow(2, int(ceil(log2(k))));
}

// Matrix Display //
void display(vector< vector<int>> &matrix, int m, int n){
    for (int i = 0; i < m; i++){
        for (int j = 0; j < n; j++){
            if (j != 0){
                cout << "\t";
            }
            cout << matrix[i][j];
        }
        cout << endl;
    }
}

// Matrix Addition //
void add(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, int size){
    int i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            C[i][j] = A[i][j] + B[i][j];
        }
    }
}

// Matrix Subtraction //
void sub(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, int size){
    int i, j;
    for (i = 0; i < size; i++){
        for (j = 0; j < size; j++){
            C[i][j] = A[i][j] - B[i][j];
        }
    }
}

// Strassen's Technique //
void Strassen_algorithmA(vector<vector<int>> &A, vector<vector<int>> &B, vector<vector<int>> &C, int size){
    if (size == 1){
        C[0][0] = A[0][0] * B[0][0];
        return;
    }
    else{
        int new_size = size / 2;
        vector<int> z(new_size);
        vector<vector<int>>
            a11(new_size, z), a12(new_size, z), a21(new_size, z), a22(new_size, z),
            b11(new_size, z), b12(new_size, z), b21(new_size, z), b22(new_size, z),
            c11(new_size, z), c12(new_size, z), c21(new_size, z), c22(new_size, z),
            p1(new_size, z), p2(new_size, z), p3(new_size, z), p4(new_size, z),
            p5(new_size, z), p6(new_size, z), p7(new_size, z),
            aResult(new_size, z), bResult(new_size, z);

        int i, j;
        for (i = 0; i < new_size; i++){
                for (j = 0; j < new_size; j++){
                    a11[i][j] = A[i][j];
                    a12[i][j] = A[i][j + new_size];
                    a21[i][j] = A[i + new_size][j];
                    a22[i][j] = A[i + new_size][j + new_size];
    
                    b11[i][j] = B[i][j];
                    b12[i][j] = B[i][j + new_size];
                    b21[i][j] = B[i + new_size][j];
                    b22[i][j] = B[i + new_size][j + new_size];
                }
        }
        add(a11, a22, aResult, new_size);
        add(b11, b22, bResult, new_size);
        Strassen_algorithmA(aResult, bResult, p1, new_size); 

        add(a21, a22, aResult, new_size);
        Strassen_algorithmA(aResult, b11, p2, new_size);

        sub(b12, b22, bResult, new_size);
        Strassen_algorithmA(a11, bResult, p3, new_size);

        sub(b21, b11, bResult, new_size);
        Strassen_algorithmA(a22, bResult, p4, new_size); 

        add(a11, a12, aResult, new_size);
        Strassen_algorithmA(aResult, b22, p5, new_size);

        sub(a21, a11, aResult, new_size);
        add(b11, b12, bResult, new_size);               
        Strassen_algorithmA(aResult, bResult, p6, new_size);

        sub(a12, a22, aResult, new_size);
        add(b21, b22, bResult, new_size);                
        Strassen_algorithmA(aResult, bResult, p7, new_size);

        add(p3, p5, c12, new_size);
        add(p2, p4, c21, new_size);

        add(p1, p4, aResult, new_size);
        add(aResult, p7, bResult, new_size);
        sub(bResult, p5, c11, new_size);

        add(p1, p3, aResult, new_size);     
        add(aResult, p6, bResult, new_size); 
        sub(bResult, p2, c22, new_size); 

        for (i = 0; i < new_size; i++){
            for (j = 0; j < new_size; j++){
                C[i][j] = c11[i][j];
                C[i][j + new_size] = c12[i][j];
                C[i + new_size][j] = c21[i][j];
                C[i + new_size][j + new_size] = c22[i][j];
            }
        }
    }
}
void strassen_algorithm(vector<vector<int>> &A, vector<vector<int>> &B, int m, int n, int a, int b){  
    int k = max({m, n, a, b});
    int s = nextpowerof2(k);

    vector<int> z(s);
    vector<vector<int>> Aa(s, z), Bb(s, z), Cc(s, z);

    for (unsigned int i = 0; i < m; i++){
        for (unsigned int j = 0; j < n; j++){
            Aa[i][j] = A[i][j];
        }
    }
    for (unsigned int i = 0; i < a; i++){
        for (unsigned int j = 0; j < b; j++){
            Bb[i][j] = B[i][j];
        }
    }
    
    Strassen_algorithmA(Aa, Bb, Cc, s);
    vector<int> temp1(b);
    vector<vector<int>> C(m, temp1);
    for (unsigned int i = 0; i < m; i++){
        for (unsigned int j = 0; j < b; j++){
            C[i][j] = Cc[i][j];
        }
    }
    display(C, m, b);
}

// Main Function //
int main() {
    auto start = high_resolution_clock::now();
    vector<vector<int>> a = { { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 } };
    vector<vector<int>> b = { { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 },
                    { 1, 2, 3, 4 } };
    cout << "4 x 4 Matrix : \n";
    strassen_algorithm(a, b, 4, 4, 4, 4);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
    
    start = high_resolution_clock::now();
    vector<vector<int>> aa = { { 2, 0, 4, 4, 9, 0 },
                    { 7, 8, 3, 4, 4, 7 },
                    { 9, 8, 8, 0, 4, 4 },
                    { 1, 2, 7, 6, 2, 0 },
                    { 5, 2, 7, 5, 6, 8 },
                    { 3, 5, 8, 1, 7, 4 } };
    vector<vector<int>> bb = { { 5, 2, 5, 4, 0, 7 },
                    { 1, 1, 3, 6, 3, 4 },
                    { 8, 7, 2, 3, 7, 3 },
                    { 3, 8, 7, 0, 0, 5 }, 
                    { 3, 4, 8, 3, 4, 1 },
                    { 6, 1, 6, 4, 8, 0 } };
    cout << "6 x 6 Matrix : \n";
    strassen_algorithm(aa, bb, 6, 6, 6, 6);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
    
    start = high_resolution_clock::now();
    vector<vector<int>> aaa = { { 4, 3, 4, 7, 3, 5, 7, 7 },
                    { 5, 5, 5, 7, 6, 4, 6, 3 },
                    { 6, 0, 5, 5, 3, 8, 7, 9 },
                    { 8, 7, 4, 0, 5, 0, 0, 9 },
                    { 7, 7, 9, 9, 9, 0, 3, 6 },
                    { 5, 5, 4, 1, 6, 7, 1, 6 },
                    { 4, 0, 5, 0, 3, 0, 1, 7 },
                    { 9, 3, 7, 3, 9, 0, 0, 2 } };
    vector<vector<int>> bbb = { { 9, 2, 3, 0, 0, 6, 7, 1 },
                    { 2, 9, 7, 6, 6, 5, 3, 3 },
                    { 4, 9, 7, 5, 6, 3, 8, 7 },
                    { 6, 9, 4, 4, 2, 2, 7, 3 },
                    { 5, 0, 5, 6, 9, 4, 1, 5 },
                    { 3, 1, 1, 0, 5, 1, 3, 8 },
                    { 3, 8, 3, 2, 3, 9, 2, 9 },
                    { 1, 5, 0, 0, 1, 9, 2, 5 } };
    cout << "8 x 8 Matrix : \n";
    strassen_algorithm(aaa, bbb, 8, 8, 8, 8);
    stop = high_resolution_clock::now();
    duration = duration_cast<microseconds>(stop - start);
    cout << "Execution time: " << duration.count() << " microseconds" << endl;
    return 0;
}
