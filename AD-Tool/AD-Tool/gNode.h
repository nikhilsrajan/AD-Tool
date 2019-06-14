#pragma once

#include "node.h"
#include "scalar.h"
#include "var.h"
#include "OP.h"

//#include "AD.h"

#include "VAL.h"

template<class T>
class AD;

/**CLASS: gNode ***************************************/
template<class T>
class gNode :public node<T> {
	node<T>* p, * self;
	char type;
public:
	gNode() { this->p = NULL; this->self = this; this->type = 'g'; }
	gNode(node<T>* P) { this->p = P; this->self = this; this->type = 'g'; }

	void operator =(T k) { this->p = new scalar<T>(k); }
	void operator =(scalar<T> s) { this->p = s.getself(); }
	void operator =(var<T> x) { this->p = x.getself(); }
	void operator =(OP<T> O) { this->p = O.getself(); }
	void operator =(AD<T> G) { this->p = G.geteval(); }

	void setNodePointer(node<T>* new_p) { this->p = new_p; }
	node<T>* getNodePointer() { return this->p; }

	node<T>* clone() { return this->p; }
	VAL<T> getVAL() { return this->p->getVAL(); }
	node<T>* getself() { return this->self; }
	void disp() { this->p->disp(); }
	char gettype() { return this->type; }
};