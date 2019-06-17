#pragma once

#include <iostream>
#include "node.h"
#include "VAL.h"
#include "counter.h"

template<class T>
class var :public node<T> {
	counter idc;
	int id;
	T val;
	var<T>* self;
	char type;

public:
	var() { this->id = idc++; this->self = this; this->type = 'v'; }
	var(T k) { this->id = idc++; this->val = k; this->self = this; this->type = 'v'; }

	void operator =(T k) { this->val = k; }
	void operator =(scalar<T> s) { this->p = s.getval(); }
	void operator =(var<T> x) { this->val = x.val; }

	void disp() {
		std::cout << "VAR: id = " << this->id << ", val = " << this->val << ", address = " << this->self << std::endl;
	}
	node<T>* clone() { return this; }
	var<T>* getself() { return this->self; }
	char gettype() { return this->type; }
	VAL<T> getVAL();
};

template<class T>
VAL<T> var<T>::getVAL() {
	VAL<T> v;
	v.input_f(this->val);
	std::vector<T> df(idc.getCount(), 0.0);

	df[this->id] = 1.0;

	v.input_df(df);

	return v;
}