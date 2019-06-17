/* Make changes in the code to take care of intermediate variable inclusion!! */
/* Add "context" or domain - protecting the globally visible counter */
/* Rename functions - disp to display, reeval to reEval ? stay consistent */
/* Contain everything within my own namespace */
/* Pass by reference - makes things faster */
/* Define gNode operators */

#pragma once


#include <iostream>
#include <cmath>
#include <vector>

#include "matrix.h"

#include "node.h"
#include "scalar.h"
#include "var.h"
#include "op.h"
#include "pNode.h"

#include "VAL.h"

#include "counter.h"

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
	void operator =(pNode<T>);

	void setval(VAL<T> v) { val = v; }
	void seteval(node<T>* ev) { eval = ev; }

	VAL<T> getval() { return val; }
	node<T>* geteval() { return eval; }

	template<class U>
	AD<U> copyAD(AD<U>);

	/**Math operators */
	AD<T> operator +(); //defined
	AD<T> operator -(); //defined

	template<class U>
	friend AD<U> operator +(var<U>); //defined
	template<class U>
	friend AD<U> operator -(var<U>); //defined

	template<class U>
	friend AD<U> operator +(pNode<U>); //defined
	template<class U>
	friend AD<U> operator -(pNode<U>); //defined

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

	AD<T> operator +(pNode<T>); //defined
	AD<T> operator -(pNode<T>); //defined
	AD<T> operator *(pNode<T>); //defined
	AD<T> operator /(pNode<T>); //defined
	AD<T> operator ^(pNode<T>); //defined

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
	friend AD<U> operator +(U, pNode<U>); //defined
	template<class U>
	friend AD<U> operator -(U, pNode<U>); //defined
	template<class U>
	friend AD<U> operator *(U, pNode<U>); //defined
	template<class U>
	friend AD<U> operator /(U, pNode<U>); //defined
	template<class U>
	friend AD<U> operator ^(U, pNode<U>); //defined

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
	friend AD<U> operator +(var<U>, pNode<U>); //defined
	template<class U>
	friend AD<U> operator -(var<U>, pNode<U>); //defined
	template<class U>
	friend AD<U> operator *(var<U>, pNode<U>); //defined
	template<class U>
	friend AD<U> operator /(var<U>, pNode<U>); //defined
	template<class U>
	friend AD<U> operator ^(var<U>, pNode<U>); //defined

	template<class U>
	friend AD<U> operator +(pNode<U>, U); //defined
	template<class U>
	friend AD<U> operator -(pNode<U>, U); //defined
	template<class U>
	friend AD<U> operator *(pNode<U>, U); //defined
	template<class U>
	friend AD<U> operator /(pNode<U>, U); //defined
	template<class U>
	friend AD<U> operator ^(pNode<U>, U); //defined

	template<class U>
	friend AD<U> operator +(pNode<U>, var<U>); //defined
	template<class U>
	friend AD<U> operator -(pNode<U>, var<U>); //defined
	template<class U>
	friend AD<U> operator *(pNode<U>, var<U>); //defined
	template<class U>
	friend AD<U> operator /(pNode<U>, var<U>); //defined
	template<class U>
	friend AD<U> operator ^(pNode<U>, var<U>); //defined

	template<class U>
	friend AD<U> operator +(pNode<U>, AD<U>); //defined
	template<class U>
	friend AD<U> operator -(pNode<U>, AD<U>); //defined
	template<class U>
	friend AD<U> operator *(pNode<U>, AD<U>); //defined
	template<class U>
	friend AD<U> operator /(pNode<U>, AD<U>); //defined
	template<class U>
	friend AD<U> operator ^(pNode<U>, AD<U>); //defined

	template<class U>
	friend AD<U> operator +(pNode<U>, pNode<U>); //defined
	template<class U>
	friend AD<U> operator -(pNode<U>, pNode<U>); //defined
	template<class U>
	friend AD<U> operator *(pNode<U>, pNode<U>); //defined
	template<class U>
	friend AD<U> operator /(pNode<U>, pNode<U>); //defined
	template<class U>
	friend AD<U> operator ^(pNode<U>, pNode<U>); //defined

	/**Advanced operations*/
	/**Gradient*/
	template <class U>
	friend std::vector<U> grad(AD<U>);

	/**Jacobian*/
	template <class U>
	friend matrix<U> jacobian(int, AD<U>*);
};

