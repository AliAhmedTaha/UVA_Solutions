#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
long long CountInvMerge(long long* a, long long n)
{
    long long Middle = n/2;
    long long Val = 0;
    long long F=0,L=Middle;
    long long *Temp = new long long[n];
    for (long long I=0; I<n; I++)
    {
        if ( L == n || ( ( F < Middle ) && ( a[F] <= a[L] ) ) )
            Temp[I] = a[F++];
        else
        {
            Temp[I] = a[L++];
            Val += (Middle-F);
        }
    }

    for (long long I=0; I<n; I++)
        a[I]=Temp[I];

    delete [] Temp;
    return Val;
}


long long CountInv(long long* a, long long n)
{
    long long Middle = n/2;

    if (n <= 1)
        return 0;

    return CountInv(a,Middle) + CountInv(a+Middle, n-Middle) + CountInvMerge(a,n);
}


////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    long long Sz,N=0,*Result = new long long[500000];

    while (true)
    {
        cin >> Sz;

        if (Sz==0)
            break;

        long long *Arr = new long long[Sz];
        for (long long I=0; I < Sz; I++)
            cin >> Arr[I];

        Result[N] = CountInv(Arr,Sz);
        N++;

        delete [] Arr;
    }

    for (long long I=0; I < N; I++)
        cout << Result[I] << endl;

    delete [] Result;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
