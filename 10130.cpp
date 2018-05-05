#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Obj
{
    int v; // value (price) of object
    int w; // weight of object
};
Obj a[1000];
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int T1[1001][31];
int Knapsack1(int n, int w)
{

    if(n==0)
        return 0;

    if(T1[n][w]>=0)
        return T1[n][w];

    int ret = Knapsack1(n-1,w);
    int cv = a[n-1].v;
    int cw = a[n-1].w;

    if(cw <= w)
    {

        int r = cv + Knapsack1(n-1,w-cw);

        if (r > ret)
            ret =r;

        T1[n][w] = ret;

    }

    return ret;

}
int ComputeKnapsack1(int N, int W) /// Recursive - memoization - initialize T then call Knapsack1(N,W);
{

    for (int I = 0; I < 1001; I++)
        for (int It = 0; It < 31; It++)
            T1[I][It] = -1;

    return Knapsack1(N,W);

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int T2[1001][31];
int ComputeKnapsack2(int N, int W) /// Bottom-up, do not save space
{

    for (int n = 0; n <= N; n++)
        for (int w = 0; w <= W; w++)
        {

            if(n==0)
            {
                T2[n][w]=0;
                continue;
            }

            int ret = T2[n-1][w];
            int cv = a[n-1].v;
            int cw = a[n-1].w;

            if(cw <= w)
            {
                int r = cv + T2[n-1][w-cw];

                if (r > ret)
                    ret = r;

            }

            T2[n][w] = ret;

        }

    return T2[N][W];

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int T3[2][31];
int ComputeKnapsack3(int N, int W) /// Bottom-up, use two rows only
{

    int cur = 0;

    for (int n = 0; n <= N; n++)
    {

        for (int w = 0; w <= W; w++)
        {

            if(n==0)
            {
                T3[cur][w]=0;
                continue;
            }

            T3[cur][w] = T3[1-cur][w];

            int cv = a[n-1].v;
            int cw = a[n-1].w;

            if(cw <= w)
            {

                int r = cv + T3[1-cur][w-cw];

                if (r > T3[cur][w])
                    T3[cur][w] = r;

            }

        }

        cur = 1-cur;

    }

    return T3[1-cur][W];

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int T4[31];
int ComputeKnapsack4(int N, int W) /// Bottom-up, save maximum space
{

    for (int n = 0; n <= N; n++)
        for (int w = W; w >= 0; w--)
        {

            if(n == 0)
            {
                T4[w]=0;
                continue;
            }

            int cv = a[n-1].v;
            int cw = a[n-1].w;

            if(cw <= w)
            {

                int r = cv + T4[w-cw];

                if (r > T4[w])
                    T4[w] = r;

            }

        }

    return T4[W];

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int ComputeKnapsack(int N, int W) /// Here we can choose the method
{
    //return ComputeKnapsack1(N,W);
    //return ComputeKnapsack2(N,W);
    //return ComputeKnapsack3(N,W);
    return ComputeKnapsack4(N,W);
}
void Compute() /// Get input and call ComputeKnapsack() whenever needed
{

    int Test,Objects,Group,N=0;
    int *Results = new int[1000];
    cin >> Test;

    for (int I = 0; I < Test; I++)
    {
        cin >> Objects;
        for (int It = 0; It < Objects; It++)
            cin >> a[It].v >> a[It].w;

        cin >> Group;
        int *W = new int[Group];

        for (int It = 0; It < Group; It++)
            cin >> W[It];

        int Val =0;
        for (int It = 0; It < Group; It++)
            Val += ComputeKnapsack(Objects,W[It]);

        Results[N++] = Val;

        delete [] W;

    }

    for (int I = 0; I < N; I++)
        cout << Results[I] << endl;

    delete [] Results;

}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Compute();
    return 0;
}
