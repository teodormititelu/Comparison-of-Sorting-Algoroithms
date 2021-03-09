#include <bits/stdc++.h>
#include <cstdlib>
#include <chrono>

using namespace std;

const int NMAX = 10000001;


ofstream fout("output.out");

int N, V[NMAX];
int C[3][NMAX];

default_random_engine RandGenerator( time(0) );
uniform_int_distribution < int > random( 0, 2147483647 );

void BubbleSort( int lf, int rg )
{
    bool sorted = false;
    int k = 0;

    while( sorted == false )
    {
        sorted = true;

        for( int i = lf; i <= rg-k; ++i )
            if ( V[i] > V[i+1] )
            {
                swap( V[i], V[i+1] );
                sorted = false;
            }
        k++;
    }
}
int Pivot(int lf,int rg)
{
    int i = lf, j = rg, stepi = 1, stepj = 0;

    while( i < j )
    {
        if( V[i] > V[j] )
        {
            swap( V[i], V[j] );
            stepi = 1 - stepi;
            stepj = 1 - stepj;
        }

        i += stepi;
        j -= stepj;
    }
    return i;
}
void QS(int lf,int rg)
{
    if( rg-lf <= 5 )
    {
        BubbleSort( lf, rg );
        return;
    }

    int r = random( RandGenerator ) % (rg-lf+1) + lf;
    swap( V[r], V[rg] );

    int p = Pivot( lf, rg );
    QS(lf, p-1);
    QS(p+1, rg);

}

void QS_med3( int lf, int rg )
{
    if( rg-lf <= 5 )
    {
        BubbleSort( lf, rg );
        return;
    }

    int r1 = random( RandGenerator ) % (rg-lf+1) + lf;
    int r2 = random( RandGenerator ) % (rg-lf+1) + lf;
    int r3 = random( RandGenerator ) % (rg-lf+1) + lf;

    int r;

    if( V[r1] <= V[r2] && V[r2] <= V[r3] ) r = r2;
    if( V[r3] <= V[r2] && V[r2] <= V[r1] ) r = r2;
    if( V[r2] <= V[r1] && V[r1] <= V[r3] ) r = r1;
    if( V[r3] <= V[r1] && V[r1] <= V[r2] ) r = r1;
    if( V[r1] <= V[r3] && V[r3] <= V[r2] ) r = r3;
    if( V[r2] <= V[r3] && V[r3] <= V[r1] ) r = r3;

    swap( V[r], V[rg] );

    int p = Pivot( lf, rg );
    QS_med3(lf, p-1);
    QS_med3(p+1, rg);

}

class BinarySearchTree
{
    struct nod
    {
        int val;
        nod *lf = NULL, *rg = NULL;
        nod *parent = NULL;
        int disc = 0;

    };

    nod *root;

    nod *nul = NULL;

    void Insert( nod *&root, int x )
    {
        if( Empty() )
        {
            root = new nod;
            root -> val = x;
            return;
        }

        if( x < root -> val )

            if( root -> lf )
                Insert( root -> lf, x );

            else
            {
                root -> lf = new nod;
                root -> lf -> val = x;
                root -> lf -> parent = root;
                root -> lf -> disc = 1;
                return;
            }
        if( x > root -> val )

            if( root -> rg )
                Insert( root -> rg, x );

            else
            {
                root -> rg = new nod;
                root -> rg -> val = x;
                root -> rg -> parent = root;
                root -> rg -> disc = 2;
                return;
            }
    }

    nod* Search( nod *&root, int x )
    {
        if( Empty() ) return nul;

        if( root -> val == x ) return root;

        if( x < root -> val ) return Search( root -> lf, x );
        else return Search( root -> rg, x );
    }

    void Sort( nod *& root, int V[] )
    {
        if( root -> lf ) Sort( root -> lf, V );

        V[++V[0]] = root -> val;

        if( root -> rg ) Sort( root -> rg, V );
    }

public:

    BinarySearchTree()
    {
        root = NULL;
    }

    ~BinarySearchTree()
    {
        delete root;
    }

