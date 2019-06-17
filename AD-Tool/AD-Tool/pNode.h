#pragma once

#include "node.h"
#include "scalar.h"
#include "var.h"
#include "op.h"

#include "VAL.h"

namespace sym {
	//#include "AD.h"
	template<class T>
	class AD;

	template<class T>
	class pNode :public node<T> {
		node<T>* p, * self;
		char type;
	public:
		pNode() { this->p = NULL; this->self = this; this->type = 'p'; }
		pNode(sym::node<T>* P) { this->p = P; this->self = this; this->type = 'p'; }

		void operator =(T k) { this->p = new sym::scalar<T>(k); }
		void operator =(sym::scalar<T> s) { this->p = s.getself(); }
		void operator =(sym::var<T> x) { this->p = x.getself(); }
		void operator =(sym::op<T> O) { this->p = O.getself(); }
		void operator =(sym::AD<T> G) { this->p = G.geteval(); }

		void setNodePointer(node<T>* new_p) { this->p = new_p; }
		node<T>* getNodePointer() { return this->p; }

		node<T>* clone() { return this->p; }
		VAL<T> getVAL() { return this->p->getVAL(); }
		node<T>* getself() { return this->self; }
		void disp() { this->p->disp(); }
		char gettype() { return this->type; }
	};
}