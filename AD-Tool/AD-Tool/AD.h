/* Make changes in the code to take care of intermediate variable inclusion!! */
/* Add "context" or domain - protecting the globally visible counter */
/* Rename functions - disp to display, reeval to reEval ? stay consistent */
/* Pass by reference - makes things faster */

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

namespace sym {

	template<class T>
	class AD {
		sym::VAL<T> val;
		sym::node<T>* eval;

	public:
		AD() { this->eval = NULL; }

		void disp(int = 0);

		void reeval();

		void operator =(T);
		void operator =(sym::var<T>);
		void operator =(sym::AD<T>);
		void operator =(sym::pNode<T>);

		void setval(sym::VAL<T> v) { val = v; }
		void seteval(sym::node<T>* ev) { eval = ev; }

		sym::VAL<T> getval() { return val; }
		sym::node<T>* geteval() { return eval; }

		template<class U>
		AD<U> copyAD(sym::AD<U>);

		/**Math operators */
		sym::AD<T> operator +(); //defined
		sym::AD<T> operator -(); //defined

		template<class U>
		friend sym::AD<U> operator +(var<U>); //defined
		template<class U>
		friend sym::AD<U> operator -(var<U>); //defined

		template<class U>
		friend sym::AD<U> operator +(pNode<U>); //defined
		template<class U>
		friend sym::AD<U> operator -(pNode<U>); //defined

		sym::AD<T> operator +(T); //defined
		sym::AD<T> operator -(T); //defined
		sym::AD<T> operator *(T); //defined
		sym::AD<T> operator /(T); //defined
		sym::AD<T> operator ^(T); //defined

		sym::AD<T> operator +(var<T>); //defined
		sym::AD<T> operator -(var<T>); //defined
		sym::AD<T> operator *(var<T>); //defined
		sym::AD<T> operator /(var<T>); //defined
		sym::AD<T> operator ^(var<T>); //defined

		sym::AD<T> operator +(AD<T>); //defined
		sym::AD<T> operator -(AD<T>); //defined
		sym::AD<T> operator *(AD<T>); //defined
		sym::AD<T> operator /(AD<T>); //defined
		sym::AD<T> operator ^(AD<T>); //defined

		sym::AD<T> operator +(pNode<T>); //defined
		sym::AD<T> operator -(pNode<T>); //defined
		sym::AD<T> operator *(pNode<T>); //defined
		sym::AD<T> operator /(pNode<T>); //defined
		sym::AD<T> operator ^(pNode<T>); //defined

