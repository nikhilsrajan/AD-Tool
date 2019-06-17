#pragma once

#include <iostream>
#include "VAL.h"
#include "node.h"
#include "counter.h"

namespace sym {
	template<class T>
	class scalar : public node<T> {
		T val;
		scalar<T>* self;
		char type;
		counter idc;

	public:
		scalar() { this->self = this; this->type = 's'; }
		scalar(T k) { this->val = k; this->self = this; this->type = 's'; }

		T getval() { return val; }

		void operator =(T k) { this->val = k; }
		void operator =(scalar<T> s) { this->val = s.val; }

		void disp() {
			std::cout << "SCALAR: val = " << this->val << ", address = " << this->self << std::endl;
		}
		node<T>* clone() { return this; }
		scalar<T>* getself() { return this->self; }
		char gettype() { return this->type; }
		VAL<T> getVAL();
	};
}

template<class T>
sym::VAL<T> sym::scalar<T>::getVAL() {
	VAL<T> v;
	v.input_f(this->val);
	std::vector<T> df(idc.getCount(), 0.0);

	v.input_df(df);

	return v;
}