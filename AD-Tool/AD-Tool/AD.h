/* Make changes in the code to take care of intermediate variable inclusion!! */
/* Pass by reference */
/* Context class to protect counter */

#pragma once


#include <iostream>
#include <cmath>

#include "vector.h"
#include "matrix.h"


#include "node.h"
#include "scalar.h"
#include "var.h"
#include "OP.h"
#include "gNode.h"

#include "VAL.h"

#include "counter.h"

using namespace std;

template<class T>
class AD {
	VAL<T> val;
	node<T>* eval;

public:
	AD() { this->eval = NULL; }

	void disp(int = 0);

	void reeval();

	void operator =(T);
	void operator =(var<T>);
	void operator =(AD<T>);
	void operator =(gNode<T>);

	void setval(VAL<T> v) { val = v; }
	void seteval(node<T>* ev) { eval = ev; }

	VAL<T> getval() { return val; }
	node<T>* geteval() { return eval; }

	template<class U>
	friend AD<U> copyAD(AD<U>);

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
	/**Gradient*/
	template <class U>
	friend vector<U> grad(AD<U>);

	/**Jacobian*/
	template <class U>
	friend matrix<U> jacobian(int, AD<U>*);
};

template<class T>
AD<T> copyAD(AD<T> G) {
	AD<T> H;
	H.val = G.val;
	H.eval = cloneNode(G.eval);
	return H;
}

template<class T>
node<T>* cloneNode(node<T>* root) {

	switch (root->gettype()) {
	case 's': { return root; break; }
	case 'v': { return root; break; }
	case 'g': { return cloneNode(root->clone()); break; }
	case 'o': {
		node<T>* O = root->clone();
		O->setLchild(cloneNode(O->getLchild()));
		O->setRchild(cloneNode(O->getRchild()));
		return O;
		break;
	}
	default: {
		cout << "Invalid node object.\n";
		return NULL;
		break;
	}
	}
}

template<class T>
void AD<T>::disp(int type) {
	switch (type) {
	case 0: this->val.disp(); break;
	case 1: this->eval->InOrderTreeWalk(); break;
	case 2: this->val.disp(); this->eval->InOrderTreeWalk(); break;
	}
}

template<class T>
void AD<T>::reeval() {
	if (this->eval != NULL)
		this->val = eval->getVAL();
}

/**Assignment operators */
template<class T>
void AD<T>::operator =(T k) {
	scalar<T>* s = new scalar<T>(k);
	this->val = s->getVAL();
	this->eval = s;
}

template<class T>
void AD<T>::operator =(var<T> x) {
	this->val = x.getVAL();
	this->eval = x.getself();
}

template<class T>
void AD<T>::operator =(AD<T> G) {
	this->val = G.val;
	this->eval = G.eval;
}

template<class T>
void AD<T>::operator =(gNode<T> g) {
	this->val = g.getVAL();
	this->eval = g.getself();
}

