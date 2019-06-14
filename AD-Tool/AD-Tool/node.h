#pragma once

#include "VAL.h"

using namespace std;

template<class T>
class node {
protected:
	node* Lchild, * Rchild;

public:
	node() { Lchild = NULL; Rchild = NULL; }
	virtual VAL<T> getVAL() = 0;
	virtual node<T>* getself() = 0;
	virtual void disp() = 0;
	virtual char gettype() = 0;
	virtual node<T>* clone() = 0;

	void InOrderTreeWalk();

	void setLchild(node* p) { this->Lchild = p; }
	void setRchild(node* p) { this->Rchild = p; }

	node<T>* getLchild() { return this->Lchild; }
	node<T>* getRchild() { return this->Rchild; }

	VAL<T> getleftVAL() { return Lchild->getVAL(); }
	VAL<T> getrightVAL() { return Rchild->getVAL(); }
};

template<class T>
void node<T>::InOrderTreeWalk() {
	if (this->Lchild != NULL) {
		cout << "LEFT: ";
		this->Lchild->InOrderTreeWalk();
	}

	cout << "THIS ";
	cout << " [" << this->gettype() << "] : ";
	this->disp();

	if (this->Rchild != NULL) {
		cout << "RGHT: ";
		this->Rchild->InOrderTreeWalk();
	}
}