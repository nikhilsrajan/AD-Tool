/*
 * File:   NonLinearSystemSolver.h
 * Author: satyaprasad, with modifications from nikhilsrajan
 *
 * Created on September 15, 2017, 3:20 PM
 */
#ifndef NONLINEARSYSTEMSOLVER_H
#define NONLINEARSYSTEMSOLVER_H

#include<iostream>
#include<cmath>
#include<vector>
#include "AD.h"
#include "SparseMatrix.h"
#include "solver.h"

#define Tolerance 0.00001
#define maxItr 50
#define track 1

using namespace std;

template <class T>
class NonLinearSystemSolver {
public:
    virtual void input(int, var<T>**, vector<T>, AD<T>*, solver<T>*) = 0;
   virtual vector<T> NonLinearSolve()=0; //pure virtual function
private:

};

template <class T>
class Newton: public NonLinearSystemSolver<T>{
public:
    Newton(){
        if(track)
            cout<<"Newton Object created\n";
    };
    Newton(int, var<T>**, vector<T>, AD<T>*, solver<T>*);
    void input(int, var<T>**, vector<T>, AD<T>*, solver<T>*);
    vector<T> NonLinearSolve();
    int getNumVar();
    var<T>** getVariables();
    vector<T> getInitialVec();
    AD<T>* getADList();
private:
    int numberOfVariables;
    var<T>** variables;
    vector<T> initialVector;
    AD<T>* functions;
    solver<T>* sol;
};

template <class T>
Newton<T>::Newton(int numVar, var<T>** variables, vector<T> initialVec, AD<T>* functions, solver<T>* s){
    if(track)
        cout<<"Newton Object created\n";
    this->numberOfVariables = numVar;
    this->variables = variables;
    this->initialVector = initialVec;
    this->functions = functions;
    this->sol = s;
    if(track)
        cout<<"Newton Object initialized\n";
}


template <class T>
int Newton<T>::getNumVar(){
    return this->numberOfVariables;
}

template <class T>
var<T>** Newton<T>::getVariables(){
    return this->variables;
}

template <class T>
vector<T> Newton<T>::getInitialVec(){
    return this->initialVector;
}

template <class T>
AD<T>* Newton<T>::getADList(){
    return this->functions;
}
template <class T>
void Newton<T>::input(int numVar, var<T>** variables, vector<T> initialVec, AD<T>* functions, solver<T>* s){
    this->numberOfVariables = numVar;
    this->variables = variables;
    this->initialVector = initialVec;
    this->functions = functions;
    this->sol = s;
    if(track)
        cout<<"Newton Object initialized\n";
}

template <class T>
vector<T> Newton<T>::NonLinearSolve(){
    vector<T> v,funcVector,b;
    SparseMatrix<T> jacob_f(numberOfVariables);
    var<T>** variables = this->getVariables();
    vector<T> initialVec = this->getInitialVec(), oldVec, newVec;
    AD<T>* AD_list = this->getADList();
    vector<T> initialVector;

    for(int k=0; k<=maxItr ;k++){
        cout<<"\nIteration: "<< k+1 <<endl;
        if(track)
            cout<<"*-------------*\n";

        oldVec = initialVec;
        for(int i=0;i < this->getNumVar() ; i++)
            *(variables[i]) = initialVec[i];

        for(int i = 0; i < this->getNumVar() ; i++)
           AD_list[i].reeval();

        jacob_f = jacobian(numberOfVariables, variables, AD_list);
        if(track)
            cout<<"Jacobian created\n";
        funcVector = functionVector(numberOfVariables, AD_list);
        if(track)
            cout<<"Function Vector created\n";
        //jacob_f.disp();
        //cout << "initial vec: \n";
        //disp(initialVec);
        //cout << "\nfunc vector: \n";
        //disp(funcVector);
        b =  (jacob_f * initialVec) - funcVector;
        if(track)
            cout<<"b Vector created\n";
        if(track)
            cout<<"Entering linear solver\n";
        initialVec = sol->solve(jacob_f,b);
        newVec = initialVec;
        //cout<< endl<< "updated solution : \n";
        //disp(initialVec);
        T error = abs(norm(oldVec-newVec));
        cout<<"\nerror = "<<error<<endl;

        if(abs(error)<Tolerance){
            break;
        }
        else if(k==50){
            cout<<"Solution Diverges!"<<endl;
            exit(1);
        }

    }

    return newVec;
}

//Broydens Method

