/*
 * File:   AD.h
 * Author: nikhilsrajan, with modifications from satyaprasad
 *
 * Created on September 11, 2017, 1:18 AM
 */

/** Make changes in the code to take care of intermediate variable inclusion!! */
#ifndef AD_H
#define AD_H

#include <iostream>
#include <cmath>
#include <vector>
#include "SparseMatrix.h"

static int idc = 0;

using namespace std;

template <class T>
class VAL;

template<class T>
class AD;

/**CLASS: node ***************************************/
template<class T>
class node{
    node *Lchild, *Rchild;

public:
    node(){ Lchild = NULL; Rchild = NULL; }
    virtual VAL<T> getVAL() = 0;
    virtual node<T>* getself() = 0;
    virtual void disp() = 0;
    virtual char gettype() = 0;
    virtual node<T>* clone() = 0;

    void InOrderTreeWalk();

    void setLchild(node *p){ this->Lchild = p; }
    void setRchild(node *p){ this->Rchild = p; }

    node<T>* getLchild(){ return this->Lchild; }
    node<T>* getRchild(){ return this->Rchild; }

    VAL<T> getleftVAL(){ return Lchild->getVAL(); }
    VAL<T> getrightVAL(){ return Rchild->getVAL(); }
};

template<class T>
void node<T>::InOrderTreeWalk(){
    if(this->Lchild != NULL){
        cout<<"LEFT: ";
        this->Lchild->InOrderTreeWalk();
    }

    cout<<"THIS ";
    cout<<" ["<<this->gettype()<<"] : ";
    this->disp();

    if(this->Rchild != NULL){
        cout<<"RGHT: ";
        this->Rchild->InOrderTreeWalk();
    }
}

/**CLASS: scalar ***************************************/
template<class T>
class scalar:public node<T>{
    T val;
    scalar<T>* self;
    char type;

public:
    scalar(){ this->self = this; this->type = 's'; }
    scalar(T k){ this->val = k; this->self = this; this->type = 's'; }

    T getval(){ return val; }

    void operator =(T k){ this->val = k; }
    void operator =(scalar<T> s){ this->val = s.val; }

    void disp(){
        cout<<"SCALAR: val = "<<this->val<<", address = "<<this->self<<endl;
    }
    node<T>* clone(){ return this; }
    scalar<T>* getself(){ return this->self; }
    char gettype(){ return this->type; }
    VAL<T> getVAL();
};

template<class T>
VAL<T> scalar<T>::getVAL(){
    VAL<T> v;
    v.input_f(this->val);
    T *df = new T[idc];

    for(int i = 0; i<idc; i++)
        df[i] = 0.0;

    v.input_df(df);

    return v;
}


/**CLASS: var ***************************************/
template<class T>
class var:public node<T>{
    int id;
    T val;
    var<T>* self;
    char type;

public:
    var(){ this->id = idc++; this->self = this; this->type = 'v'; }
    var(T k){ this->id = idc++; this->val = k; this->self = this; this->type = 'v'; }

    void operator =(T k){ this->val = k; }
    void operator =(scalar<T> s){ this->p = s.getval(); }
    void operator =(var<T> x){ this->val = x.val; }

    int getid(){ return id; }

    void disp(){
        cout<<"VAR: id = "<<this->id<<", val = "<<this->val<<", address = "<<this->self<<endl;
    }
    node<T>* clone(){ return this; }
    var<T>* getself(){ return this->self; }
    char gettype(){ return this->type; }
    VAL<T> getVAL();
};

template<class T>
VAL<T> var<T>::getVAL(){
    VAL<T> v;
    v.input_f(this->val);
    T *df = new T[idc];

    for(int i = 0; i<this->id; i++)
        df[i] = 0.0;

    df[this->id] = 1.0;

    for(int i = this->id+1; i<idc; i++)
        df[i] = 0.0;

    v.input_df(df);

    return v;
}


/**CLASS: OP ***************************************/
template<class T>
class OP:public node<T>{
    OP* self;
    char op, type;

public:
    OP(){ this->op = '\0'; this->self = this; this->type = 'o'; }
    OP(char ch){ this->op = ch; this->self = this; this->type = 'o'; }
    OP(char ch, node<T> *L){ this->op = ch; this->setLchild(L); this->self = this; this->type = 'o'; }
    OP(char ch, node<T> *L, node<T> *R){ this->op = ch; this->setLchild(L); this->setRchild(R); this->self = this; this->type = 'o'; }
    OP(OP<T> &O){ this->op = O.op; this->setLchild(O.getLchild()); this->setRchild(O.getRchild()); this->self = this; this->type = 'o'; }

