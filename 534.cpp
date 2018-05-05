#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

////////////////////////////////////////////////////////////////////////////////////////////////////////////
template <class Value>
struct Array
{
    int  n, sz=1;
    Value* arr;

    void Initialize()
    {
        n=-1;
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
            n = sz/2;
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

struct Edge
{
    int		v;  // id of the adjacent node
    double	w;  // edge weight = distance between the two nodes
};

struct Node
{
    int x,y; // x and y coordinates of the node
    Array <Edge> adj;

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

// Find the square root of "v" in "n" iterations
double Sqrt(double v, int n=100)
{
    double X=0, Y=v, Sqr;
    for (int I=0; I < n; I++)
    {
        Sqr = (X+Y)/2;
        if ( Sqr*Sqr < v)
            X = Sqr;
        else
            Y = Sqr;
    }

    return Sqr;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int NumOfRocks,N=0;
    double Min, *Results = new double[100000];
    Graph G;

    while(true)
    {
        cin >> NumOfRocks;

        if (NumOfRocks == 0)
            break;

        double D[NumOfRocks];
        int P[NumOfRocks];
        bool V[NumOfRocks];

        for(int I=0; I<NumOfRocks; I++)
        {
            D[I]=999999;
            P[I]=-1;
            V[I]=false;
        }

        G.Initialize(NumOfRocks);

        for(int I=0; I<NumOfRocks; I++)
            cin >> G.nodes[I].x >> G.nodes[I].y;

        double Val;
        bool Flag = true;
        int Ind = 0;


        for(int I=0; I<NumOfRocks; I++)
        {
            V[Ind] = true;

            for(int It=0; It<NumOfRocks; It++)
            {
                Val = Sqrt( (pow( (G.nodes[Ind].x-G.nodes[It].x),2) + pow( (G.nodes[Ind].y-G.nodes[It].y),2) ) );
                if ( !V[It] && D[It] > Val)
                {
                    D[It] = Val;
                    P[It] = Ind;
                }
            }

            Min = 999999;
            for(int It=0; It<NumOfRocks; It++)
            {
                if ( !V[It] && D[It] < Min)
                {
                    Min = D[It];
                    Ind = It;
                }
            }
            if (Ind == 1)
            {
                Min = 0;
                while(P[Ind] != -1)
                {
                    if (D[Ind] > Min)
                    {
                        Min = D[Ind];
                    }
                    Ind = P[Ind];
                }
                Results[N] = Min;
                N++;
                break;
            }
        }
        G.Destroy();
    }


    for(int I=0; I<N; I++)
    {
        cout << "Scenario #"<<I+1<<endl;
        cout << "Frog Distance = " << setprecision(3) << fixed << Results[I] << endl << endl;
    }

    delete [] Results;
    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