template <class T>
class Broyden : public NonLinearSystemSolver<T>{
public:
    Broyden(){
        if(track)
            cout<<"Broyden Object created\n";
    };
    Broyden(int, var<T>**, vector<T>, AD<T>*, solver<T>*);
    void input(int, var<T>**, vector<T>, AD<T>*, solver<T>*);
    vector<T> NonLinearSolve();
    int getNumVar();
    var<T>** getVariables();
    vector<T> getInitialVec();
    AD<T>* getADList();
private:
    int numberOfVariables;
    var<T>** variables;
    vector<T> initialVector;
    AD<T>* functions;
    solver<T>* sol;
};

template <class T>
Broyden<T>::Broyden(int numVar, var<T>** variables, vector<T> initialVec, AD<T>* functions, solver<T>* s){
    if(track)
        cout<<"Broyden Object created\n";
    this->numberOfVariables = numVar;
    this->variables = variables;
    this->initialVector = initialVec;
    this->functions = functions;
    this->sol = s;
    if(track)
        cout<<"Broyden Object Initialized\n";
}


template <class T>
int Broyden<T>::getNumVar(){
    return this->numberOfVariables;
}

template <class T>
var<T>** Broyden<T>::getVariables(){
    return this->variables;
}

template <class T>
vector<T> Broyden<T>::getInitialVec(){
    return this->initialVector;
}

template <class T>
AD<T>* Broyden<T>::getADList(){
    return this->functions;
}

template <class T>
void Broyden<T>::input(int numVar, var<T>** variables, vector<T> initialVec, AD<T>* functions, solver<T>* s){
    this->numberOfVariables = numVar;
    this->variables = variables;
    this->initialVector = initialVec;
    this->functions = functions;
    this->sol = s;
    if(track)
        cout<<"Broyden Object initialized\n";
}

template <class T>
vector<T> Broyden<T>::NonLinearSolve(){
    vector<T> v,oldfuncVector,newfuncVector,b,tempvec;
    SparseMatrix<T> jacob_f(numberOfVariables);
    var<T>** variables = this->getVariables();
    vector<T> initialVec = this->getInitialVec(), oldVec, newVec;
    AD<T>* AD_list = this->getADList();
    vector<T> initialVector;

    for(int i=0;i < this->getNumVar() ; i++){  //assign initial values.
        *(variables[i]) = initialVec[i];
    }
    for(int i = 0; i < this->getNumVar() ; i++){
        AD_list[i].reeval();
    }
    jacob_f = jacobian(numberOfVariables, variables, AD_list);
    if(track)
        cout<<"Jacobian created\n";

    for(int k=0; k<=maxItr ;k++){
        cout<<endl<<"\nIteration: "<< k+1 <<endl;
        if(track)
            cout<<"*-------------*\n";

        oldVec = initialVec;
        oldfuncVector = functionVector(numberOfVariables, AD_list);
        if(track)
            cout<<"Function Vector created\n";
        //jacob_f.disp();
        //cout << "initial vec: ";
        //disp(initialVec);
        //cout << "func vector: ";
        //disp(oldfuncVector);
        b =  jacob_f * initialVec - oldfuncVector;
        if(track)
            cout<<"b Vector created\n";
        if(track)
            cout<<"Entering linear solver\n";
        initialVec = sol->solve(jacob_f,b);
        newVec = initialVec;
        //cout<< endl<< "updated solution : ";
        //disp(initialVec);

        for(int i=0;i < this->getNumVar() ; i++){  //assign initial values.
            *(variables[i]) = initialVec[i];
        }
        if(track)
            cout<<"Variable values updated\n";

        for(int i = 0; i < this->getNumVar() ; i++)
           AD_list[i].reeval();
        if(track)
            cout<<"Function values reevaluated\n";

        newfuncVector = functionVector(numberOfVariables, AD_list);

        tempvec = ((newfuncVector - oldfuncVector) - jacob_f * (oldVec - newVec)/(norm(newVec)*norm(newVec)));
        jacob_f = jacob_f + tempvec * (oldVec - newVec);

        if(track)
            cout<<"Jacobian Matrix updated\n";

        T error = abs(norm(oldVec-newVec));
        cout<<"\nerror = "<<error<<endl;


         if(abs(error)<Tolerance){
             break;
         }
         else if(k==50){
             cout<<"Solution Diverges"<<endl;
             exit(1);
        }
    }

    return newVec;
}

#endif /* NONLINEARSYSTEMSOLVER_H */