    void operator =(OP<T> O){ this->op = O.op; this->setLchild(O.getLchild()); this->setRchild(O.getRchild()); }

    OP<T>* getself(){ return this->self; }
    char gettype(){ return this->type; }

    node<T>* clone(){ return new OP<T>(*this); }

    void disp(){
        cout<<"OP: op = "<<this->op<<", address = "<<this->self<<endl;
    }

    VAL<T> getVAL();
};

template<class T>
VAL<T> OP<T>::getVAL(){
    VAL<T> v;
    switch(this->op){
        case '+':
            if(this->getRchild() == NULL)
                v = this->getleftVAL();
            else
                v = this->getleftVAL() + this->getrightVAL();
            break;
        case '-':
            if(this->getRchild() == NULL)
                v = -(this->getleftVAL());
            else
                v = this->getleftVAL() - this->getrightVAL();
            break;
        case '*': v = this->getleftVAL() * this->getrightVAL(); break;
        case '/': v = this->getleftVAL() / this->getrightVAL(); break;
        case '^': v = this->getleftVAL() ^ this->getrightVAL(); break;
        default: cout<<"ERROR: Invalid Operator.\n"; exit(1); break;
    }
    return v;
}


/**CLASS: gNode ***************************************/
template<class T>
class gNode:public node<T>{
    node<T> *p, *self;
    char type;
public:
    gNode(){ this->p = NULL; this->self = this; this->type = 'g'; }
    gNode(node<T>* P){ this->p = P; this->self = this; this->type = 'g'; }

    void operator =(T k){ this->p = new scalar<T>(k); }
    void operator =(scalar<T> s){ this->p = s.getself(); }
    void operator =(var<T> x){ this->p = x.getself(); }
    void operator =(OP<T> O){ this->p = O.getself(); }
    void operator =(AD<T> G){ this->p = G.geteval(); }
    void operator =(gNode<T> g){ this->p = g.p; }

    void setNodePointer(node<T> *new_p){ this->p = new_p; }
    node<T>* getNodePointer(){ return this->p; }

    node<T>* clone(){ return this->p; }
    VAL<T> getVAL(){
        if(this->p != NULL)
            return this->p->getVAL();
        else{
            VAL<T> V(0);
            return V;
        }
    }
    node<T>* getself(){ return this->self; }
    void disp(){ this->p->disp(); }
    char gettype(){ return this->type; }
};


/**CLASS: VAL ***************************************/
template <class T>
class VAL{
    T f;
    T * df;
public:
    VAL();
    VAL(T k){
        this->f = k;
        this->df = new T[idc];

        for(int i = 0; i<idc; i++)
            this->df[i] = 0.0;

    }
    VAL(T k, int id){
        this->f = k;
        this->df = new T[idc];

        for(int i = 0; i<id; i++)
            this->df[i] = 0.0;

        this->df[id] = 1.0;

        for(int i = id+1; i<idc; i++)
            this->df[i] = 0.0;
    }

    void disp(){
        cout<<"f = "<<this->f<<endl;
        cout<<"df = ";
        for(int i = 0; i<idc; i++)
            cout<<this->df[i]<<"   ";
        cout<<endl;
    }

    void input_f(T k){ this->f = k; }
    void input_df(T* dk){ this->df = dk; }

    T getf(){ return f; }

    T& operator [] (int);

    /**Member Functions*/
    /**Unary operators*/
    VAL operator +(); //defined
    VAL operator -(); //defined

    /**Binary operators*/
    void operator =(VAL); // defined
    VAL operator +(VAL); // defined
    VAL operator -(VAL); // defined
    VAL operator *(VAL); // defined
    VAL operator /(VAL); // defined
    VAL operator ^(VAL); // defined
};

template<class T>
VAL<T>::VAL(){
    this->f = 0.0;
    this->df = new T[idc];

    for(int i = 0; i<idc; i++)
        this->df[i] = 0.0;
}

template<class T>
T& VAL<T>::operator [] (int k){
    if (k<idc)
        return df[k];
    else{
        cout << "Index out of bound!";
        exit(1);
    }
}

/**VAL: Operator Overloading*/
template<class T>
void VAL<T>::operator =(VAL g){
    this->f = g.f;
    for(int i = 0; i<idc; i++)
        this->df[i] = g.df[i];
}

template<class T>
VAL<T> VAL<T>::operator +(){
    VAL<T> h;
    h.f = f;
    for(int i = 0; i<idc; i++)
        h.df[i] = this->df[i];
    return h;
}

template<class T>
VAL<T> VAL<T>::operator -(){
    VAL<T> h;
    h.f = -(this->f);
    for(int i = 0; i<idc; i++)
        h.df[i] = -(this->df[i]);
    return h;
}

