#pragma once

using namespace std;

template<class T>
class node

template<class T>
class scalar :public node<T> {
	T val;
	scalar<T>* self;
	char type;

public:
	scalar() { this->self = this; this->type = 's'; }
	scalar(T k) { this->val = k; this->self = this; this->type = 's'; }

	T getval() { return val; }

	void operator =(T k) { this->val = k; }
	void operator =(scalar<T> s) { this->val = s.val; }

	void disp() {
		cout << "SCALAR: val = " << this->val << ", address = " << this->self << endl;
	}
	node<T>* clone() { return this; }
	scalar<T>* getself() { return this->self; }
	char gettype() { return this->type; }
	VAL<T> getVAL();
};

template<class T>
VAL<T> scalar<T>::getVAL() {
	VAL<T> v;
	v.input_f(this->val);
	T* df = new T[idc];

	for (int i = 0; i < idc; i++)
		df[i] = 0.0;

	v.input_df(df);

	return v;
}