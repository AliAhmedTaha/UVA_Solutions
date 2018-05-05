#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct DisjointSets
{
    int n;
    int* parent;
    int* num_nodes;

    void Initialize(int _n)
    {
        n=_n;
        parent = new int [_n];
        num_nodes = new int [_n];
        for (int I=0; I<_n; I++)
        {
            parent[I]=I;
            num_nodes[I]=1;
        }
    }
    void Destroy()
    {
        delete [] parent;
        delete [] num_nodes;
    }
    int Find(int i)
    {
        while (true)
        {
            if (parent[i]==i)
                return i;
            else
                i=parent[i];
        }
    }
    bool Union(int i, int j)
    {
        if (Find(i)==Find(j))
            return false;
        else
        {
            if (num_nodes[parent[Find(i)]]<num_nodes[parent[Find(j)]])
            {
                num_nodes[parent[Find(j)]] += num_nodes[parent[Find(i)]];
                parent[Find(i)] = parent[Find(j)];
            }
            else
            {
                num_nodes[parent[Find(i)]] += num_nodes[parent[Find(j)]];
                parent[Find(j)] = parent[Find(i)];
            }
            n--;
            return true;
        }
    }
};
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

struct Edge
{
    int u, v;
    int w;
};

bool IsBeforeEdge(Edge& a, Edge& b)
{
    return a.w < b.w;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{

    int J,R,U,V,W,N=0,Cou,Results[100000];
    while (true)
    {
        cin >> J >> R;
        if (J==0&&R==0)
            break;
        Edge *Arr = new Edge[R];
        for (int I=0; I<R; I++)
        {
            cin >> U >> V >> W;

            Arr[I].u=U;
            Arr[I].v=V;
            Arr[I].w=W;
        }

        MergeSort(Arr,R,IsBeforeEdge);

        DisjointSets Nodes;
        Nodes.Initialize(J);

        bool *Taken = new bool[R];
        for (int I=0; I<R; I++)
            Taken[I] = false;
        Cou=0;

        for (int I=0; I < R; I++)
        {
            if ( Nodes.Find(Arr[I].u) != Nodes.Find(Arr[I].v) )
            {
                Nodes.Union(Arr[I].u,Arr[I].v);
                Taken[I]=true;
                Cou++;
            }
            if ( Cou == J-1 )
                break;
        }

        int Sum=0;
        for (int I=0; I < R; I++)
            if ( !Taken[I] )
                Sum += Arr[I].w;

        Results[N]=Sum;
        N++;
        delete [] Taken,Arr;
        Nodes.Destroy();
    }

    for (int I=0; I < N; I++)
        cout << Results[I] << endl;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
