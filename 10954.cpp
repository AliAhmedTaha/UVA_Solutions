#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
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

template<class Elem>
struct Heap
{
    Array<Elem> a;
    bool (*IsBefore)(int&, int&);
    void Initialize(bool (*_IsBefore)(int&, int&))
    {
        a.Initialize();
        IsBefore = _IsBefore;
    }
    void Destroy()
    {
        a.Destroy();
    }
    int Child(int i)
    {
        return (i*2)+1;
    }
    int Parent(int i)
    {
        return (i-1)/2;
    }
    void MoveUp(int ind)
    {
        while (true)
        {
            if ( IsBefore(a[ind],a[Parent(ind)]) )
            {
                Elem temp=a[ind];
                a[ind]=a[Parent(ind)];
                ind=Parent(ind);
                a[ind]=temp;
            }
            else
                break;
        }
    }
    void MoveDown(int ind)
    {
        while (true)
        {
            if(Child(ind)+1<=a.n)
            {
                if (IsBefore(a[Child(ind)],a[Child(ind)+1])&&IsBefore(a[Child(ind)],a[ind]))
                {
                    Elem temp=a[ind];
                    a[ind]=a[Child(ind)];
                    a[Child(ind)]=temp;
                    ind=Child(ind);
                }
                else if (IsBefore(a[Child(ind)+1],a[Child(ind)])&&IsBefore(a[Child(ind)+1],a[ind]))
                {
                    Elem temp=a[ind];
                    a[ind]=a[Child(ind)+1];
                    a[Child(ind)+1]=temp;
                    ind=Child(ind)+1;
                }
                else if (IsBefore(a[Child(ind)],a[ind]))
                {
                    Elem temp=a[ind];
                    a[ind]=a[Child(ind)];
                    a[Child(ind)]=temp;
                    ind=Child(ind);
                }
                else

                    break;
            }
            else if (Child(ind)<=a.n&&IsBefore(a[Child(ind)],a[ind]))
            {
                Elem temp=a[ind];
                a[ind]=a[Child(ind)];
                a[Child(ind)]=temp;
                ind=Child(ind);
            }
            else
                break;
        }
    }

    void Add(Elem e)
    {
        a.AddLast(e);
        MoveUp(a.n);
    }

    Elem GetFirst()
    {
        return a[0];
    }

    Elem RetrieveFirst()
    {
        Elem T=a[0];
        a[0]=a[a.n];
        a.RemoveLast();
        MoveDown(0);
        return T;
    }
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool IsBeforeInt(int& a, int& b)
{
    return a < b;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int Itr,In;
    Array<int> Costs,Sum;
    Heap<int> H;
    H.Initialize(IsBeforeInt);
    Costs.Initialize();
    while (true)
    {
        cin>>Itr;

        if (Itr==0)
            break;

        for (int I=0; I<Itr; I++)
        {
            cin>>In;
            H.Add(In);
        }
        Sum.Initialize();
        for (int I=0; I<Itr-1; I++)
        {
            In=H.RetrieveFirst();
            In+=H.RetrieveFirst();
            H.Add(In);
            Sum.AddLast(In);
        }
        H.RetrieveFirst();
        In=0;

        for (int I=0; I<=Sum.n; I++)
            In+=Sum[I];

        Sum.Destroy();
        Costs.AddLast(In);
    }

    for (int I=0; I<=Costs.n; I++)
        cout << Costs[I] << endl;

    Costs.Destroy();
    H.Destroy();

    return 0;
}
