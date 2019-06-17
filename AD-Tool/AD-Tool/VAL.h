#pragma once
#include <iostream>
#include <vector>

#include "counter.h"

namespace sym {
	template <class T>
	class VAL {
		T f;
		std::vector<T> df;
		counter idc;
	public:
		VAL();

		void disp() {
			std::cout << "f = " << this->f << std::endl;
			std::cout << "df = ";
			for (int i = 0; i < idc; i++)
				std::cout << this->df[i] << "   ";
			std::cout << std::endl;
		}

		void input_f(T k) { this->f = k; }
		void input_df(std::vector<T> dk) { this->df = dk; }

		T getf() { return f; }

		T& operator [] (int);

		/**Member Functions*/
		/**Unary operators*/
		VAL operator +(); //defined
		VAL operator -(); //defined

		/**Binary operators*/
		void operator =(VAL); // defined
		VAL operator +(VAL); // defined
		VAL operator -(VAL); // defined
		VAL operator *(VAL); // defined
		VAL operator /(VAL); // defined
		VAL operator ^(VAL); // defined
	};
}

template<class T>
sym::VAL<T>::VAL() {
	this->f = 0.0;
	this->df = std::vector<T>(idc.getCount(), 0.0);
}

template<class T>
T& sym::VAL<T>::operator [] (int k) {
	if (k < idc)
		return df[k];
	else {
		std::cout << "Index out of bound!";
		exit(1);
	}
}

/**VAL: Operator Overloading*/
template<class T>
void sym::VAL<T>::operator =(VAL g) {
	this->f = g.f;
	for (int i = 0; i < idc; i++)
		this->df[i] = g.df[i];
}

template<class T>
sym::VAL<T> sym::VAL<T>::operator +() {
	VAL<T> h;
	h.f = f;
	for (int i = 0; i < idc; i++)
		h.df[i] = this->df[i];
	return h;
}

template<class T>
sym::VAL<T> sym::VAL<T>::operator -() {
	VAL<T> h;
	h.f = -(this->f);
	for (int i = 0; i < idc; i++)
		h.df[i] = -(this->df[i]);
	return h;
}

template<class T>
sym::VAL<T> sym::VAL<T>::operator +(sym::VAL<T> g) {
	sym::VAL<T> h;
	h.f = this->f + g.f;
	for (int i = 0; i < idc; i++)
		h.df[i] = this->df[i] + g.df[i];
	return h;
}

template<class T>
sym::VAL<T> sym::VAL<T>::operator -(sym::VAL<T> g) {
	VAL<T> h;
	h.f = this->f - g.f;
	for (int i = 0; i < idc; i++)
		h.df[i] = this->df[i] - g.df[i];
	return h;
}

template<class T>
sym::VAL<T> sym::VAL<T>::operator *(sym::VAL<T> g) {
	VAL<T> h;
	h.f = this->f * g.f;
	for (int i = 0; i < idc; i++)
		h.df[i] = g.f * (this->df[i]) + this->f * g.df[i];
	return h;
}

template<class T>
sym::VAL<T> sym::VAL<T>::operator /(sym::VAL<T> g) {
	if (g.f == 0) {
		std::cout << "MATH ERROR: Division by Zero!\n";
		exit(1);
	}
	else {
		sym::VAL<T> h;
		h.f = this->f / g.f;
		for (int i = 0; i < idc; i++)
			h.df[i] = this->df[i] / g.f - this->f * g.df[i] / (g.f * g.f);
		return h;
	}
}

template<class T>
sym::VAL<T> sym::VAL<T>::operator ^(sym::VAL<T> g) {
	sym::VAL<T> h;
	if (this->f == 0 && g.f == 0) {
		std::cout << "MATH ERROR: 0^0 Undefined!\n";
		exit(1);
	}
	else if (this->f == 0 && g.f < 0) {
		std::cout << "MATH ERROR: Division by Zero!\n";
		exit(1);
	}
	else
		h.f = pow(this->f, g.f);

	int g_df = 0;

	for (int i = 0; i < idc && g_df == 0; i++)
		if (g.df[i] != 0)
			g_df = 1;

	if (g_df == 0) {
		if (this->f != 0) {
			for (int i = 0; i < idc; i++)
				h.df[i] = pow(this->f, (g.f - 1)) * g.f * this->df[i];
		}
		else if (g.f > 1) {
			for (int i = 0; i < idc; i++)
				h.df[i] = 0.0;
		}
		else {
			std::cout << "MATH ERROR: Division by Zero!\n";
			exit(1);
		}
	}
	else if (this->f > 0) {
		for (int i = 0; i < idc; i++)
			h.df[i] = pow(this->f, (g.f - 1)) * g.f * this->df[i] + pow(this->f, g.f) * g.df[i] * log(this->f);
	}
	else {
		std::cout << "MATH ERROR: LOG undefined for values <= 0!\n";
		exit(1);
	}
	return h;
}
