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

int main()
{
    int Itr,Inp,In,In1,In2;
    DisjointSets Sets;
    cin >> Itr;
    int Max[Itr];
    for (int I=0; I < Itr; I++)
    {
        cin >> In;
        Max[I]=1;
        Sets.Initialize(In+1);
        cin >> Inp;
        for (int It=0; It < Inp; It++)
        {
            cin >> In1 >> In2;
            Sets.Union(In1,In2);
            if ( Sets.num_nodes[Sets.Find(In1)] > Max[I])
                Max[I] = Sets.num_nodes[Sets.Find(In1)];
        }
        Sets.Destroy();
    }

    for (int It=0; It < Itr; It++)
        cout << Max[It] << endl;

    return 0;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
