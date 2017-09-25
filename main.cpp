/*
 * File:   main.cpp
 * Author: nikhilsrajan and satyaprasad
 *
 * Created on September 9, 2017, 3:29 PM
 */
#include <iostream>
#include <fstream>
#include "SparseMatrix.h"
#include "NonLinearDE.h"


using namespace std;


int main(){
    AD<double> A,B,C,D,E;
    var<double> x,y;
    gNode<double> U;
    double p, q, r, s, a, b, c, d;
    int Nx, Ny;

    /**Problem 1: 2D DE*/
    p=0; q=1; r=0; s=1; a=0; b=0; c=0; d=0;
    Nx = 11; Ny = 11;

    A = 1;
    B = 1;
    C = 0;
    D = 0;
    E = 2.0;


    /**Problem 2: 1D DE
    (The exceptions are not taken into account, thus has problems)*//*
    p=0; q=2; r=0; s=0; a=0; b=0; c=0; d=0;
    Nx=11; Ny=11;

    A=1;
    B=0;
    C=U;
    D=0;

    E = (U^2.0) - (x^4.0) + 2.0*(x^2.0) - x + 2.0;
    */

    vector<double> InitialGuess((Nx-2)*(Ny-2), 1);


    Broyden<double> BS;
    Gauss_Seidal<double> GS;
    var<double> *varlist[] = {&x};


    NonLinearDE<double> nde(1,varlist,U,A,B,C,D,E,p,q,r,s,a,b,c,d,Nx,Ny);
    nde.solveDE(&InitialGuess, &BS, &GS);

    SparseMatrix<double> Solution = nde.getSolution();
    cout<<endl<<endl<<"Solution:\n";
    Solution.disp();


    /**Transferring into file */
    fstream fileX, fileY, fileZ;
    fileX.open("X.txt", ios::out);
    fileY.open("Y.txt", ios::out);
    fileZ.open("Z.txt", ios::out);
    for(int i = 0; i<Nx; i++){
        for(int j = 0; j<Ny; j++){
            fileX<<(p + i*(q - p)/(Nx - 1))<<"\t";
            fileY<<(r + j*(s - r)/(Ny - 1))<<"\t";
            fileZ<<Solution(i, j)<<"\t";
        }
        fileX<<endl;
        fileY<<endl;
        fileZ<<endl;
    }

    fileX.close();
    fileY.close();
    fileZ.close();

    cout<<"\n\nData transfered to files.\n\n";

    return 0;
}
