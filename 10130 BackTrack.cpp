#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;
////////////////////////////////////////////////////////////////////////////////////////////////////////////
template<class Type>
void Merge(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int Middle = n/2;
    int F=0,L=Middle;
    Type *Temp = new Type[n];
    for (int I=0; I<n; I++)
    {
        if ( L== n || (F < Middle && IsBefore(a[F],a[L]) ) )
            Temp[I] = a[F++];
        else
            Temp[I] = a[L++];
    }
    for (int I=0; I<n; I++)
        a[I]=Temp[I];
    delete [] Temp;
}
template<class Type>
int MergeSort(Type* a, int n, bool (*IsBefore)(Type& a, Type& b))
{
    int Mid = n/2;
    if (n<=1)
        return 0;
    MergeSort<Type>(a,Mid,IsBefore);
    MergeSort<Type>(a+Mid,n-Mid,IsBefore);
    Merge<Type>(a,n,IsBefore);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
struct Obj
{
    int v;
    int w;
};
int n;       /// number of objects (input)
Obj a[1000]; /// objects (input)
////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool IsBefore(Obj& a, Obj& b) /// return true if unit value of a is greater than unit value of b
{
    return (double)a.v/a.w > (double)b.v/b.w;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int best_val; /// the best total value found until now
int Bound(int i, int w) /// upper bound on the total value of items [i..n-1] that can fit in w
{
    int Upper = 0,I;
    for(I = i ; I < n; I++)
    {
        if ( w - a[I].w >= 0 )
        {
            Upper += a[I].v;
            w -= a[I].w;
        }
        else
            break;
    }

    if (w > 0 && I < n)
        Upper +=  (double) w * a[I-1].v / a[I-1].w ;

    return Upper;
}
void BackTrack(int i, int w, int cur_val) /// starting from item i, remaining weight w, cur_value of objects[0..i-1]
{
    if(i == n)
    {
        if(cur_val > best_val)
            best_val = cur_val;
        return;
    }

    if(a[i].w <= w)
        BackTrack(i+1, w-a[i].w, cur_val+a[i].v);

    int Max = Bound(i,w) + cur_val;
    if (Max <= best_val)
        return;

    BackTrack(i+1, w, cur_val);
}
int ComputeKnapsack(int N, int W) // solve knapsack of N objects and W weight
{
    best_val = 0;
    BackTrack(0, W, 0);
    return best_val;
}
void Compute()
{
    int Test;
    cin >> Test;
    for (int I = 0; I < Test; I++)
    {
        cin >> n;
        for (int It = 0; It < n; It++)
            cin >> a[It].v >> a[It].w;

        MergeSort(a, n, IsBefore);

        int Group;
        cin >> Group;

        int *W = new int[Group];
        for (int It = 0; It < Group; It++)
            cin >> W[It];

        int Val = 0;
        for (int It = 0; It < Group; It++)
            Val += ComputeKnapsack(n,W[It]);

        delete [] W;

        cout << Val << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    //freopen("input_assign12_10130.txt", "r", stdin);
    Compute();
    return 0;
}
