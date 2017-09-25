/*
 * File:   NonLinearDE.h
 * Author: nikhilsrajan and satyaprasad
 *
 * Created on September 23, 2017, 1:29 AM
 */

#ifndef NONLINEARDE_H
#define NONLINEARDE_H

#include <iostream>
#include <vector>
#include "AD.h"
#include "NonLinearSystemSolver.h"
#include "SparseMatrix.h"

#define track 0

using namespace std;

template<class T>
class NonLinearDE {
    int numVar;
    var<T> **var_list;
    gNode<T> *U;
    AD<T> A, B, C, D, E;
    int Nx, Ny; // number of spokes cutting the x axis and y axis resp, including the boundaries
    T p, q, r, s, a, b, c, d;
    NonLinearSystemSolver<T> *ns;
    solver<T> *ls;
    SparseMatrix<T> mesh;
    vector<T> *initialGuess;


public:
    NonLinearDE(){};
    NonLinearDE(int, var<T>**, gNode<T>& , AD<T>, AD<T>, AD<T>, AD<T>, AD<T>, T, T, T, T, T, T, T, T, int, int);
    void solveDE(vector<T>* = NULL,  NonLinearSystemSolver<T>* = NULL, solver<T>* = NULL);
    SparseMatrix<T> getSolution(){ return mesh; }
};

template<class T>
NonLinearDE<T> :: NonLinearDE(int numVar, var<T>** variables, gNode<T> &U , AD<T> A, AD<T> B, AD<T> C, AD<T> D, AD<T> E, T p, T q, T r, T s, T a, T b, T c, T d, int Nx, int Ny){
    if(numVar > 2){
        cout<<"Too many variables\n";
        exit(1);
    }

    this->numVar = numVar; // by default
    this->var_list = variables;
    this->U = &U;
    this->A = A; this->B = B; this->C = C; this->D = D; this->E = E;
    this->p = p; this->q = q; this->r = r; this->s = s;
    this->a = a; this->b = b; this->c = c; this->d = d;
    this->Nx = Nx; this->Ny = Ny;
}

template<class T>
void NonLinearDE<T> :: solveDE(vector<T>* initialGuess,  NonLinearSystemSolver<T>* ns, solver<T>* ls){
    if(initialGuess == NULL){
        cout<<"No initial guess vector inputted. Setting default guess as 1.\n";
        int size = (this->Nx-2)*(this->Ny-2);
        this->initialGuess = new vector<T>(size, 1);
    }
    else if((*initialGuess).size() != (this->Nx-2)*(this->Ny-2)){
        cout<<"Initial Guess vector size does not equal number of equations.\n";
        exit(1);
    }
    else
        this->initialGuess = initialGuess;

    var<T> v_mesh[this->Nx][this->Ny];

    for(int i = 0; i<this->Nx; i++){
        v_mesh[i][0] = a;
        v_mesh[i][this->Ny-1] = b;
    }
    for(int j = 0; j<this->Ny; j++){
        v_mesh[0][j] = c;
        v_mesh[this->Nx-1][j] = d;
    }

    int count = 0;

    for(int i = 1; i<this->Nx-1; i++){
        for(int j = 1; j<this->Ny-1; j++){
            v_mesh[i][j] = (*(this->initialGuess))[count++];
        }
    }

    AD<T> *F_list = new AD<T>[(this->Nx-2)*(this->Ny-2)];
    gNode<T> _Ui, _Uj, Ui_, Uj_; // U(i-1, j), U(i, j-1), U(i+1, j), U(i, j+1) respectively
    T h = (q - p)/(this->Nx-1), k = (s - r)/(this->Ny-1);

    count = 0;

    for(int i = 1; i<this->Nx-1; i++){
        for(int j = 1; j<this->Ny-1; j++){
            *(this->var_list[0]) = this->p + i*h;

            if(this->numVar > 1)
                *(this->var_list[1]) = this->r + j*k;

            _Ui = v_mesh[i-1][j];
            _Uj = v_mesh[i][j-1];
            *(this->U) = v_mesh[i][j];
            Ui_ = v_mesh[i+1][j];
            Uj_ = v_mesh[i][j+1];

            T c = 2.0; // to correct type casting problems

            AD<T> C1 = this->A*(Ui_ -c*(*(this->U)) + _Ui)/(h*h);
            AD<T> C2 = this->B*(Uj_ -c*(*(this->U)) + _Uj)/(k*k);
            AD<T> C3 = this->C*(Ui_ - _Ui)/(c*h);
            AD<T> C4 = this->D*(Uj_ - _Uj)/(c*k);

            AD<T> temp = sCopyAD(C1 + C2 + C3 + C4 + this->E);
            F_list[count++] = copyAD(temp);  //Slight Ambiguity, the boundary terms variables instead of scalars
            if(track){
                node<T>* p = F_list[count - 1].geteval();
                p->InOrderTreeWalk();
                cout<<endl;
            }
        }
    }



    if(track){
        cout<<endl;
        for(int i = 0; i<this->Nx; i++){
            for(int j = 0; j<this->Ny; j++){
                VAL<T> v = v_mesh[i][j].getVAL();
                cout<<"U ("<<i<<", "<<j<<") = var("<<v_mesh[i][j].getid()<<") = "<<v.getf()<<endl;
            }
        }
        cout<<endl;
    }

    var<T> **v_linear = new var<T>*[(this->Nx - 2)*(this->Ny - 2)];

    count = 0;

    for(int i = 1; i<this->Nx-1; i++)
        for(int j = 1; j<this->Ny-1; j++)
            v_linear[count++] = &v_mesh[i][j];

    if(ns == NULL){
        cout<<"No Non Linear System Solver chosen. Setting default Non Linear Solver as \"Broyden\".\n";
        if(ls == NULL){
            cout<<"No Linear System Solver chosen. Setting default Non Linear Solver as \"Gauss Elimination\".\n";
            this->ls = new GaussElimination<T>;
        }
        else
            this->ls = ls;

        this->ns = new Broyden<T>((this->Nx-2)*(this->Ny-2), v_linear, *(this->initialGuess), F_list, this->ls);
    }
    else{
        if(ls == NULL){
            cout<<"No Linear System Solver chosen. Setting default Non Linear Solver as \"Gauss Elimination\".\n";
            this->ls = new GaussElimination<T>;
        }
        else
            this->ls = ls;
        this->ns = ns;
        this->ns->input((this->Nx-2)*(this->Ny-2), v_linear, *(this->initialGuess), F_list, this->ls);
    }

    vector<T> solution = this->ns->NonLinearSolve();

    SparseMatrix<T> temp(this->Nx, this->Ny);

    for(int i = 0; i<this->Nx; i++){
        temp(i, 0, a);
        temp(i, this->Ny-1, b);
    }
    for(int j = 0; j<this->Ny; j++){
        temp(0, j, c);
        temp(this->Nx-1, j, d);
    }

    count = 0;

    for(int i = 1; i<this->Nx-1; i++){
        for(int j = 1; j<this->Ny-1; j++){
            temp(i, j, solution[count++]);
        }
    }

    this->mesh = temp;
}
#endif /* NONLINEARDE_H */