    bool Empty()
    {
        return root == NULL ;
    }

    void Delete( int x )
    {
        if( Empty() ) return;

        nod *root_copy = root;

        root = Search( root, x );

        if( root == nul )
        {
            root = root_copy;
            return;
        }

        nod *nodx = root;

        if( nodx -> rg )
        {
            root = nodx -> rg;
            root -> parent = nodx -> parent;

            if( nodx -> disc == 1 ) nodx -> parent -> lf = root;
            else nodx -> parent -> rg = root;

            if( nodx -> lf )
            {
                nod *aux = nodx -> rg;
                while( aux -> lf ) aux = aux -> lf;
                aux -> lf = nodx -> lf;
            }
        }
        else
        {
            if( nodx -> lf )
            {
                root = nodx -> lf;
                root -> parent = nodx -> parent;
                if( nodx -> disc == 1 )nodx -> parent -> lf = root;
                else nodx -> parent -> rg = root;
            }
            else root = NULL;
        }

        if( nodx == root )root = NULL;
        else root = root_copy;

        delete nodx;

        return;
    }

    void Insert( int x )
    {
        Insert( root, x );
    }

    void Sort( int V[] )
    {
        Sort( root, V );
    }
};

class Heap
{
    vector < int > H;

    inline int parent( int nod )
    {
        return ( ( nod - 1 ) >> 1 ) ;
    }

    inline int left( int nod )
    {
        return ( nod << 1 ) + 1;
    }

    inline int right( int nod )
    {
        return ( nod << 1 ) + 2;
    }

    void HeapUp( int nod )
    {

        while ( nod && H[nod] > H[parent( nod )] )
        {
            swap( H[nod], H[parent( nod )] );
            nod = parent ( nod );
        }

    }

    void HeapDown( int nod )
    {
        int son;

        do
        {
            son = 0;

            if( left( nod ) < H.size() )
            {
                son = left( nod );

                if( right( nod ) < H.size() && H[right( nod )] > H[left( nod )] )
                    son = right( nod );

                if( H[son] <= H[nod] ) son = 0;
            }
            if( son )
            {
                swap( H[son], H[nod] );
                nod = son;
            }

        }
        while( son );

    }

public:

    ~Heap()
    {
        H.clear();
    }

    int Max()
    {
        return H[0];
    }

    int Size()
    {
        return H.size();
    }

    void Insert( int x )
    {
        H.push_back( x );
        HeapUp( H.size() - 1 );
    }

    void Delete( int nod )
    {
        H[nod] = H[H.size()-2];
        H.pop_back();

        if( nod && H[nod] > H[parent( nod )] )
            HeapUp( nod );
        else HeapDown( nod );
    }

    void Build( int V[], int N )
    {

        for( int i = 1; i <= N; ++i )
            H.push_back( V[i] );

        for (int i = H.size() / 2 + 1; i >= 0; --i)
            HeapDown( i );
    }

    void Sort( int V[], int N )
    {
        Build( V, N );

        for( int i = H.size()-1; i >= 0; --i )
        {
            swap( H[i], H[0] );
            V[i+1] = H[i];
            H.pop_back();
            HeapDown( 0 );
        }
    }
};

void Radix( int V[] )
{
    long long vmax = V[1];

    for( int i = 2; i <= N; ++i )
        if( V[i] > vmax ) vmax = V[i];

    queue < int > B[10];

    int bucket, index;

    for( long long exp = 1; exp <= vmax; exp *= 10 )
    {
        for( int i = 1; i <= N; ++i )
        {
            bucket = (V[i] / exp) % 10;

            B[bucket].push( V[i] );
        }

        index = 0;

        for( auto &Bucket: B )
        {
            while( !Bucket.empty() )
            {
                V[++index] = Bucket.front();
                Bucket.pop();
            }
        }
    }
}

