#pragma once

#include "VAL.h"

template<class T>
class OP :public node<T> {
	OP* self;
	char op, type;

public:
	OP() { this->op = '\0'; this->self = this; this->type = 'o'; }
	OP(char ch) { this->op = ch; this->self = this; this->type = 'o'; }
	OP(char ch, node<T>* L) { this->op = ch; this->setLchild(L); this->self = this; this->type = 'o'; }
	OP(char ch, node<T>* L, node<T>* R) { this->op = ch; this->setLchild(L); this->setRchild(R); this->self = this; this->type = 'o'; }
	OP(OP<T>& O) { this->op = O.op; this->setLchild(O.getLchild()); this->setRchild(O.getRchild()); this->self = this; this->type = 'o'; }

	void operator =(OP<T> O) { this->op = O.op; this->setLchild(O.getLchild()); this->setRchild(O.getRchild()); }

	OP<T>* getself() { return this->self; }
	char gettype() { return this->type; }

	node<T>* clone() { return new OP<T>(*this); }

	void disp() {
		cout << "OP: op = " << this->op << ", address = " << this->self << endl;
	}

	VAL<T> getVAL();
};

template<class T>
VAL<T> OP<T>::getVAL() {
	VAL<T> v;
	switch (this->op) {
	case '+':
		if (this->getRchild() == NULL)
			v = this->getleftVAL();
		else
			v = this->getleftVAL() + this->getrightVAL();
		break;
	case '-':
		if (this->getRchild() == NULL)
			v = -(this->getleftVAL());
		else
			v = this->getleftVAL() - this->getrightVAL();
		break;
	case '*': v = this->getleftVAL() * this->getrightVAL(); break;
	case '/': v = this->getleftVAL() / this->getrightVAL(); break;
	case '^': v = this->getleftVAL() ^ this->getrightVAL(); break;
	default: cout << "ERROR: Invalid Operator.\n"; exit(1); break;
	}
	return v;
}