		template<class U>
		friend sym::AD<U> sym::operator +(U, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator -(U, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator *(U, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator /(U, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator ^(U, sym::var<U>); //defined
		
		template<class U>
		friend sym::AD<U> sym::operator +(U, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator -(U, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator *(U, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator /(U, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator ^(U, sym::AD<U>); //defined

		template<class U>
		friend sym::AD<U> sym::operator +(U, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator -(U, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator *(U, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator /(U, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> sym::operator ^(U, sym::pNode<U>); //defined

		template<class U>
		friend sym::AD<U> sym::operator +(sym::var<U>, U); //defined
		template<class U>
		friend sym::AD<U> sym::operator -(sym::var<U>, U); //defined
		template<class U>
		friend sym::AD<U> sym::operator *(sym::var<U>, U); //defined
		template<class U>
		friend sym::AD<U> sym::operator /(sym::var<U>, U); //defined
		template<class U>
		friend sym::AD<U> sym::operator ^(sym::var<U>, U); //defined

		template<class U>
		friend sym::AD<U> operator +(sym::var<U>, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> operator -(sym::var<U>, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> operator *(sym::var<U>, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> operator /(sym::var<U>, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> operator ^(sym::var<U>, sym::var<U>); //defined

		template<class U>
		friend sym::AD<U> operator +(sym::var<U>, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> operator -(sym::var<U>, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> operator *(sym::var<U>, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> operator /(sym::var<U>, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> operator ^(sym::var<U>, sym::AD<U>); //defined

		template<class U>
		friend sym::AD<U> operator +(sym::var<U>, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> operator -(sym::var<U>, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> operator *(sym::var<U>, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> operator /(sym::var<U>, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> operator ^(sym::var<U>, sym::pNode<U>); //defined

		template<class U>
		friend sym::AD<U> sym::operator +(sym::pNode<U>, U);
		template<class U>
		friend sym::AD<U> sym::operator -(sym::pNode<U>, U);
		template<class U>
		friend sym::AD<U> sym::operator *(sym::pNode<U>, U);
		template<class U>
		friend sym::AD<U> sym::operator /(sym::pNode<U>, U);
		template<class U>
		friend sym::AD<U> sym::operator ^(sym::pNode<U>, U);

		template<class U>
		friend sym::AD<U> operator +(sym::pNode<U>, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> operator -(sym::pNode<U>, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> operator *(sym::pNode<U>, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> operator /(sym::pNode<U>, sym::var<U>); //defined
		template<class U>
		friend sym::AD<U> operator ^(sym::pNode<U>, sym::var<U>); //defined

		template<class U>
		friend sym::AD<U> operator +(sym::pNode<U>, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> operator -(sym::pNode<U>, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> operator *(sym::pNode<U>, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> operator /(sym::pNode<U>, sym::AD<U>); //defined
		template<class U>
		friend sym::AD<U> operator ^(sym::pNode<U>, sym::AD<U>); //defined

		template<class U>
		friend sym::AD<U> operator +(sym::pNode<U>, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> operator -(sym::pNode<U>, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> operator *(sym::pNode<U>, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> operator /(sym::pNode<U>, sym::pNode<U>); //defined
		template<class U>
		friend sym::AD<U> operator ^(sym::pNode<U>, sym::pNode<U>); //defined

		/**Advanced operations*/
		/**Gradient*/
		template <class U>
		friend std::vector<U> grad(AD<U>);

		/**Jacobian*/
		template <class U>
		friend matrix<U> jacobian(int, AD<U>*);
	};


	template<class T>
	sym::AD<T> copyAD(sym::AD<T> G) {
		sym::AD<T> H;
		H.setval(G.getval());
		H.seteval(cloneNode(G.geteval()));
		return H;
	}

	template<class T>
	sym::node<T>* cloneNode(sym::node<T>* root) {

		switch (root->gettype()) {
		case 's': { return root; break; }
		case 'v': { return root; break; }
		case 'p': { return cloneNode(root->clone()); break; }
		case 'o': {
			sym::node<T>* O = root->clone();
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
	void sym::AD<T>::disp(int type) {
		switch (type) {
		case 0: this->val.disp(); break;
		case 1: this->eval->InOrderTreeWalk(); break;
		case 2: this->val.disp(); this->eval->InOrderTreeWalk(); break;
		}
	}

	template<class T>
	void sym::AD<T>::reeval() {
		if (this->eval != NULL)
			this->val = eval->getVAL();
	}

	/**Assignment operators */
	template<class T>
	void sym::AD<T>::operator =(T k) {
		sym::scalar<T>* s = new sym::scalar<T>(k);
		this->val = s->getVAL();
		this->eval = s;
	}

	template<class T>
	void sym::AD<T>::operator =(sym::var<T> x) {
		this->val = x.getVAL();
		this->eval = x.getself();
	}

	template<class T>
	void sym::AD<T>::operator =(sym::AD<T> G) {
		this->val = G.val;
		this->eval = G.eval;
	}

	template<class T>
	void sym::AD<T>::operator =(sym::pNode<T> g) {
		this->val = g.getVAL();
		this->eval = g.getself();
	}

	/**unary(AD) */
	template<class T>
	sym::AD<T> sym::AD<T>::operator +() {
		sym::AD<T> H;

		H.val = this->val;
		sym::op<T>* O = new sym::op<T>('+', this->eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator -() {
		sym::AD<T> H;

		H.val = -(this->val);
		sym::op<T>* O = new sym::op<T>('-', this->eval);

		H.eval = O;
		return H;
	}

	/**unary(T) - NOT ALLOWED! */

	/**unary(var) */
	template<class T>
	sym::AD<T> operator +(sym::var<T> x) {
		sym::AD<T> H;

		H.val = x.getVAL();
		sym::op<T>* O = new sym::op<T>('+', x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(sym::var<T> x) {
		sym::AD<T> H;

		H.val = -x.getVAL();
		sym::op<T>* O = new sym::op<T>('-', x.getself());

		H.eval = O;
		return H;
	}

	/**unary(gNode) */
	template<class T>
	sym::AD<T> operator +(sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = g.getVAL();
		sym::op<T>* O = new sym::op<T>('+', g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = -g.getVAL();
		sym::op<T>* O = new sym::op<T>('-', g.getself());

		H.eval = O;
		return H;
	}

	/**binary(AD, T) */
	template<class T>
	sym::AD<T> sym::AD<T>::operator +(T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = this->val + s->getVAL();

		sym::op<T>* O = new sym::op<T>('+', this->eval, s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator -(T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = this->val - s->getVAL();

		sym::op<T>* O = new sym::op<T>('-', this->eval, s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator *(T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);


		H.val = this->val * s->getVAL();

		sym::op<T>* O = new sym::op<T>('*', this->eval, s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator /(T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = this->val / s->getVAL();

		sym::op<T>* O = new sym::op<T>('/', this->eval, s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator ^(T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = this->val ^ s->getVAL();

		sym::op<T>* O = new sym::op<T>('^', this->eval, s);

		H.eval = O;
		return H;
	}

	/**binary(AD, var) */
	template<class T>
	sym::AD<T> sym::AD<T>::operator +(sym::var<T> x) {
		sym::AD<T> H;

		H.val = this->val + x.getVAL();

		sym::op<T>* O = new sym::op<T>('+', this->eval, x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator -(sym::var<T> x) {
		sym::AD<T> H;

		H.val = this->val - x.getVAL();

		sym::op<T>* O = new sym::op<T>('-', this->eval, x.getself());

		H.eval = O;
		return H;
	}


	template<class T>
	sym::AD<T> sym::AD<T>::operator *(sym::var<T> x) {
		sym::AD<T> H;

		H.val = this->val * x.getVAL();

		sym::op<T>* O = new sym::op<T>('*', this->eval, x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator /(sym::var<T> x) {
		sym::AD<T> H;

		H.val = this->val / x.getVAL();

		sym::op<T>* O = new sym::op<T>('/', this->eval, x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator ^(sym::var<T> x) {
		sym::AD<T> H;

		H.val = this->val ^ x.getVAL();

		sym::op<T>* O = new sym::op<T>('^', this->eval, x.getself());

		H.eval = O;
		return H;
	}

	/**binary(AD, AD) */
	template<class T>
	sym::AD<T> sym::AD<T>::operator +(sym::AD<T> G) {
		sym::AD<T> H;

		H.val = this->val + G.val;

		sym::op<T>* O = new sym::op<T>('+', this->eval, G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator -(sym::AD<T> G) {
		sym::AD<T> H;

		H.val = this->val - G.val;

		sym::op<T>* O = new sym::op<T>('-', this->eval, G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator *(sym::AD<T> G) {
		sym::AD<T> H;

		H.val = this->val * G.val;

		sym::op<T>* O = new sym::op<T>('*', this->eval, G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator /(sym::AD<T> G) {
		sym::AD<T> H;

		H.val = this->val / G.val;

		sym::op<T>* O = new sym::op<T>('/', this->eval, G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator ^(sym::AD<T> G) {
		sym::AD<T> H;

		H.val = this->val ^ G.val;

		sym::op<T>* O = new sym::op<T>('^', this->eval, G.eval);

		H.eval = O;
		return H;
	}

	/**binary(AD, gNode) */
	template<class T>
	sym::AD<T> sym::AD<T>::operator +(sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = this->val + g.getVAL();

		sym::op<T>* O = new sym::op<T>('+', this->eval, g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator -(sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = this->val - g.getVAL();

		sym::op<T>* O = new sym::op<T>('-', this->eval, g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator *(sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = this->val * g.getVAL();

		sym::op<T>* O = new sym::op<T>('*', this->eval, g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator /(sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = this->val / g.getVAL();

		sym::op<T>* O = new sym::op<T>('/', this->eval, g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> sym::AD<T>::operator ^(sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = this->val ^ g.getVAL();

		sym::op<T>* O = new sym::op<T>('^', this->eval, g.getself());

		H.eval = O;
		return H;
	}

	/**binary(T, T) - NOT ALLOWED! */

	/**binary(T, var) */
	template<class T>
	sym::AD<T> operator +(T k, sym::var<T> x) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() + x.getVAL();

		sym::op<T>* O = new sym::op<T>('+', s, x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(T k, sym::var<T> x) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() - x.getVAL();

		sym::op<T>* O = new sym::op<T>('-', s, x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator *(T k, sym::var<T> x) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() * x.getVAL();

		sym::op<T>* O = new sym::op<T>('*', s, x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator /(T k, sym::var<T> x) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() / x.getVAL();

		sym::op<T>* O = new sym::op<T>('/', s, x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator ^(T k, sym::var<T> x) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() ^ x.getVAL();

		sym::op<T>* O = new sym::op<T>('^', s, x.getself());

		H.eval = O;
		return H;
	}

	/**binary(T, AD) */
	template<class T>
	sym::AD<T> operator +(T k, sym::AD<T> G) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() + G.val;

		sym::op<T>* O = new sym::op<T>('+', s, G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(T k, sym::AD<T> G) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() - G.val;

		sym::op<T>* O = new sym::op<T>('-', s, G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator *(T k, sym::AD<T> G) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() * G.val;

		sym::op<T>* O = new sym::op<T>('*', s, G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator /(T k, sym::AD<T> G) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() / G.val;

		sym::op<T>* O = new sym::op<T>('/', s, G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator ^(T k, sym::AD<T> G) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() ^ G.val;

		sym::op<T>* O = new sym::op<T>('^', s, G.eval);

		H.eval = O;
		return H;
	}

	/**binary(T, gNode) */
	template<class T>
	sym::AD<T> operator +(T k, sym::pNode<T> g) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() + g.getVAL();

		sym::op<T>* O = new sym::op<T>('+', s, g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(T k, sym::pNode<T> g) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() - g.getVAL();

		sym::op<T>* O = new sym::op<T>('-', s, g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator *(T k, sym::pNode<T> g) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() * g.getVAL();

		sym::op<T>* O = new sym::op<T>('*', s, g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator /(T k, sym::pNode<T> g) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() / g.getVAL();

		sym::op<T>* O = new sym::op<T>('/', s, g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator ^(T k, sym::pNode<T> g) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = s->getVAL() ^ g.getVAL();

		sym::op<T>* O = new sym::op<T>('^', s, g.getself());

		H.eval = O;
		return H;
	}

	/**binary(var, T) */
	template<class T>
	sym::AD<T> operator +(sym::var<T> x, T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = x.getVAL() + s->getVAL();

		sym::op<T>* O = new sym::op<T>('+', x.getself(), s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(sym::var<T> x, T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = x.getVAL() - s->getVAL();

		sym::op<T>* O = new sym::op<T>('-', x.getself(), s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator *(sym::var<T> x, T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = x.getVAL() * s->getVAL();

		sym::op<T>* O = new sym::op<T>('*', x.getself(), s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator /(sym::var<T> x, T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = x.getVAL() / s->getVAL();

		sym::op<T>* O = new sym::op<T>('/', x.getself(), s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator ^(sym::var<T> x, T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = x.getVAL() ^ s->getVAL();

		sym::op<T>* O = new sym::op<T>('^', x.getself(), s);

		H.eval = O;
		return H;
	}

	/**binary(var, var) */
	template<class T>
	sym::AD<T> operator +(sym::var<T> x, sym::var<T> y) {
		sym::AD<T> H;

		H.val = x.getVAL() + y.getVAL();

		sym::op<T>* O = new sym::op<T>('+', x.getself(), y.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(sym::var<T> x, sym::var<T> y) {
		sym::AD<T> H;

		H.val = x.getVAL() - y.getVAL();

		sym::op<T>* O = new sym::op<T>('-', x.getself(), y.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator *(sym::var<T> x, sym::var<T> y) {
		sym::AD<T> H;

		H.val = x.getVAL() * y.getVAL();

		sym::op<T>* O = new sym::op<T>('*', x.getself(), y.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator /(sym::var<T> x, sym::var<T> y) {
		sym::AD<T> H;

		H.val = x.getVAL() / y.getVAL();

		sym::op<T>* O = new sym::op<T>('/', x.getself(), y.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator ^(sym::var<T> x, sym::var<T> y) {
		sym::AD<T> H;

		H.val = x.getVAL() ^ y.getVAL();

		sym::op<T>* O = new sym::op<T>('^', x.getself(), y.getself());

		H.eval = O;
		return H;
	}

	/**binary(var, AD) */
	template<class T>
	sym::AD<T> operator +(sym::var<T> x, sym::AD<T> G) {
		sym::AD<T> H;

		H.val = x.getVAL() + G.val;

		sym::op<T>* O = new sym::op<T>('+', x.getself(), G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(sym::var<T> x, sym::AD<T> G) {
		sym::AD<T> H;

		H.val = x.getVAL() - G.val;

		sym::op<T>* O = new sym::op<T>('-', x.getself(), G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator *(sym::var<T> x, sym::AD<T> G) {
		sym::AD<T> H;

		H.val = x.getVAL() * G.val;

		sym::op<T>* O = new sym::op<T>('*', x.getself(), G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator /(sym::var<T> x, sym::AD<T> G) {
		sym::AD<T> H;

		H.val = x.getVAL() / G.val;

		sym::op<T>* O = new sym::op<T>('/', x.getself(), G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator ^(sym::var<T> x, sym::AD<T> G) {
		sym::AD<T> H;

		H.val = x.getVAL() ^ G.val;

		sym::op<T>* O = new sym::op<T>('^', x.getself(), G.eval);

		H.eval = O;
		return H;
	}

	/**binary(var, gNode) */
	template<class T>
	sym::AD<T> operator +(sym::var<T> x, sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = x.getVAL() + g.getVAL();

		sym::op<T>* O = new sym::op<T>('+', x.getself(), g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(sym::var<T> x, sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = x.getVAL() - g.getVAL();

		sym::op<T>* O = new sym::op<T>('-', x.getself(), g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator *(sym::var<T> x, sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = x.getVAL() * g.getVAL();

		sym::op<T>* O = new sym::op<T>('*', x.getself(), g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator /(sym::var<T> x, sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = x.getVAL() / g.getVAL();

		sym::op<T>* O = new sym::op<T>('/', x.getself(), g.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator ^(sym::var<T> x, sym::pNode<T> g) {
		sym::AD<T> H;

		H.val = x.getVAL() ^ g.getVAL();

		sym::op<T>* O = new sym::op<T>('^', x.getself(), g.getself());

		H.eval = O;
		return H;
	}

	/**binary(gNode, T) */
	template<class T>
	sym::AD<T> operator +(sym::pNode<T> g, T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = g.getVAL() + s->getVAL();

		sym::op<T>* O = new sym::op<T>('+', g.getself(), s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(sym::pNode<T> g, T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = g.getVAL() - s->getVAL();

		sym::op<T>* O = new sym::op<T>('-', g.getself(), s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator *(sym::pNode<T> g, T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = g.getVAL() * s->getVAL();

		sym::op<T>* O = new sym::op<T>('*', g.getself(), s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator /(sym::pNode<T> g, T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = g.getVAL() / s->getVAL();

		sym::op<T>* O = new sym::op<T>('/', g.getself(), s);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator ^(sym::pNode<T> g, T k) {
		sym::AD<T> H;
		sym::scalar<T>* s = new sym::scalar<T>(k);

		H.val = g.getVAL() ^ s->getVAL();

		sym::op<T>* O = new sym::op<T>('^', g.getself(), s);

		H.eval = O;
		return H;
	}

	/**binary(gNode, var) */
	template<class T>
	sym::AD<T> operator +(sym::pNode<T> g, sym::var<T> x) {
		sym::AD<T> H;

		H.val = g.getVAL() + x.getVAL();

		sym::op<T>* O = new sym::op<T>('+', g.getself(), x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(sym::pNode<T> g, sym::var<T> x) {
		sym::AD<T> H;

		H.val = g.getVAL() - x.getVAL();

		sym::op<T>* O = new sym::op<T>('-', g.getself(), x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator *(sym::pNode<T> g, sym::var<T> x) {
		sym::AD<T> H;

		H.val = g.getVAL() * x.getVAL();

		sym::op<T>* O = new sym::op<T>('*', g.getself(), x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator /(sym::pNode<T> g, sym::var<T> x) {
		sym::AD<T> H;

		H.val = g.getVAL() / x.getVAL();

		sym::op<T>* O = new sym::op<T>('/', g.getself(), x.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator ^(sym::pNode<T> g, sym::var<T> x) {
		sym::AD<T> H;

		H.val = g.getVAL() ^ x.getVAL();

		sym::op<T>* O = new sym::op<T>('^', g.getself(), x.getself());

		H.eval = O;
		return H;
	}

	/**binary(gNode, AD) */
	template<class T>
	sym::AD<T> operator +(sym::pNode<T> g, sym::AD<T> G) {
		sym::AD<T> H;

		H.val = g.getVAL() + G.val;

		sym::op<T>* O = new sym::op<T>('+', g.getself(), G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(sym::pNode<T> g, sym::AD<T> G) {
		sym::AD<T> H;

		H.val = g.getVAL() - G.val;

		sym::op<T>* O = new sym::op<T>('-', g.getself(), G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator *(sym::pNode<T> g, sym::AD<T> G) {
		sym::AD<T> H;

		H.val = g.getVAL() * G.val;

		sym::op<T>* O = new sym::op<T>('*', g.getself(), G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator /(sym::pNode<T> g, sym::AD<T> G) {
		sym::AD<T> H;

		H.val = g.getVAL() / G.val;

		sym::op<T>* O = new sym::op<T>('/', g.getself(), G.eval);

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator ^(sym::pNode<T> g, sym::AD<T> G) {
		sym::AD<T> H;

		H.val = g.getVAL() ^ G.val;

		sym::op<T>* O = new sym::op<T>('^', g.getself(), G.eval);

		H.eval = O;
		return H;
	}

	/**binary(gNode, gNode) */
	template<class T>
	sym::AD<T> operator +(sym::pNode<T> g, sym::pNode<T> h) {
		sym::AD<T> H;

		H.val = g.getVAL() + h.getVAL();

		sym::op<T>* O = new sym::op<T>('+', g.getself(), h.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator -(sym::pNode<T> g, sym::pNode<T> h) {
		sym::AD<T> H;

		H.val = g.getVAL() - h.getVAL();

		sym::op<T>* O = new sym::op<T>('-', g.getself(), h.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator *(sym::pNode<T> g, sym::pNode<T> h) {
		sym::AD<T> H;

		H.val = g.getVAL() * h.getVAL();

		sym::op<T>* O = new sym::op<T>('*', g.getself(), h.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator /(sym::pNode<T> g, sym::pNode<T> h) {
		sym::AD<T> H;

		H.val = g.getVAL() / h.getVAL();

		sym::op<T>* O = new sym::op<T>('/', g.getself(), h.getself());

		H.eval = O;
		return H;
	}

	template<class T>
	sym::AD<T> operator ^(sym::pNode<T> g, sym::pNode<T> h) {
		sym::AD<T> H;

		H.val = g.getVAL() ^ h.getVAL();

		sym::op<T>* O = new sym::op<T>('^', g.getself(), h.getself());

		H.eval = O;
		return H;
	}

	/**Advanced operations*/
	template<class T>
	std::vector<T> grad(sym::AD<T> G) {
		counter idc;
		std::vector<T> V(idc.getCount(), 0);
		for (int i = 0; i < idc; i++)
			V[i] = G.val[i];

		return V;
	}

	template<class T>
	matrix<T> jacobian(int n, std::vector<sym::AD<T>> AD_list) {
		counter idc;
		matrix<T> M(n, idc.getCount());
		for (int i = 0; i < n; i++)
			for (int j = 0; j < idc; j++)
				M(i, j) = AD_list[i].val[j];

		return M;
	}
}