void Radix_Base( int V[], int base )
{
    long long vmax = V[1];

    for( int i = 2; i <= N; ++i )
        if( V[i] > vmax ) vmax = V[i];

    queue < int > B[ ( 1 << base ) ];

    int bucket, index;
    int mask = ( 1 << base ) - 1;

    for( int exp = 0; ( 1LL << exp ) <= vmax; exp += base )
    {
        for( int i = 1; i <= N; ++i )
        {
            bucket = ( V[i] & (mask << exp) ) >> exp;

            B[bucket].push( V[i] );
        }

        index = 0;

        for( auto &Bucket: B )
        {
            while( !Bucket.empty() )
            {
                V[++index] = Bucket.front();
                Bucket.pop();
            }
        }
    }
}

void Check_QS()
{
    fout << "QuickSort + BS: \t\t\t\t";

    for( int j = 0; j <= 2; ++j )
    {
        for( int i = 1; i <= N; ++i ) V[i] = C[j][i];

        chrono::steady_clock::time_point _start( chrono::steady_clock::now() );

        QS( 1, N );

        chrono::steady_clock::time_point _end( chrono::steady_clock::now() );

        fout << chrono::duration_cast< chrono::milliseconds >( _end - _start).count();
        if( j != 2 ) fout << '\\';
    }
    fout << " ms\n";
}

void Check_QS_med3()
{
    fout << "QuickSort med 3 + BS:\t\t\t";

    for( int j = 0; j <= 2; ++j )
    {
        for( int i = 1; i <= N; ++i ) V[i] = C[j][i];

        chrono::steady_clock::time_point _start( chrono::steady_clock::now() );

        QS_med3( 1, N );

        chrono::steady_clock::time_point _end( chrono::steady_clock::now() );

        fout << chrono::duration_cast< chrono::milliseconds >( _end - _start).count();
        if( j != 2 ) fout << '\\';
    }
    fout << " ms\n";
}

void Check_TreeSort()
{
    fout << "TreeSort, Unbalanced BST: \t\t";

    for( int j = 0; j <= 2; ++j )
    {
        for( int i = 1; i <= N; ++i ) V[i] = C[j][i];

        chrono::steady_clock::time_point _start( chrono::steady_clock::now() );

        BinarySearchTree BST;

        for ( int i = 1; i <= N; ++i )
            BST.Insert( V[i] );

        BST.Sort( V );

        chrono::steady_clock::time_point _end( chrono::steady_clock::now() );

        fout << chrono::duration_cast< chrono::milliseconds >( _end - _start).count();
        if( j != 2 ) fout << '\\';
    }
    fout << " ms\n";
}

void Check_HeapSort()
{
    fout << "Heapsort: \t\t\t\t\t\t";

    for( int j = 0; j <= 2; ++j )
    {
        for( int i = 1; i <= N; ++i ) V[i] = C[j][i];

        chrono::steady_clock::time_point _start( chrono::steady_clock::now() );

        Heap H;

        H.Sort( V, N );

        chrono::steady_clock::time_point _end( chrono::steady_clock::now() );

        fout << chrono::duration_cast< chrono::milliseconds >( _end - _start).count();
        if( j != 2 ) fout << '\\';
    }
    fout << " ms\n";
}

void Check_Radix()
{
    fout << "Radix LSD, baza 10: \t\t\t";

    for( int j = 0; j <= 2; ++j )
    {
        for( int i = 1; i <= N; ++i ) V[i] = C[j][i];

        chrono::steady_clock::time_point _start( chrono::steady_clock::now() );

        Radix( V );

        chrono::steady_clock::time_point _end( chrono::steady_clock::now() );

        fout << chrono::duration_cast< chrono::milliseconds >( _end - _start).count();
        if( j != 2 ) fout << '\\';
    }

    fout << " ms\n";
}

void Check_Radix_Base( int base )
{
    fout << "Radix LSD, baza 2^" << base << ": \t\t\t";

    for( int j = 0; j <= 2; ++j )
    {
        for( int i = 1; i <= N; ++i ) V[i] = C[j][i];

        chrono::steady_clock::time_point _start( chrono::steady_clock::now() );

        Radix_Base( V, base );

        chrono::steady_clock::time_point _end( chrono::steady_clock::now() );

        fout <<chrono::duration_cast< chrono::milliseconds >( _end - _start).count();
        if( j != 2 ) fout << '\\';
    }
    fout << " ms\n";
}