/**unary(AD) */
template<class T>
AD<T> AD<T>::operator +() {
	AD<T> H;

	H.val = this->val;
	OP<T>* O = new OP<T>('+', this->eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator -() {
	AD<T> H;

	H.val = -(this->val);
	OP<T>* O = new OP<T>('-', this->eval);

	H.eval = O;
	return H;
}

/**unary(T) - NOT ALLOWED! */

/**unary(var) */
template<class T>
AD<T> operator +(var<T> x) {
	AD<T> H;

	H.val = x.getVAL();
	OP<T>* O = new OP<T>('+', x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(var<T> x) {
	AD<T> H;

	H.val = -x.getVAL();
	OP<T>* O = new OP<T>('-', x.getself());

	H.eval = O;
	return H;
}

/**unary(gNode) */
template<class T>
AD<T> operator +(gNode<T> g) {
	AD<T> H;

	H.val = g.getVAL();
	OP<T>* O = new OP<T>('+', g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(gNode<T> g) {
	AD<T> H;

	H.val = -g.getVAL();
	OP<T>* O = new OP<T>('-', g.getself());

	H.eval = O;
	return H;
}

/**binary(AD, T) */
template<class T>
AD<T> AD<T>::operator +(T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = this->val + s->getVAL();

	OP<T>* O = new OP<T>('+', this->eval, s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator -(T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = this->val - s->getVAL();

	OP<T>* O = new OP<T>('-', this->eval, s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator *(T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);


	H.val = this->val * s->getVAL();

	OP<T>* O = new OP<T>('*', this->eval, s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator /(T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = this->val / s->getVAL();

	OP<T>* O = new OP<T>('/', this->eval, s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator ^(T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = this->val ^ s->getVAL();

	OP<T>* O = new OP<T>('^', this->eval, s);

	H.eval = O;
	return H;
}

/**binary(AD, var) */
template<class T>
AD<T> AD<T>::operator +(var<T> x) {
	AD<T> H;

	H.val = this->val + x.getVAL();

	OP<T>* O = new OP<T>('+', this->eval, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator -(var<T> x) {
	AD<T> H;

	H.val = this->val - x.getVAL();

	OP<T>* O = new OP<T>('-', this->eval, x.getself());

	H.eval = O;
	return H;
}


template<class T>
AD<T> AD<T>::operator *(var<T> x) {
	AD<T> H;

	H.val = this->val * x.getVAL();

	OP<T>* O = new OP<T>('*', this->eval, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator /(var<T> x) {
	AD<T> H;

	H.val = this->val / x.getVAL();

	OP<T>* O = new OP<T>('/', this->eval, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator ^(var<T> x) {
	AD<T> H;

	H.val = this->val ^ x.getVAL();

	OP<T>* O = new OP<T>('^', this->eval, x.getself());

	H.eval = O;
	return H;
}

/**binary(AD, AD) */
template<class T>
AD<T> AD<T>::operator +(AD<T> G) {
	AD<T> H;

	H.val = this->val + G.val;

	OP<T>* O = new OP<T>('+', this->eval, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator -(AD<T> G) {
	AD<T> H;

	H.val = this->val - G.val;

	OP<T>* O = new OP<T>('-', this->eval, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator *(AD<T> G) {
	AD<T> H;

	H.val = this->val * G.val;

	OP<T>* O = new OP<T>('*', this->eval, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator /(AD<T> G) {
	AD<T> H;

	H.val = this->val / G.val;

	OP<T>* O = new OP<T>('/', this->eval, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator ^(AD<T> G) {
	AD<T> H;

	H.val = this->val ^ G.val;

	OP<T>* O = new OP<T>('^', this->eval, G.eval);

	H.eval = O;
	return H;
}

/**binary(AD, gNode) */
template<class T>
AD<T> AD<T>::operator +(gNode<T> g) {
	AD<T> H;

	H.val = this->val + g.getVAL();

	OP<T>* O = new OP<T>('+', this->eval, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator -(gNode<T> g) {
	AD<T> H;

	H.val = this->val - g.getVAL();

	OP<T>* O = new OP<T>('-', this->eval, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator *(gNode<T> g) {
	AD<T> H;

	H.val = this->val * g.getVAL();

	OP<T>* O = new OP<T>('*', this->eval, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator /(gNode<T> g) {
	AD<T> H;

	H.val = this->val / g.getVAL();

	OP<T>* O = new OP<T>('/', this->eval, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator ^(gNode<T> g) {
	AD<T> H;

	H.val = this->val ^ g.getVAL();

	OP<T>* O = new OP<T>('^', this->eval, g.getself());

	H.eval = O;
	return H;
}

/**binary(T, T) - NOT ALLOWED! */

/**binary(T, var) */
template<class T>
AD<T> operator +(T k, var<T> x) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() + x.getVAL();

	OP<T>* O = new OP<T>('+', s, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(T k, var<T> x) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() - x.getVAL();

	OP<T>* O = new OP<T>('-', s, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(T k, var<T> x) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() * x.getVAL();

	OP<T>* O = new OP<T>('*', s, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(T k, var<T> x) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() / x.getVAL();

	OP<T>* O = new OP<T>('/', s, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(T k, var<T> x) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() ^ x.getVAL();

	OP<T>* O = new OP<T>('^', s, x.getself());

	H.eval = O;
	return H;
}

/**binary(T, AD) */
template<class T>
AD<T> operator +(T k, AD<T> G) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() + G.val;

	OP<T>* O = new OP<T>('+', s, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(T k, AD<T> G) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() - G.val;

	OP<T>* O = new OP<T>('-', s, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(T k, AD<T> G) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() * G.val;

	OP<T>* O = new OP<T>('*', s, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(T k, AD<T> G) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() / G.val;

	OP<T>* O = new OP<T>('/', s, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(T k, AD<T> G) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() ^ G.val;

	OP<T>* O = new OP<T>('^', s, G.eval);

	H.eval = O;
	return H;
}

/**binary(T, gNode) */
template<class T>
AD<T> operator +(T k, gNode<T> g) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() + g.getVAL();

	OP<T>* O = new OP<T>('+', s, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(T k, gNode<T> g) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() - g.getVAL();

	OP<T>* O = new OP<T>('-', s, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(T k, gNode<T> g) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() * g.getVAL();

	OP<T>* O = new OP<T>('*', s, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(T k, gNode<T> g) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() / g.getVAL();

	OP<T>* O = new OP<T>('/', s, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(T k, gNode<T> g) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() ^ g.getVAL();

	OP<T>* O = new OP<T>('^', s, g.getself());

	H.eval = O;
	return H;
}

/**binary(var, T) */
template<class T>
AD<T> operator +(var<T> x, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = x.getVAL() + s->getVAL();

	OP<T>* O = new OP<T>('+', x.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(var<T> x, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = x.getVAL() - s->getVAL();

	OP<T>* O = new OP<T>('-', x.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(var<T> x, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = x.getVAL() * s->getVAL();

	OP<T>* O = new OP<T>('*', x.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(var<T> x, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = x.getVAL() / s->getVAL();

	OP<T>* O = new OP<T>('/', x.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(var<T> x, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = x.getVAL() ^ s->getVAL();

	OP<T>* O = new OP<T>('^', x.getself(), s);

	H.eval = O;
	return H;
}

/**binary(var, var) */
template<class T>
AD<T> operator +(var<T> x, var<T> y) {
	AD<T> H;

	H.val = x.getVAL() + y.getVAL();

	OP<T>* O = new OP<T>('+', x.getself(), y.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(var<T> x, var<T> y) {
	AD<T> H;

	H.val = x.getVAL() - y.getVAL();

	OP<T>* O = new OP<T>('-', x.getself(), y.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(var<T> x, var<T> y) {
	AD<T> H;

	H.val = x.getVAL() * y.getVAL();

	OP<T>* O = new OP<T>('*', x.getself(), y.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(var<T> x, var<T> y) {
	AD<T> H;

	H.val = x.getVAL() / y.getVAL();

	OP<T>* O = new OP<T>('/', x.getself(), y.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(var<T> x, var<T> y) {
	AD<T> H;

	H.val = x.getVAL() ^ y.getVAL();

	OP<T>* O = new OP<T>('^', x.getself(), y.getself());

	H.eval = O;
	return H;
}

/**binary(var, AD) */
template<class T>
AD<T> operator +(var<T> x, AD<T> G) {
	AD<T> H;

	H.val = x.getVAL() + G.val;

	OP<T>* O = new OP<T>('+', x.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(var<T> x, AD<T> G) {
	AD<T> H;

	H.val = x.getVAL() - G.val;

	OP<T>* O = new OP<T>('-', x.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(var<T> x, AD<T> G) {
	AD<T> H;

	H.val = x.getVAL() * G.val;

	OP<T>* O = new OP<T>('*', x.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(var<T> x, AD<T> G) {
	AD<T> H;

	H.val = x.getVAL() / G.val;

	OP<T>* O = new OP<T>('/', x.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(var<T> x, AD<T> G) {
	AD<T> H;

	H.val = x.getVAL() ^ G.val;

	OP<T>* O = new OP<T>('^', x.getself(), G.eval);

	H.eval = O;
	return H;
}

/**binary(var, gNode) */
template<class T>
AD<T> operator +(var<T> x, gNode<T> g) {
	AD<T> H;

	H.val = x.getVAL() + g.getVAL();

	OP<T>* O = new OP<T>('+', x.getself(), g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(var<T> x, gNode<T> g) {
	AD<T> H;

	H.val = x.getVAL() - g.getVAL();

	OP<T>* O = new OP<T>('-', x.getself(), g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(var<T> x, gNode<T> g) {
	AD<T> H;

	H.val = x.getVAL() * g.getVAL();

	OP<T>* O = new OP<T>('*', x.getself(), g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(var<T> x, gNode<T> g) {
	AD<T> H;

	H.val = x.getVAL() / g.getVAL();

	OP<T>* O = new OP<T>('/', x.getself(), g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(var<T> x, gNode<T> g) {
	AD<T> H;

	H.val = x.getVAL() ^ g.getVAL();

	OP<T>* O = new OP<T>('^', x.getself(), g.getself());

	H.eval = O;
	return H;
}

/**binary(gNode, T) */
template<class T>
AD<T> operator +(gNode<T> g, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = g.getVAL() + s->getVAL();

	OP<T>* O = new OP<T>('+', g.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(gNode<T> g, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = g.getVAL() - s->getVAL();

	OP<T>* O = new OP<T>('-', g.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(gNode<T> g, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = g.getVAL() * s->getVAL();

	OP<T>* O = new OP<T>('*', g.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(gNode<T> g, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = g.getVAL() / s->getVAL();

	OP<T>* O = new OP<T>('/', g.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(gNode<T> g, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = g.getVAL() ^ s->getVAL();

	OP<T>* O = new OP<T>('^', g.getself(), s);

	H.eval = O;
	return H;
}

/**binary(gNode, var) */
template<class T>
AD<T> operator +(gNode<T> g, var<T> x) {
	AD<T> H;

	H.val = g.getVAL() + x.getVAL();

	OP<T>* O = new OP<T>('+', g.getself(), x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(gNode<T> g, var<T> x) {
	AD<T> H;

	H.val = g.getVAL() - x.getVAL();

	OP<T>* O = new OP<T>('-', g.getself(), x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(gNode<T> g, var<T> x) {
	AD<T> H;

	H.val = g.getVAL() * x.getVAL();

	OP<T>* O = new OP<T>('*', g.getself(), x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(gNode<T> g, var<T> x) {
	AD<T> H;

	H.val = g.getVAL() / x.getVAL();

	OP<T>* O = new OP<T>('/', g.getself(), x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(gNode<T> g, var<T> x) {
	AD<T> H;

	H.val = g.getVAL() ^ x.getVAL();

	OP<T>* O = new OP<T>('^', g.getself(), x.getself());

	H.eval = O;
	return H;
}

/**binary(gNode, AD) */
template<class T>
AD<T> operator +(gNode<T> g, AD<T> G) {
	AD<T> H;

	H.val = g.getVAL() + G.val;

	OP<T>* O = new OP<T>('+', g.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(gNode<T> g, AD<T> G) {
	AD<T> H;

	H.val = g.getVAL() - G.val;

	OP<T>* O = new OP<T>('-', g.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(gNode<T> g, AD<T> G) {
	AD<T> H;

	H.val = g.getVAL() * G.val;

	OP<T>* O = new OP<T>('*', g.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(gNode<T> g, AD<T> G) {
	AD<T> H;

	H.val = g.getVAL() / G.val;

	OP<T>* O = new OP<T>('/', g.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(gNode<T> g, AD<T> G) {
	AD<T> H;

	H.val = g.getVAL() ^ G.val;

	OP<T>* O = new OP<T>('^', g.getself(), G.eval);

	H.eval = O;
	return H;
}

/**binary(gNode, gNode) */
template<class T>
AD<T> operator +(gNode<T> g, gNode<T> h) {
	AD<T> H;

	H.val = g.getVAL() + h.getVAL();

	OP<T>* O = new OP<T>('+', g.getself(), h.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(gNode<T> g, gNode<T> h) {
	AD<T> H;

	H.val = g.getVAL() - h.getVAL();

	OP<T>* O = new OP<T>('-', g.getself(), h.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(gNode<T> g, gNode<T> h) {
	AD<T> H;

	H.val = g.getVAL() * h.getVAL();

	OP<T>* O = new OP<T>('*', g.getself(), h.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(gNode<T> g, gNode<T> h) {
	AD<T> H;

	H.val = g.getVAL() / h.getVAL();

	OP<T>* O = new OP<T>('/', g.getself(), h.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(gNode<T> g, gNode<T> h) {
	AD<T> H;

	H.val = g.getVAL() ^ h.getVAL();

	OP<T>* O = new OP<T>('^', g.getself(), h.getself());

	H.eval = O;
	return H;
}

/**Advanced operations*/
template<class T>
vector<T> grad(AD<T> G) {
	counter idc;
	vector<T> V(idc.getCount());
	for (int i = 0; i < idc; i++)
		V[i] = G.val[i];

	return V;
}

template<class T>
matrix<T> jacobian(int n, AD<T>* AD_list) {
	counter idc;
	matrix<T> M(n, idc.getCount());
	for (int i = 0; i < n; i++)
		for (int j = 0; j < idc ; j++)
			M(i, j) = AD_list[i].val[j];

	return M;
}