template<class T>
VAL<T> VAL<T>::operator +(VAL g){
    VAL<T> h;
    h.f = this->f + g.f;
    for(int i = 0; i<idc; i++)
        h.df[i] = this->df[i] + g.df[i];
    return h;
}

template<class T>
VAL<T> VAL<T>::operator -(VAL g){
    VAL<T> h;
    h.f = this->f - g.f;
    for(int i = 0; i<idc; i++)
        h.df[i] = this->df[i] - g.df[i];
    return h;
}

template<class T>
VAL<T> VAL<T>::operator *(VAL g){
    VAL<T> h;
    h.f = this->f*g.f;
    for(int i = 0; i<idc; i++)
        h.df[i] = g.f*(this->df[i]) + this->f*g.df[i];
    return h;
}

template<class T>
VAL<T> VAL<T>::operator /(VAL g){
    if(g.f == 0){
        cout<<"MATH ERROR: Division by Zero!\n";
        exit(1);
    }
    else{
        VAL<T> h;
        h.f = this->f/g.f;
        for(int i = 0; i<idc; i++)
            h.df[i] = this->df[i]/g.f - this->f*g.df[i]/(g.f*g.f);
        return h;
    }
}

template<class T>
VAL<T> VAL<T>::operator ^(VAL g){
    VAL<T> h;
    if(this->f == 0 && g.f == 0){
        cout<<"MATH ERROR: 0^0 Undefined!\n";
        exit(1);
    }
    else if(this->f == 0 && g.f < 0){
        cout<<"MATH ERROR: Division by Zero!\n";
        exit(1);
    }
    else
        h.f = pow(this->f, g.f);

    int g_df = 0;

    for(int i = 0; i<idc && g_df == 0; i++)
        if(g.df[i] != 0)
            g_df = 1;

    if(g_df == 0){
        if(this->f != 0){
            for(int i = 0; i<idc; i++)
                h.df[i] = pow(this->f, (g.f - 1))*g.f*this->df[i];
        }
        else if(g.f > 1){
            for(int i = 0; i<idc; i++)
                h.df[i] = 0.0;
        }
        else{
            cout<<"MATH ERROR: Division by Zero!\n";
            exit(1);
        }
    }
    else if(this->f > 0){
        for(int i = 0; i<idc; i++)
            h.df[i] = pow(this->f, (g.f - 1))*g.f*this->df[i] + pow(this->f, g.f)*g.df[i]*log(this->f);
    }
    else{
        cout<<"MATH ERROR: LOG undefined for values <= 0!\n";
        exit(1);
    }
    return h;
}


/**CLASS: AD ***************************************/
template<class T>
class AD{
    VAL<T> val;
    node<T> *eval;

public:
    AD(){ this->eval = NULL; }

    void disp(int = 0);

    void reeval();

    void operator =(T);
    void operator =(var<T>);
    void operator =(AD<T>);
    void operator =(gNode<T>);

    void setval(VAL<T> v){ val = v; }
    void seteval(node<T>* ev){ eval = ev; }

    VAL<T> getval(){ return val; }
    node<T>* geteval(){ return eval; }

    template<class U>
    friend AD<U> copyAD(AD<U>);

    template<class U>
    friend AD<U> sCopyAD(AD<U>);

    /**Math operators */
    AD<T> operator +(); //defined
    AD<T> operator -(); //defined

    template<class U>
    friend AD<U> operator +(var<U>);
    template<class U>
    friend AD<U> operator -(var<U>);

    template<class U>
    friend AD<U> operator +(gNode<U>);
    template<class U>
    friend AD<U> operator -(gNode<U>);

    AD<T> operator +(T); //defined
    AD<T> operator -(T); //defined
    AD<T> operator *(T); //defined
    AD<T> operator /(T); //defined
    AD<T> operator ^(T); //defined

    AD<T> operator +(var<T>); //defined
    AD<T> operator -(var<T>); //defined
    AD<T> operator *(var<T>); //defined
    AD<T> operator /(var<T>); //defined
    AD<T> operator ^(var<T>); //defined

    AD<T> operator +(AD<T>); //defined
    AD<T> operator -(AD<T>); //defined
    AD<T> operator *(AD<T>); //defined
    AD<T> operator /(AD<T>); //defined
    AD<T> operator ^(AD<T>); //defined

    AD<T> operator +(gNode<T>); //defined
    AD<T> operator -(gNode<T>); //defined
    AD<T> operator *(gNode<T>); //defined
    AD<T> operator /(gNode<T>); //defined
    AD<T> operator ^(gNode<T>); //defined