void Check_STL()
{
    fout << "STL Sort: \t\t\t\t\t\t";

    for( int j = 0; j <= 2; ++j )
    {
        for( int i = 1; i <= N; ++i ) V[i] = C[j][i];

        chrono::steady_clock::time_point _start( chrono::steady_clock::now() );

        sort( V+1, V+N+1 );

        chrono::steady_clock::time_point _end( chrono::steady_clock::now() );

        fout << chrono::duration_cast< chrono::milliseconds >( _end - _start).count();
        if( j != 2 ) fout << '\\';
    }

    fout << " ms\n";
}

void Shuffle( int V[] )
{
    int p1, p2;
    for( int i = 1; i <= N; ++i )
    {
        p1 = random( RandGenerator ) % N + 1;
        p2 = random( RandGenerator ) % N + 1;
        swap( V[p1], V[p2] );
    }
}

void Generate()
{

    fout << "\n\t\t\t Vector Crescator\n\n";

    for( int j = 0; j <= 2; ++j )
        for( int i = 1; i <= N; ++i )
            C[j][i] = C[j][i-1] + random( RandGenerator )%2000;


    if( N <= 10000 ) Check_TreeSort();
    else fout << "TreeSort, Unbalanced BST: \t\tAborted: Case( n^2 )\n";
    Check_HeapSort();
    Check_QS();
    Check_QS_med3();
    Check_Radix();
    Check_Radix_Base( 4 );
    Check_Radix_Base( 10 );
    Check_STL();


    fout << "\n\t\t\t Vector Descrescator\n\n";

    for( int j = 0; j <= 2; ++j )
        for( int i = N; i >= 1; --i )
            C[j][i] = C[j][i+1] + random( RandGenerator )%2000;

    if( N <= 10000 ) Check_TreeSort();
    else fout << "TreeSort, Unbalanced BST: \t\tAborted: Case( n^2 )\n";
    Check_HeapSort();
    Check_QS();
    Check_QS_med3();
    Check_Radix();
    Check_Radix_Base( 4 );
    Check_Radix_Base( 10 );
    Check_STL();


    fout << "\n\t\t\t Vector Munte\n\n";

    for( int j = 0; j <= 2; ++j)
    {
        for( int i = 1; i <= N/2; ++i )
            C[j][i] = C[j][i-1] + random( RandGenerator )%4000;
        for( int i = N; i > N/2; --i )
            C[j][i] = C[j][i+1] + random( RandGenerator )%4000;
    }


    if( N <= 10000 ) Check_TreeSort();
    else fout << "TreeSort, Unbalanced BST: \t\tAborted: Case( n^2 )\n";
    Check_HeapSort();
    Check_QS();
    Check_QS_med3();
    Check_Radix();
    Check_Radix_Base( 4 );
    Check_Radix_Base( 10 );
    Check_STL();


    fout << "\n\t\t\t Vector Aleator\n\n";

    for( int j = 0; j <= 2; ++j )
        for( int i = 1; i <= N; ++i )
            C[j][i] = random( RandGenerator );

    Check_TreeSort();
    Check_HeapSort();
    Check_QS();
    Check_QS_med3();
    Check_Radix();
    Check_Radix_Base( 4 );
    Check_Radix_Base( 10 );
    Check_STL();


    fout << "\n\t\t\t Permutare\n\n";

    for( int j = 0; j <= 2; ++j )
        for( int i = 1; i <= N; ++i )
            C[j][i] = i;

    Shuffle( C[0] );
    Shuffle( C[1] );
    Shuffle( C[2] );


    Check_TreeSort();
    Check_HeapSort();
    Check_QS();
    Check_QS_med3();
    Check_Radix();
    Check_Radix_Base( 4 );
    Check_Radix_Base( 10 );
    Check_STL();

}

int main()
{
    cout << "N: ";
    cin >> N;
    Generate();

    return 0;
}