template<class T>
AD<T> copyAD(AD<T> G) {
	AD<T> H;
	H.setval(G.getval());
	H.seteval(cloneNode(G.geteval()));
	return H;
}

template<class T>
node<T>* cloneNode(node<T>* root) {

	switch (root->gettype()) {
	case 's': { return root; break; }
	case 'v': { return root; break; }
	case 'p': { return cloneNode(root->clone()); break; }
	case 'o': {
		node<T>* O = root->clone();
		O->setLchild(cloneNode(O->getLchild()));
		O->setRchild(cloneNode(O->getRchild()));
		return O;
		break;
	}
	default: {
		std::cout << "Invalid node object.\n";
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
void AD<T>::operator =(pNode<T> g) {
	this->val = g.getVAL();
	this->eval = g.getself();
}

/**unary(AD) */
template<class T>
AD<T> AD<T>::operator +() {
	AD<T> H;

	H.val = this->val;
	op<T>* O = new op<T>('+', this->eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator -() {
	AD<T> H;

	H.val = -(this->val);
	op<T>* O = new op<T>('-', this->eval);

	H.eval = O;
	return H;
}

/**unary(T) - NOT ALLOWED! */

/**unary(var) */
template<class T>
AD<T> operator +(var<T> x) {
	AD<T> H;

	H.val = x.getVAL();
	op<T>* O = new op<T>('+', x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(var<T> x) {
	AD<T> H;

	H.val = -x.getVAL();
	op<T>* O = new op<T>('-', x.getself());

	H.eval = O;
	return H;
}

/**unary(gNode) */
template<class T>
AD<T> operator +(pNode<T> g) {
	AD<T> H;

	H.val = g.getVAL();
	op<T>* O = new op<T>('+', g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(pNode<T> g) {
	AD<T> H;

	H.val = -g.getVAL();
	op<T>* O = new op<T>('-', g.getself());

	H.eval = O;
	return H;
}

/**binary(AD, T) */
template<class T>
AD<T> AD<T>::operator +(T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = this->val + s->getVAL();

	op<T>* O = new op<T>('+', this->eval, s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator -(T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = this->val - s->getVAL();

	op<T>* O = new op<T>('-', this->eval, s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator *(T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);


	H.val = this->val * s->getVAL();

	op<T>* O = new op<T>('*', this->eval, s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator /(T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = this->val / s->getVAL();

	op<T>* O = new op<T>('/', this->eval, s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator ^(T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = this->val ^ s->getVAL();

	op<T>* O = new op<T>('^', this->eval, s);

	H.eval = O;
	return H;
}

/**binary(AD, var) */
template<class T>
AD<T> AD<T>::operator +(var<T> x) {
	AD<T> H;

	H.val = this->val + x.getVAL();

	op<T>* O = new op<T>('+', this->eval, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator -(var<T> x) {
	AD<T> H;

	H.val = this->val - x.getVAL();

	op<T>* O = new op<T>('-', this->eval, x.getself());

	H.eval = O;
	return H;
}


template<class T>
AD<T> AD<T>::operator *(var<T> x) {
	AD<T> H;

	H.val = this->val * x.getVAL();

	op<T>* O = new op<T>('*', this->eval, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator /(var<T> x) {
	AD<T> H;

	H.val = this->val / x.getVAL();

	op<T>* O = new op<T>('/', this->eval, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator ^(var<T> x) {
	AD<T> H;

	H.val = this->val ^ x.getVAL();

	op<T>* O = new op<T>('^', this->eval, x.getself());

	H.eval = O;
	return H;
}

/**binary(AD, AD) */
template<class T>
AD<T> AD<T>::operator +(AD<T> G) {
	AD<T> H;

	H.val = this->val + G.val;

	op<T>* O = new op<T>('+', this->eval, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator -(AD<T> G) {
	AD<T> H;

	H.val = this->val - G.val;

	op<T>* O = new op<T>('-', this->eval, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator *(AD<T> G) {
	AD<T> H;

	H.val = this->val * G.val;

	op<T>* O = new op<T>('*', this->eval, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator /(AD<T> G) {
	AD<T> H;

	H.val = this->val / G.val;

	op<T>* O = new op<T>('/', this->eval, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator ^(AD<T> G) {
	AD<T> H;

	H.val = this->val ^ G.val;

	op<T>* O = new op<T>('^', this->eval, G.eval);

	H.eval = O;
	return H;
}

/**binary(AD, gNode) */
template<class T>
AD<T> AD<T>::operator +(pNode<T> g) {
	AD<T> H;

	H.val = this->val + g.getVAL();

	op<T>* O = new op<T>('+', this->eval, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator -(pNode<T> g) {
	AD<T> H;

	H.val = this->val - g.getVAL();

	op<T>* O = new op<T>('-', this->eval, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator *(pNode<T> g) {
	AD<T> H;

	H.val = this->val * g.getVAL();

	op<T>* O = new op<T>('*', this->eval, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator /(pNode<T> g) {
	AD<T> H;

	H.val = this->val / g.getVAL();

	op<T>* O = new op<T>('/', this->eval, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> AD<T>::operator ^(pNode<T> g) {
	AD<T> H;

	H.val = this->val ^ g.getVAL();

	op<T>* O = new op<T>('^', this->eval, g.getself());

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

	op<T>* O = new op<T>('+', s, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(T k, var<T> x) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() - x.getVAL();

	op<T>* O = new op<T>('-', s, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(T k, var<T> x) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() * x.getVAL();

	op<T>* O = new op<T>('*', s, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(T k, var<T> x) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() / x.getVAL();

	op<T>* O = new op<T>('/', s, x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(T k, var<T> x) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() ^ x.getVAL();

	op<T>* O = new op<T>('^', s, x.getself());

	H.eval = O;
	return H;
}

/**binary(T, AD) */
template<class T>
AD<T> operator +(T k, AD<T> G) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() + G.val;

	op<T>* O = new op<T>('+', s, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(T k, AD<T> G) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() - G.val;

	op<T>* O = new op<T>('-', s, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(T k, AD<T> G) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() * G.val;

	op<T>* O = new op<T>('*', s, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(T k, AD<T> G) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() / G.val;

	op<T>* O = new op<T>('/', s, G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(T k, AD<T> G) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() ^ G.val;

	op<T>* O = new op<T>('^', s, G.eval);

	H.eval = O;
	return H;
}

/**binary(T, gNode) */
template<class T>
AD<T> operator +(T k, pNode<T> g) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() + g.getVAL();

	op<T>* O = new op<T>('+', s, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(T k, pNode<T> g) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() - g.getVAL();

	op<T>* O = new op<T>('-', s, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(T k, pNode<T> g) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() * g.getVAL();

	op<T>* O = new op<T>('*', s, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(T k, pNode<T> g) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() / g.getVAL();

	op<T>* O = new op<T>('/', s, g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(T k, pNode<T> g) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = s->getVAL() ^ g.getVAL();

	op<T>* O = new op<T>('^', s, g.getself());

	H.eval = O;
	return H;
}

/**binary(var, T) */
template<class T>
AD<T> operator +(var<T> x, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = x.getVAL() + s->getVAL();

	op<T>* O = new op<T>('+', x.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(var<T> x, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = x.getVAL() - s->getVAL();

	op<T>* O = new op<T>('-', x.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(var<T> x, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = x.getVAL() * s->getVAL();

	op<T>* O = new op<T>('*', x.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(var<T> x, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = x.getVAL() / s->getVAL();

	op<T>* O = new op<T>('/', x.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(var<T> x, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = x.getVAL() ^ s->getVAL();

	op<T>* O = new op<T>('^', x.getself(), s);

	H.eval = O;
	return H;
}

/**binary(var, var) */
template<class T>
AD<T> operator +(var<T> x, var<T> y) {
	AD<T> H;

	H.val = x.getVAL() + y.getVAL();

	op<T>* O = new op<T>('+', x.getself(), y.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(var<T> x, var<T> y) {
	AD<T> H;

	H.val = x.getVAL() - y.getVAL();

	op<T>* O = new op<T>('-', x.getself(), y.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(var<T> x, var<T> y) {
	AD<T> H;

	H.val = x.getVAL() * y.getVAL();

	op<T>* O = new op<T>('*', x.getself(), y.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(var<T> x, var<T> y) {
	AD<T> H;

	H.val = x.getVAL() / y.getVAL();

	op<T>* O = new op<T>('/', x.getself(), y.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(var<T> x, var<T> y) {
	AD<T> H;

	H.val = x.getVAL() ^ y.getVAL();

	op<T>* O = new op<T>('^', x.getself(), y.getself());

	H.eval = O;
	return H;
}

/**binary(var, AD) */
template<class T>
AD<T> operator +(var<T> x, AD<T> G) {
	AD<T> H;

	H.val = x.getVAL() + G.val;

	op<T>* O = new op<T>('+', x.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(var<T> x, AD<T> G) {
	AD<T> H;

	H.val = x.getVAL() - G.val;

	op<T>* O = new op<T>('-', x.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(var<T> x, AD<T> G) {
	AD<T> H;

	H.val = x.getVAL() * G.val;

	op<T>* O = new op<T>('*', x.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(var<T> x, AD<T> G) {
	AD<T> H;

	H.val = x.getVAL() / G.val;

	op<T>* O = new op<T>('/', x.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(var<T> x, AD<T> G) {
	AD<T> H;

	H.val = x.getVAL() ^ G.val;

	op<T>* O = new op<T>('^', x.getself(), G.eval);

	H.eval = O;
	return H;
}

/**binary(var, gNode) */
template<class T>
AD<T> operator +(var<T> x, pNode<T> g) {
	AD<T> H;

	H.val = x.getVAL() + g.getVAL();

	op<T>* O = new op<T>('+', x.getself(), g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(var<T> x, pNode<T> g) {
	AD<T> H;

	H.val = x.getVAL() - g.getVAL();

	op<T>* O = new op<T>('-', x.getself(), g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(var<T> x, pNode<T> g) {
	AD<T> H;

	H.val = x.getVAL() * g.getVAL();

	op<T>* O = new op<T>('*', x.getself(), g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(var<T> x, pNode<T> g) {
	AD<T> H;

	H.val = x.getVAL() / g.getVAL();

	op<T>* O = new op<T>('/', x.getself(), g.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(var<T> x, pNode<T> g) {
	AD<T> H;

	H.val = x.getVAL() ^ g.getVAL();

	op<T>* O = new op<T>('^', x.getself(), g.getself());

	H.eval = O;
	return H;
}

/**binary(gNode, T) */
template<class T>
AD<T> operator +(pNode<T> g, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = g.getVAL() + s->getVAL();

	op<T>* O = new op<T>('+', g.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(pNode<T> g, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = g.getVAL() - s->getVAL();

	op<T>* O = new op<T>('-', g.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(pNode<T> g, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = g.getVAL() * s->getVAL();

	op<T>* O = new op<T>('*', g.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(pNode<T> g, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = g.getVAL() / s->getVAL();

	op<T>* O = new op<T>('/', g.getself(), s);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(pNode<T> g, T k) {
	AD<T> H;
	scalar<T>* s = new scalar<T>(k);

	H.val = g.getVAL() ^ s->getVAL();

	op<T>* O = new op<T>('^', g.getself(), s);

	H.eval = O;
	return H;
}

/**binary(gNode, var) */
template<class T>
AD<T> operator +(pNode<T> g, var<T> x) {
	AD<T> H;

	H.val = g.getVAL() + x.getVAL();

	op<T>* O = new op<T>('+', g.getself(), x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(pNode<T> g, var<T> x) {
	AD<T> H;

	H.val = g.getVAL() - x.getVAL();

	op<T>* O = new op<T>('-', g.getself(), x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(pNode<T> g, var<T> x) {
	AD<T> H;

	H.val = g.getVAL() * x.getVAL();

	op<T>* O = new op<T>('*', g.getself(), x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(pNode<T> g, var<T> x) {
	AD<T> H;

	H.val = g.getVAL() / x.getVAL();

	op<T>* O = new op<T>('/', g.getself(), x.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(pNode<T> g, var<T> x) {
	AD<T> H;

	H.val = g.getVAL() ^ x.getVAL();

	op<T>* O = new op<T>('^', g.getself(), x.getself());

	H.eval = O;
	return H;
}

/**binary(gNode, AD) */
template<class T>
AD<T> operator +(pNode<T> g, AD<T> G) {
	AD<T> H;

	H.val = g.getVAL() + G.val;

	op<T>* O = new op<T>('+', g.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(pNode<T> g, AD<T> G) {
	AD<T> H;

	H.val = g.getVAL() - G.val;

	op<T>* O = new op<T>('-', g.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(pNode<T> g, AD<T> G) {
	AD<T> H;

	H.val = g.getVAL() * G.val;

	op<T>* O = new op<T>('*', g.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(pNode<T> g, AD<T> G) {
	AD<T> H;

	H.val = g.getVAL() / G.val;

	op<T>* O = new op<T>('/', g.getself(), G.eval);

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(pNode<T> g, AD<T> G) {
	AD<T> H;

	H.val = g.getVAL() ^ G.val;

	op<T>* O = new op<T>('^', g.getself(), G.eval);

	H.eval = O;
	return H;
}

/**binary(gNode, gNode) */
template<class T>
AD<T> operator +(pNode<T> g, pNode<T> h) {
	AD<T> H;

	H.val = g.getVAL() + h.getVAL();

	op<T>* O = new op<T>('+', g.getself(), h.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator -(pNode<T> g, pNode<T> h) {
	AD<T> H;

	H.val = g.getVAL() - h.getVAL();

	op<T>* O = new op<T>('-', g.getself(), h.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator *(pNode<T> g, pNode<T> h) {
	AD<T> H;

	H.val = g.getVAL() * h.getVAL();

	op<T>* O = new op<T>('*', g.getself(), h.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator /(pNode<T> g, pNode<T> h) {
	AD<T> H;

	H.val = g.getVAL() / h.getVAL();

	op<T>* O = new op<T>('/', g.getself(), h.getself());

	H.eval = O;
	return H;
}

template<class T>
AD<T> operator ^(pNode<T> g, pNode<T> h) {
	AD<T> H;

	H.val = g.getVAL() ^ h.getVAL();

	op<T>* O = new op<T>('^', g.getself(), h.getself());

	H.eval = O;
	return H;
}

/**Advanced operations*/
template<class T>
std::vector<T> grad(AD<T> G) {
	counter idc;
	std::vector<T> V(idc.getCount(), 0);
	for (int i = 0; i < idc; i++)
		V[i] = G.val[i];

	return V;
}

template<class T>
matrix<T> jacobian(int n, std::vector<AD<T>> AD_list) {
	counter idc;
	matrix<T> M(n, idc.getCount());
	for (int i = 0; i < n; i++)
		for (int j = 0; j < idc ; j++)
			M(i, j) = AD_list[i].val[j];

	return M;
}