    template<class U>
    friend AD<U> operator +(U, var<U>); //defined
    template<class U>
    friend AD<U> operator -(U, var<U>); //defined
    template<class U>
    friend AD<U> operator *(U, var<U>); //defined
    template<class U>
    friend AD<U> operator /(U, var<U>); //defined
    template<class U>
    friend AD<U> operator ^(U, var<U>); //defined

    template<class U>
    friend AD<U> operator +(U, AD<U>); //defined
    template<class U>
    friend AD<U> operator -(U, AD<U>); //defined
    template<class U>
    friend AD<U> operator *(U, AD<U>); //defined
    template<class U>
    friend AD<U> operator /(U, AD<U>); //defined
    template<class U>
    friend AD<U> operator ^(U, AD<U>); //defined

    template<class U>
    friend AD<U> operator +(U, gNode<U>); //defined
    template<class U>
    friend AD<U> operator -(U, gNode<U>); //defined
    template<class U>
    friend AD<U> operator *(U, gNode<U>); //defined
    template<class U>
    friend AD<U> operator /(U, gNode<U>); //defined
    template<class U>
    friend AD<U> operator ^(U, gNode<U>); //defined

    template<class U>
    friend AD<U> operator +(var<U>, U); //defined
    template<class U>
    friend AD<U> operator -(var<U>, U); //defined
    template<class U>
    friend AD<U> operator *(var<U>, U); //defined
    template<class U>
    friend AD<U> operator /(var<U>, U); //defined
    template<class U>
    friend AD<U> operator ^(var<U>, U); //defined

    template<class U>
    friend AD<U> operator +(var<U>, var<U>); //defined
    template<class U>
    friend AD<U> operator -(var<U>, var<U>); //defined
    template<class U>
    friend AD<U> operator *(var<U>, var<U>); //defined
    template<class U>
    friend AD<U> operator /(var<U>, var<U>); //defined
    template<class U>
    friend AD<U> operator ^(var<U>, var<U>); //defined

    template<class U>
    friend AD<U> operator +(var<U>, AD<U>); //defined
    template<class U>
    friend AD<U> operator -(var<U>, AD<U>); //defined
    template<class U>
    friend AD<U> operator *(var<U>, AD<U>); //defined
    template<class U>
    friend AD<U> operator /(var<U>, AD<U>); //defined
    template<class U>
    friend AD<U> operator ^(var<U>, AD<U>); //defined

    template<class U>
    friend AD<U> operator +(var<U>, gNode<U>); //defined
    template<class U>
    friend AD<U> operator -(var<U>, gNode<U>); //defined
    template<class U>
    friend AD<U> operator *(var<U>, gNode<U>); //defined
    template<class U>
    friend AD<U> operator /(var<U>, gNode<U>); //defined
    template<class U>
    friend AD<U> operator ^(var<U>, gNode<U>); //defined

    template<class U>
    friend AD<U> operator +(gNode<U>, U); //defined
    template<class U>
    friend AD<U> operator -(gNode<U>, U); //defined
    template<class U>
    friend AD<U> operator *(gNode<U>, U); //defined
    template<class U>
    friend AD<U> operator /(gNode<U>, U); //defined
    template<class U>
    friend AD<U> operator ^(gNode<U>, U); //defined

    template<class U>
    friend AD<U> operator +(gNode<U>, var<U>); //defined
    template<class U>
    friend AD<U> operator -(gNode<U>, var<U>); //defined
    template<class U>
    friend AD<U> operator *(gNode<U>, var<U>); //defined
    template<class U>
    friend AD<U> operator /(gNode<U>, var<U>); //defined
    template<class U>
    friend AD<U> operator ^(gNode<U>, var<U>); //defined

    template<class U>
    friend AD<U> operator +(gNode<U>, AD<U>); //defined
    template<class U>
    friend AD<U> operator -(gNode<U>, AD<U>); //defined
    template<class U>
    friend AD<U> operator *(gNode<U>, AD<U>); //defined
    template<class U>
    friend AD<U> operator /(gNode<U>, AD<U>); //defined
    template<class U>
    friend AD<U> operator ^(gNode<U>, AD<U>); //defined

    template<class U>
    friend AD<U> operator +(gNode<U>, gNode<U>); //defined
    template<class U>
    friend AD<U> operator -(gNode<U>, gNode<U>); //defined
    template<class U>
    friend AD<U> operator *(gNode<U>, gNode<U>); //defined
    template<class U>
    friend AD<U> operator /(gNode<U>, gNode<U>); //defined
    template<class U>
    friend AD<U> operator ^(gNode<U>, gNode<U>); //defined

