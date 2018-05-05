#include <cstdio>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <cmath>
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

struct Point
{
    double x,y;
};

bool IsBeforeX(Point& a, Point& b)
{
    return a.x < b.x;
}

bool IsBeforeY(Point& a, Point& b)
{
    return a.y < b.y;
}

double dist(Point& a, Point& b)
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2));
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Sort the points p according to x before calling this function
double ClosestPair(Point* p, int n)
{
    double Min = 100000;
    if (n <= 3)
    {
        for (int i = 0; i < n; ++i)
            for (int j = i+1; j < n; ++j)
                if (dist(p[i], p[j]) < Min)
                    Min = dist(p[i], p[j]);
        MergeSort(p,n,IsBeforeY);
        return Min;
    }

    int mid = n/2;

    double a = ClosestPair(p,mid);
    double b = ClosestPair(p+mid,n-mid);

    double Mini = a;
    if (b < Mini)
        Mini = b;

    MergeSort(p,n,IsBeforeY);

    Point *Arr = new Point[n];
    double Test = (0.5*(p[mid-1].x+p[mid].x));
    int N=0;

    for (int i=0; i < n; i++)
        if(abs(Test-p[i].x) <= Min )
            Arr[N++] = p[i];

    double Min0 = 100000;
    for (int i = 0; i < N; ++i)
        for (int j = i+1; j < i+8&&j<N; ++j)
            if (dist(Arr[i], Arr[j]) < Min0)
                Min0 = dist(Arr[i], Arr[j]);

    if (Min0 < Mini)
        Mini = Min0;

    delete [] Arr;
    return Mini;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    double *R = new double[100000];
    int N,Ind=0;
    Point *P;
    while(true)
    {
        cin >> N;
        if (N == 0)
            break;

        P = new Point[N];
        for (int I=0; I<N; I++)
            cin >> P[I].x >> P[I].y;

        MergeSort(P,N,IsBeforeX);

        R[Ind] = ClosestPair(P,N);
        Ind++;

        delete [] P;
    }

    for (int I=0; I<Ind; I++)
        if ( R[I] < 10000 )
            cout << setprecision(4) << fixed << R[I] << endl;
        else
            cout << "INFINITY" << endl;

    delete [] R;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
