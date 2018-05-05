#include <iostream>
#include "limits.h"
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int p[11]; /// the dimensions of matrices
int T[11][11]; /// T[a][b]=the optimal number of multiplication of p[a]...p[b]
int D[11][11]; /// D[a][b]=the decision (value of k) that gets T[a][b]
/// Top down version
int MatChain(int a, int b) /// Recursive
{
    if ( a+1 == b )
    {
        T[a][b] = 0;
        return 0;
    }

    if ( T[a][b] >= 0 )
        return T[a][b];

    T[a][b] = INT_MAX;
    for (int k = a+1; k < b; k++)
    {
        int v = MatChain(a,k) + MatChain(k,b) + p[a] * p[k] * p[b];
        if ( v < T[a][b] )
        {
            T[a][b] = v;
            D[a][b] = k;
        }
    }
    return T[a][b];

}
/// Initialize T then call MatChain(0,n)
void MatChainTopDown(int n)
{
    for (int I = 0; I <= n; I++)
        for (int It = 0; It <= n; It++)
            T[I][It] = -1;

    MatChain(0,n);
}
/// BottomUp version
void MatChainBottomUp(int n)
{
    for (int S = 1; S <= n; S++)
        for (int I = 0; I+S <= n; I++)
        {
            int J = I+S;
            T[I][J] = INT_MAX;
            for (int K = I+1; K < J; K++)
            {
                int V = T[I][K] + T[K][J] + p[I] * p[K] * p[J];
                if ( V < T[I][J] )
                {
                    T[I][J] = V;
                    D[I][J] = K;
                }
            }
        }
}
///Recursive to output the solution for both versions
void MatChainSol(int a, int b)
{
    if (a+1 == b)
        cout << "A" << a+1;
    else
    {
        int k = D[a][b];
        cout << "(";
        MatChainSol(a,k);
        cout << " x ";
        MatChainSol(k,b);
        cout << ")";
    }
}
void Compute()
{

    int NumOfPairs,N,Cou=0;
    int *Size = new int[100000];
    struct Solution
    {
        int CpyD[11][11];
    };
    Solution *Results = new Solution[100000];

    while (true)
    {
        cin >> NumOfPairs;
        if(NumOfPairs == 0)
            break;

        N = 0;
        for (int I = 0; I < NumOfPairs*2; I++)
        {
            if (I % 2 == 0 && I != 0)
                N--;
            cin >> p[N++];
        }

    /// //// Here we can Switch Methods ////
        MatChainBottomUp(NumOfPairs);
        //MatChainTopDown(NumOfPairs);
    /// /////////// ///////////////////////

        for (int I = 0; I <= N; I++)
            for (int It = 0; It <= N; It++)
                Results[Cou].CpyD[I][It] = D[I][It];
        Size[Cou++] = NumOfPairs;
    }

    for (int I = 0; I < Cou; I++)
    {
        for (int It = 0; It <= Size[I]; It++)
            for (int Itr = 0; Itr <= Size[I]; Itr++)
                D[It][Itr] = Results[I].CpyD[It][Itr];

        cout << "Case " << I+1 << ": ";
        MatChainSol(0,Size[I]);
        cout << endl;
    }

    delete [] Results;
    delete [] Size;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Compute();
    return 0;
}
