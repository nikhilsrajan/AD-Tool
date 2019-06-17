#pragma once

#include <iostream>
#include "VAL.h"

template<class T>
class op :public node<T> {
	op* self;
	char sym, type;

public:
	op() { this->sym = '\0'; this->self = this; this->type = 'o'; }
	op(char ch) { this->sym = ch; this->self = this; this->type = 'o'; }
	op(char ch, node<T>* L) { this->sym = ch; this->setLchild(L); this->self = this; this->type = 'o'; }
	op(char ch, node<T>* L, node<T>* R) { this->sym = ch; this->setLchild(L); this->setRchild(R); this->self = this; this->type = 'o'; }
	op(op<T>& O) { this->sym = O.sym; this->setLchild(O.getLchild()); this->setRchild(O.getRchild()); this->self = this; this->type = 'o'; }

	void operator =(op<T> O) { this->sym = O.sym; this->setLchild(O.getLchild()); this->setRchild(O.getRchild()); }

	op<T>* getself() { return this->self; }
	char gettype() { return this->type; }

	node<T>* clone() { return new op<T>(*this); }

	void disp() {
		std::cout << "OP: op = " << this->sym << ", address = " << this->self << std::endl;
	}

	VAL<T> getVAL();
};

template<class T>
VAL<T> op<T>::getVAL() {
	VAL<T> v;
	switch (this->sym) {
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
	default: std::cout << "ERROR: Invalid Operator.\n"; exit(1); break;
	}
	return v;
}