    /**Advanced operations*/
    template<class U>
    friend vector<U> functionVector(int, AD<U>*);

    /**Gradient*/
    template <class U>
    friend vector<T> grad(int, var<T>**, AD<U>);

    /**Jacobian*/
    template <class U>
    friend SparseMatrix<U> jacobian(int, var<U>**, AD<U>*);
};

template<class T>
AD<T> copyAD(AD<T> G){
    AD<T> H;
    H.val = G.val;
    H.eval = cloneNode(G.eval);
    return H;
}

template<class T>
node<T>* cloneNode(node<T>* root){
    switch(root->gettype()){
        case 's': return root; break;
        case 'v': return root; break;
        case 'g': return cloneNode(root->clone()); break;
        case 'o': {
            node<T> *O = root->clone();
            O->setLchild(cloneNode(O->getLchild()));
            O->setRchild(cloneNode(O->getRchild()));
            return O;
            break;
        }
        default :
            cout<<"no such case exist!";
            exit(1);

    }
}

template<class T>
AD<T> sCopyAD(AD<T> G){
    AD<T> H;
    H.val = G.val;
    H.eval = sCloneNode(G.eval);
    return H;
}

template<class T>
node<T>* sCloneNode(node<T>* root){
    switch(root->gettype()){
        case 's': return root; break;
        case 'v':{
            VAL<T> val = root->getVAL();
            scalar<T> *s = new scalar<T>(val.getf());
            return s;
            break;
        }
        case 'g': return root; break;
        case 'o':{
            node<T> *O = root->clone();
            O->setLchild(sCloneNode(O->getLchild()));
            O->setRchild(sCloneNode(O->getRchild()));
            return O;
            break;
        }
        default :
            cout<<"No such case exist!";
            exit(1);
    }
}

template<class T>
void AD<T>::disp(int type){
    switch(type){
        case 0: this->val.disp(); break;
        case 1: this->eval->InOrderTreeWalk(); break;
        case 2: this->val.disp(); this->eval->InOrderTreeWalk(); break;
    }
}

template<class T>
void AD<T>::reeval(){
    if(this->eval != NULL)
        this->val = eval->getVAL();
}

/**Assignment operators */
template<class T>
void AD<T>::operator =(T k){
    scalar<T> *s = new scalar<T>(k);
    this->val = s->getVAL();
    this->eval = s;
}

template<class T>
void AD<T>::operator =(var<T> x){
    this->val = x.getVAL();
    this->eval = x.getself();
}

template<class T>
void AD<T>::operator =(AD<T> G){
    this->val = G.val;
    this->eval = G.eval;
}

template<class T>
void AD<T>::operator =(gNode<T> g){
    if(g.getNodePointer() == NULL)
    this->val = g.getVAL();
    this->eval = g.getself();
}

