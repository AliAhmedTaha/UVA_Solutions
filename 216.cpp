#include <cstdio>
#include <cstdlib>
#include <limits.h>
#include <iomanip>
#include <cstring>
#include <cmath>
#include <iostream>
#define MAX_COMPUTERS 8
using namespace std;

void swap(int& a, int& b)
{
    int Temp = a;
    a = b;
    b = Temp;
}
struct Point
{
    int x,y;
};
double Dist(Point& a, Point& b)
{
    return sqrt(pow(a.x-b.x,2)+pow(a.y-b.y,2)) + 16;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int		n; /// number of computers (input)
Point	com[MAX_COMPUTERS]; /// locations of computers (input)
double	dist[MAX_COMPUTERS][MAX_COMPUTERS]; /// dist[i][j]=distance from com[i] to com[j] (pre-computed)
////////////////////////////////////////////////////////////////////////////////////////////////////////////
double	best_val; /// best value until now
int		best_sol[MAX_COMPUTERS]; /// best solution until now (a permutation)
int		s[MAX_COMPUTERS]; /// s is current permutation. s[i]=index of the ith computer in this permutation.
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void UpdateSol() /// evaluate the permutation s, then update best_val and best_sol if necessary
{
    for(int I=0; I<n; I++)
        best_sol[I] = s[I];
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Backtrack0(int i) /// backtrack using swaps
{
    if(i == n)
    {
        double Val=0;
        for (int I=0; I<n-1; I++)
            Val += dist[s[I]][s[I+1]];

        if (Val < best_val)
        {
            best_val = Val;
            UpdateSol();
        }
        return;
    }

    for (int J=i; J<n; J++)
    {
        swap(s[i],s[J]);
        Backtrack0(i+1);
        swap(s[i],s[J]);
    }
}
void Compute0()/// do necessay initializations and call Backtrack0()
{
    for (int I=0; I<n; I++)
        s[I] = I;
    Backtrack0(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool v[MAX_COMPUTERS]; /// v[i]=true if com[i] already taken in the permutation
void Backtrack1(int i) /// backtrack using the v[] array
{
    if(i == n)
    {
        double Val=0;
        for (int I=0; I<n-1; I++)
            Val += dist[s[I]][s[I+1]];

        if (Val < best_val)
        {
            best_val = Val;
            UpdateSol();
        }
        return;
    }

    for (int J=0; J<n; J++)
        if(!v[J])
        {
            s[i] = J;
            v[J]= true;
            Backtrack1(i+1);
            v[J] = false;
        }
}
void Compute1() /// do necessay initializations and call Backtrack1()
{
    for (int I=0; I<n; I++)
        v[I] = false;
    Backtrack1(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Dancing Links:
int F[MAX_COMPUTERS+1]; /// head=F[0], elements are indexed from 1 to n, F[n]=0
int B[MAX_COMPUTERS+1]; /// B[0]=n, B[1]=0
void Remove(int i)
{
    F[B[i]]=F[i];
    B[F[i]]=B[i];
}
void Restore(int i)
{
    B[F[i]]=i;
    F[B[i]]=i;
}
void InitDancingLinks(int n)
{
    int i;
    for(i=0; i<n; i++)
        F[i]=i+1;
    F[n]=0;
    for(i=n; i>0; i--)
        B[i]=i-1;
    B[0]=n;
}
/// for(i=F[0];i!=0;i=F[i]) iterate on available list indexes
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Backtrack2(int i) /// backtrack using dancing links
{
    if(i == n)
    {
        double Val=0;
        for (int I=0; I<n-1; I++)
            Val += dist[s[I]][s[I+1]];

        if (Val < best_val)
        {
            best_val = Val;
            UpdateSol();
        }
        return;
    }

    for (int J=F[0]; J!=0; J=F[J])
    {
        s[i] = J-1;
        Remove(J);
        Backtrack2(i+1);
        Restore(J);
    }
}
void Compute2() /// do necessay initializations and call Backtrack2()
{
    InitDancingLinks(n);
    Backtrack2(0);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void ComputeCore()
{
    /// do necessay initializations of dist[][] and best_val
    for(int I=0; I<n; I++)
        for(int It=0; It<n; It++)
            dist[I][It] = Dist(com[I],com[It]);

    best_val = INT_MAX;

    //Compute0();
    //Compute1();
    Compute2();
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
void Compute() /// get input and then call ComputeCore(); then print output
{
    int NetWork = 1;
    while(true)
    {
        cin >> n;

        if (n == 0)
            break;

        for(int I=0; I < n; I++)
            cin >> com[I].x >> com[I].y;

        ComputeCore();

        cout << "**********************************************************" << endl;
        cout << "Network #" << NetWork++ << endl;
        for(int I=0; I < n-1; I++)
        {
            cout << "Cable requirement to connect (" << com[best_sol[I]].x << "," << com[best_sol[I]].y << ") to (";
            cout << com[best_sol[I+1]].x << "," << com[best_sol[I+1]].y << ") is ";
            cout << setprecision(2) << fixed << dist[best_sol[I]][best_sol[I+1]] <<" feet." << endl;
        }
        cout  << "Number of feet of cable required is " << best_val << "." << endl;
    }
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
    Compute();
    return 0;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////
