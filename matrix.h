#include<iostream>
#include<cmath>
#include<cstdlib>

using namespace std;

template<class T>
class matrix
{
    T **a;
    int rsize,csize;
public:
    matrix ()
    {

    }
    matrix (int, int);
    void input ();
    void disp ();
    matrix<T> operator+ (matrix<T>);
    matrix<T> operator- (matrix<T>);
    matrix<T> operator* (matrix<T>);
    template<class U>
    friend int row_size (matrix<U>);
    template<class U>
    friend int col_size (matrix<U>);
    T& operator () (int, int);
};

template<class T>
matrix<T>::matrix (int x, int y)
{
    rsize = x;
    csize = y;
    a = new T *[rsize];
    for(int i=0;i<rsize;i++)
        a[i] = new T[csize];
}

template<class T>
void matrix<T>::input ()
{
    cout << "Enter the size of the coefficient Matrix:" << endl;
    cin >> rsize >> csize;
    a = new T *[rsize];
    for(int i=0;i<rsize;i++)
        a[i] = new T[csize];
    cout << "Enter the elements row wise" << endl;
    for(int i=0;i<rsize;i++)
    {
        for(int j=0;j<csize;j++)
            cin >> a[i][j];
    }
}

template<class T>
void matrix<T>::disp ()
{
    for(int i=0;i<rsize;i++)
    {
        for(int j=0;j<csize;j++)
            cout << a[i][j] << "\t";
        cout << endl;
    }
}

template<class T>
matrix<T> matrix<T>::operator+ (matrix<T> M)
{
    matrix<T> P;
    if(rsize != M.rsize || csize != M.csize)
    {
        cout << "Matrix addition is invalid\n";
        exit(0);
    }
    else
    {
        P = matrix<T> (rsize, csize);
        for(int i=0;i<rsize;i++)
            for(int j=0;j<csize;j++)
                P.a[i][j] = a[i][j] + M.a[i][j];
        return P;
    }
}

template<class T>
matrix<T> matrix<T>::operator- (matrix<T> M)
{
    matrix<T> P;
    if(rsize != M.rsize || csize != M.csize)
    {
        cout << "Matrix addition is invalid\n";
        exit(0);
    }
    else
    {
        P = matrix<T> (rsize, csize);
        for(int i=0;i<rsize;i++)
            for(int j=0;j<csize;j++)
                P.a[i][j] = a[i][j] - M.a[i][j];
        return P;
    }
}

template<class T>
matrix<T> matrix<T>::operator* (matrix<T> M)
{
    matrix<T> P;
    if (csize != M.rsize)
    {
        cout << "Invalid matrix multiplication ! \n";
        exit(0);
    }
    else
    {
        P = matrix<T> (rsize, M.csize);
        for(int i=0;i<rsize;i++)
            for(int j=0;j<M.csize;j++)
            {
                P.a[i][j]=0.0;
                for(int k=0;k<csize;k++)
                    P.a[i][j] = P.a[i][j] + a[i][k]*M.a[k][j];
            }
        return P;
    }
}

template<class T>
int row_size (matrix<T> M)
{
    return M.rsize;
}

template<class T>
int col_size (matrix<T> M)
{
    return M.csize;
}

template<class T>
T& matrix<T>::operator () (int x, int y)
{
    if (x<rsize && y<csize)
        return a[x][y];
    else
    {
        cout << "Index out of bound !" << endl;
        exit(0);
    }
}