/**unary(AD) */
template<class T>
AD<T> AD<T>::operator +(){
    AD<T> H;

    H.val = this->val;
    OP<T> *O = new OP<T>('+', this->eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator -(){
    AD<T> H;

    H.val = -(this->val);
    OP<T> *O = new OP<T>('-', this->eval);

    H.eval = O;
    return H;
}

/**unary(T) - NOT ALLOWED! */

/**unary(var) */
template<class T>
AD<T> operator +(var<T> x){
    AD<T> H;

    H.val = x.getVAL();
    OP<T> *O = new OP<T>('+', x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(var<T> x){
    AD<T> H;

    H.val = -x.getVAL();
    OP<T> *O = new OP<T>('-', x.getself());

    H.eval = O;
    return H;
}

/**unary(gNode) */
template<class T>
AD<T> operator +(gNode<T> g){
    AD<T> H;

    H.val = g.getVAL();
    OP<T> *O = new OP<T>('+', g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(gNode<T> g){
    AD<T> H;

    H.val = -g.getVAL();
    OP<T> *O = new OP<T>('-', g.getself());

    H.eval = O;
    return H;
}

/**binary(AD, T) */
template<class T>
AD<T> AD<T>::operator +(T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = this->val + s->getVAL();

    OP<T> *O = new OP<T>('+', this->eval, s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator -(T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = this->val - s->getVAL();

    OP<T> *O = new OP<T>('-', this->eval, s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator *(T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);


    H.val = this->val * s->getVAL();

    OP<T> *O = new OP<T>('*', this->eval, s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator /(T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = this->val / s->getVAL();

    OP<T> *O = new OP<T>('/', this->eval, s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator ^(T k){
    AD<T> H;
    scalar<T>*s = new scalar<T>(k);

    H.val = this->val ^ s->getVAL();

    OP<T> *O = new OP<T>('^', this->eval, s);

    H.eval = O;
    return H;
}

/**binary(AD, var) */
template<class T>
AD<T> AD<T>::operator +(var<T> x){
    AD<T> H;

    H.val = this->val + x.getVAL();

    OP<T> *O = new OP<T>('+', this->eval, x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator -(var<T> x){
    AD<T> H;

    H.val = this->val - x.getVAL();

    OP<T> *O = new OP<T>('-', this->eval, x.getself());

    H.eval = O;
    return H;
}


template<class T>
AD<T> AD<T>::operator *(var<T> x){
    AD<T> H;

    H.val = this->val * x.getVAL();

    OP<T> *O = new OP<T>('*', this->eval, x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator /(var<T> x){
    AD<T> H;

    H.val = this->val / x.getVAL();

    OP<T> *O = new OP<T>('/', this->eval, x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator ^(var<T> x){
    AD<T> H;

    H.val = this->val ^ x.getVAL();

    OP<T> *O = new OP<T>('^', this->eval, x.getself());

    H.eval = O;
    return H;
}

/**binary(AD, AD) */
template<class T>
AD<T> AD<T>::operator +(AD<T> G){
    AD<T> H;

    H.val = this->val + G.val;

    OP<T> *O = new OP<T>('+', this->eval, G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator -(AD<T> G){
    AD<T> H;

    H.val = this->val - G.val;

    OP<T> *O = new OP<T>('-', this->eval, G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator *(AD<T> G){
    AD<T> H;

    H.val = this->val * G.val;

    OP<T> *O = new OP<T>('*', this->eval, G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator /(AD<T> G){
    AD<T> H;

    H.val = this->val / G.val;

    OP<T> *O = new OP<T>('/', this->eval, G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator ^(AD<T> G){
    AD<T> H;

    H.val = this->val ^ G.val;

    OP<T> *O = new OP<T>('^', this->eval, G.eval);

    H.eval = O;
    return H;
}

/**binary(AD, gNode) */
template<class T>
AD<T> AD<T>::operator +(gNode<T> g){
    AD<T> H;

    H.val = this->val + g.getVAL();

    OP<T> *O = new OP<T>('+', this->eval, g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator -(gNode<T> g){
    AD<T> H;

    H.val = this->val - g.getVAL();

    OP<T> *O = new OP<T>('-', this->eval, g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator *(gNode<T> g){
    AD<T> H;

    H.val = this->val * g.getVAL();

    OP<T> *O = new OP<T>('*', this->eval, g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator /(gNode<T> g){
    AD<T> H;

    H.val = this->val / g.getVAL();

    OP<T> *O = new OP<T>('/', this->eval, g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> AD<T>::operator ^(gNode<T> g){
    AD<T> H;

    H.val = this->val ^ g.getVAL();

    OP<T> *O = new OP<T>('^', this->eval, g.getself());

    H.eval = O;
    return H;
}

/**binary(T, T) - NOT ALLOWED! */

/**binary(T, var) */
template<class T>
AD<T> operator +(T k, var<T> x){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() + x.getVAL();

    OP<T> *O = new OP<T>('+', s, x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(T k, var<T> x){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() - x.getVAL();

    OP<T> *O = new OP<T>('-', s, x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator *(T k, var<T> x){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() * x.getVAL();

    OP<T> *O = new OP<T>('*', s, x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator /(T k, var<T> x){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() / x.getVAL();

    OP<T> *O = new OP<T>('/', s, x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator ^(T k, var<T> x){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() ^ x.getVAL();

    OP<T> *O = new OP<T>('^', s, x.getself());

    H.eval = O;
    return H;
}

/**binary(T, AD) */
template<class T>
AD<T> operator +(T k, AD<T> G){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() + G.val;

    OP<T> *O = new OP<T>('+', s, G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(T k, AD<T> G){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() - G.val;

    OP<T> *O = new OP<T>('-', s, G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator *(T k, AD<T> G){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() * G.val;

    OP<T> *O = new OP<T>('*', s, G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator /(T k, AD<T> G){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() / G.val;

    OP<T> *O = new OP<T>('/', s, G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator ^(T k, AD<T> G){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() ^ G.val;

    OP<T> *O = new OP<T>('^', s, G.eval);

    H.eval = O;
    return H;
}

/**binary(T, gNode) */
template<class T>
AD<T> operator +(T k, gNode<T> g){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() + g.getVAL();

    OP<T> *O = new OP<T>('+', s, g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(T k, gNode<T> g){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() - g.getVAL();

    OP<T> *O = new OP<T>('-', s, g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator *(T k, gNode<T> g){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() * g.getVAL();

    OP<T> *O = new OP<T>('*', s, g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator /(T k, gNode<T> g){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() / g.getVAL();

    OP<T> *O = new OP<T>('/', s, g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator ^(T k, gNode<T> g){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = s->getVAL() ^ g.getVAL();

    OP<T> *O = new OP<T>('^', s, g.getself());

    H.eval = O;
    return H;
}

/**binary(var, T) */
template<class T>
AD<T> operator +(var<T> x, T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = x.getVAL() + s->getVAL();

    OP<T> *O = new OP<T>('+', x.getself(), s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(var<T> x, T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = x.getVAL() - s->getVAL();

    OP<T> *O = new OP<T>('-', x.getself(), s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator *(var<T> x, T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = x.getVAL() * s->getVAL();

    OP<T> *O = new OP<T>('*', x.getself(), s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator /(var<T> x, T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = x.getVAL() / s->getVAL();

    OP<T> *O = new OP<T>('/', x.getself(), s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator ^(var<T> x, T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = x.getVAL() ^ s->getVAL();

    OP<T> *O = new OP<T>('^', x.getself(), s);

    H.eval = O;
    return H;
}

/**binary(var, var) */
template<class T>
AD<T> operator +(var<T> x, var<T> y){
    AD<T> H;

    H.val = x.getVAL() + y.getVAL();

    OP<T> *O = new OP<T>('+', x.getself(), y.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(var<T> x, var<T> y){
    AD<T> H;

    H.val = x.getVAL() - y.getVAL();

    OP<T> *O = new OP<T>('-', x.getself(), y.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator *(var<T> x, var<T> y){
    AD<T> H;

    H.val = x.getVAL() * y.getVAL();

    OP<T> *O = new OP<T>('*', x.getself(), y.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator /(var<T> x, var<T> y){
    AD<T> H;

    H.val = x.getVAL() / y.getVAL();

    OP<T> *O = new OP<T>('/', x.getself(), y.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator ^(var<T> x, var<T> y){
    AD<T> H;

    H.val = x.getVAL() ^ y.getVAL();

    OP<T> *O = new OP<T>('^', x.getself(), y.getself());

    H.eval = O;
    return H;
}

/**binary(var, AD) */
template<class T>
AD<T> operator +(var<T> x, AD<T> G){
    AD<T> H;

    H.val = x.getVAL() + G.val;

    OP<T> *O = new OP<T>('+', x.getself(), G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(var<T> x, AD<T> G){
    AD<T> H;

    H.val = x.getVAL() - G.val;

    OP<T> *O = new OP<T>('-', x.getself(), G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator *(var<T> x, AD<T> G){
    AD<T> H;

    H.val = x.getVAL() * G.val;

    OP<T> *O = new OP<T>('*', x.getself(), G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator /(var<T> x, AD<T> G){
    AD<T> H;

    H.val = x.getVAL() / G.val;

    OP<T> *O = new OP<T>('/', x.getself(), G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator ^(var<T> x, AD<T> G){
    AD<T> H;

    H.val = x.getVAL() ^ G.val;

    OP<T> *O = new OP<T>('^', x.getself(), G.eval);

    H.eval = O;
    return H;
}

/**binary(var, gNode) */
template<class T>
AD<T> operator +(var<T> x, gNode<T> g){
    AD<T> H;

    H.val = x.getVAL() + g.getVAL();

    OP<T> *O = new OP<T>('+', x.getself(), g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(var<T> x, gNode<T> g){
    AD<T> H;

    H.val = x.getVAL() - g.getVAL();

    OP<T> *O = new OP<T>('-', x.getself(), g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator *(var<T> x, gNode<T> g){
    AD<T> H;

    H.val = x.getVAL() * g.getVAL();

    OP<T> *O = new OP<T>('*', x.getself(), g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator /(var<T> x, gNode<T> g){
    AD<T> H;

    H.val = x.getVAL() / g.getVAL();

    OP<T> *O = new OP<T>('/', x.getself(), g.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator ^(var<T> x, gNode<T> g){
    AD<T> H;

    H.val = x.getVAL() ^ g.getVAL();

    OP<T> *O = new OP<T>('^', x.getself(), g.getself());

    H.eval = O;
    return H;
}

/**binary(gNode, T) */
template<class T>
AD<T> operator +(gNode<T> g, T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = g.getVAL() + s->getVAL();

    OP<T> *O = new OP<T>('+', g.getself(), s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(gNode<T> g, T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = g.getVAL() - s->getVAL();

    OP<T> *O = new OP<T>('-', g.getself(), s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator *(gNode<T> g, T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = g.getVAL() * s->getVAL();

    OP<T> *O = new OP<T>('*', g.getself(), s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator /(gNode<T> g, T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = g.getVAL() / s->getVAL();

    OP<T> *O = new OP<T>('/', g.getself(), s);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator ^(gNode<T> g, T k){
    AD<T> H;
    scalar<T> *s = new scalar<T>(k);

    H.val = g.getVAL() ^ s->getVAL();

    OP<T> *O = new OP<T>('^', g.getself(), s);

    H.eval = O;
    return H;
}

/**binary(gNode, var) */
template<class T>
AD<T> operator +(gNode<T> g, var<T> x){
    AD<T> H;

    H.val = g.getVAL() + x.getVAL();

    OP<T> *O = new OP<T>('+', g.getself(), x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(gNode<T> g, var<T> x){
    AD<T> H;

    H.val = g.getVAL() - x.getVAL();

    OP<T> *O = new OP<T>('-', g.getself(), x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator *(gNode<T> g, var<T> x){
    AD<T> H;

    H.val = g.getVAL() * x.getVAL();

    OP<T> *O = new OP<T>('*', g.getself(), x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator /(gNode<T> g, var<T> x){
    AD<T> H;

    H.val = g.getVAL() / x.getVAL();

    OP<T> *O = new OP<T>('/', g.getself(), x.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator ^(gNode<T> g, var<T> x){
    AD<T> H;

    H.val = g.getVAL() ^ x.getVAL();

    OP<T> *O = new OP<T>('^', g.getself(), x.getself());

    H.eval = O;
    return H;
}

/**binary(gNode, AD) */
template<class T>
AD<T> operator +(gNode<T> g, AD<T> G){
    AD<T> H;

    H.val = g.getVAL() + G.val;

    OP<T> *O = new OP<T>('+', g.getself(), G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(gNode<T> g, AD<T> G){
    AD<T> H;

    H.val = g.getVAL() - G.val;

    OP<T> *O = new OP<T>('-', g.getself(), G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator *(gNode<T> g, AD<T> G){
    AD<T> H;

    H.val = g.getVAL() * G.val;

    OP<T> *O = new OP<T>('*', g.getself(), G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator /(gNode<T> g, AD<T> G){
    AD<T> H;

    H.val = g.getVAL() / G.val;

    OP<T> *O = new OP<T>('/', g.getself(), G.eval);

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator ^(gNode<T> g, AD<T> G){
    AD<T> H;

    H.val = g.getVAL() ^ G.val;

    OP<T> *O = new OP<T>('^', g.getself(), G.eval);

    H.eval = O;
    return H;
}

/**binary(gNode, gNode) */
template<class T>
AD<T> operator +(gNode<T> g, gNode<T> h){
    AD<T> H;

    H.val = g.getVAL() + h.getVAL();

    OP<T> *O = new OP<T>('+', g.getself(), h.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator -(gNode<T> g, gNode<T> h){
    AD<T> H;

    H.val = g.getVAL() - h.getVAL();

    OP<T> *O = new OP<T>('-', g.getself(), h.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator *(gNode<T> g, gNode<T> h){
    AD<T> H;

    H.val = g.getVAL() * h.getVAL();

    OP<T> *O = new OP<T>('*', g.getself(), h.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator /(gNode<T> g, gNode<T> h){
    AD<T> H;

    H.val = g.getVAL() / h.getVAL();

    OP<T> *O = new OP<T>('/', g.getself(), h.getself());

    H.eval = O;
    return H;
}

template<class T>
AD<T> operator ^(gNode<T> g, gNode<T> h){
    AD<T> H;

    H.val = g.getVAL() ^ h.getVAL();

    OP<T> *O = new OP<T>('^', g.getself(), h.getself());

    H.eval = O;
    return H;
}

/**Advanced operations*/
template<class T>
vector<T> functionVector(int numF, AD<T>* AD_list){
    vector<T> V(numF);
    for(int i = 0; i<numF; i++)
        V[i] = AD_list[i].val.getf();
    return V;
}


template<class T>
vector<T> grad(int n, var<T>** varList, AD<T> G){
    vector<T> V(idc);
    for(int i = 0; i<idc; i++)
        V[i] = G.val[varList[j]->getid()];

    return V;
}

template<class T>
SparseMatrix<T> jacobian(int n, var<T>** varList, AD<T>* AD_list){
    SparseMatrix<T> M(n);
    for(int i = 0; i<n; i++)
        for(int j = 0; j<n; j++)
            M(i, j, AD_list[i].val[varList[j]->getid()]);

    return M;
}
#endif
