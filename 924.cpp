#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Value>
struct Array
{
    int  n=-1, sz=1;
    Value* arr;

    void Initialize()
    {
        arr = new Value[sz];
    }
    void Destroy()
    {
        delete [] arr;
    }
    void AddLast(Value v)
    {
        n++;
        if (n < sz)
        {
            arr[n]=v;
        }
        else
        {
            Value *arra=new Value[sz];
            for (int i=0; i<sz; i++)
                arra[i]=arr[i];

            sz*=2;
            Destroy();
            Initialize();

            for (int i=0; i<sz/2; i++)
                arr[i]=arra[i];

            delete [] arra;
            arr[n]=v;
        }
    }
    void RemoveLast()
    {
        n--;
        if ( sz !=1 && arr[(sz/2)]==NULL)
        {
            sz/=2;
            Value *arra=new Value[sz];
            for (int i=0; i<sz; i++)
                arra[i]=arr[i];

            Destroy();
            Initialize();

            for (int i=0; i<sz; i++)
                arr[i]=arra[i];

            delete [] arra;
        }
    }
    Value& operator[](int i)
    {

        if (i<0||i>=sz)
            cout << "Error!" << endl;
        else
            return arr[i];

    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

struct Node
{
    Array<int> adj;

    void Initialize()
    {
        adj.Initialize();
    }
    void Destroy()
    {
        adj.Destroy();
    }
};

struct Graph
{
    int n;
    Node* nodes;

    void Initialize(int _n)
    {
        n = _n;
        nodes = new Node[_n];
        for (int I=0; I<_n; I++)
            nodes[I].Initialize();
    }
    void Destroy()
    {
        for (int I=0; I<n; I++)
            nodes[I].Destroy();
        delete [] nodes;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

template <class Type>
struct Queue
{
    int f, n;
    Type* elems;

    void Initialize(int size)
    {
        elems = new Type [size];
        f=0;
        n=0;
    }
    void Destroy()
    {
        delete [] elems;
    }
    void Add(Type t)
    {
        elems[n]=t;
        n++;
    }
    Type Pop()
    {
        f++;
        return elems[f-1];
    }
    Type Peek()
    {
        return elems[f];

    }
    int Num()
    {
        return n-f;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int In,In1,In2;
    Graph G;
    cin >> In;
    G.Initialize(In);
    for (int I=0; I<In; I++)
    {
        cin >> In1;
        for (int It=0; It<In1; It++)
        {
            cin >> In2;
            G.nodes[I].adj.AddLast(In2);
        }
    }

    Array<bool> Vis;
    Vis.Initialize();
    for (int I=0; I<In; I++)
        Vis.AddLast(false);

    cin >> In2;
    int Cases[In2];

    for (int I=0; I<In2; I++)
    {
        cin >> In1;
        Cases[I]=In1;
    }
    /////////////////////////////////////////////////
    Queue<int> Q;
    Q.Initialize(In*In);
    int Sum=0,M=0,D,last,CurrD=0,cou;
    for (int I=0; I<In2; I++)
    {
        for (int Itr=0; Itr <= Vis.n; Itr++)
            Vis[Itr]=false;
        Q.Add(Cases[I]);
        Vis[Cases[I]]=true;
        last=1;
        CurrD=0;
        M=0;
        while (Q.Num()!=0)
        {
            CurrD++;
            cou=last;
            last=0;
            for (int Itr=0; Itr < cou; Itr++)
            {
                for (int It=0; It < G.nodes[Q.Peek()].adj.n+1; It++)
                {
                    if (!Vis[G.nodes[Q.Peek()].adj[It]])
                    {
                        Sum++;
                        last++;
                        Q.Add(G.nodes[Q.Peek()].adj[It]);
                        Vis[G.nodes[Q.Peek()].adj[It]]=true;
                    }
                }
                Q.Pop();
            }
            if (Sum > M)
            {
                M=Sum;
                D=CurrD;
            }
            Sum=0;
        }
        if (M == 0)
            cout << 0 << endl;
        else
            cout << M << " " << D << endl;
    }
    G.Destroy();
    Vis.Destroy();
    Q.Destroy();
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
