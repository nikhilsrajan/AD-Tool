#pragma once

#include <iostream>
#include <cmath>
#include <cstdlib>

using namespace std;

template<class T>
class vector
{
	T* v;
	int size;
public:
	vector()
	{

	}
	vector(int k)
	{
		size = k;
		v = new T[size];
	}
	vector(int k, T c)
	{
		size = k;
		v = new T[size];
		for (int i = 0; i < size; i++)
			v[i] = c;
	}
	void input();
	void disp();
	vector operator +(vector);
	vector operator -(vector);
	T& operator [] (int);
	template<class U>
	friend vector<U> operator *(U, vector<U>);
	template<class U>
	friend int size_of(vector<U>);
	template <class U>
	friend U norm(vector<U>);
};

template<class T>
void vector<T>::input()
{
	cout << "Enter the size of the right hand vector\n";
	cin >> size; // (Using this we can also take size of the vector as input from the user)
	v = new T(size);
	cout << "Enter the elements\n";
	for (int i = 0; i < size; i++)
		cin >> v[i];
}

template<class T>
void vector<T>::disp()
{
	for (int i = 0; i < size; i++)
		cout << v[i] << "   ";
}

template <class T>
vector<T> vector<T>::operator +(vector u)
{
	vector w;
	if (size == u.size)
	{
		w = vector(size);
		for (int i = 0; i < w.size; i++)
			w.v[i] = v[i] + u.v[i];
		return w;
	}
	else
	{
		cout << "\n Pls input two vectors of same size";
		exit(0);
	}
}

template <class T>
vector<T> vector<T>::operator -(vector u)
{
	vector w;
	if (size == u.size)
	{
		w = vector(size);
		for (int i = 0; i < w.size; i++)
			w.v[i] = v[i] - u.v[i];
		return w;
	}
	else
	{
		cout << "\nPls input two vectors of same size";
		exit(0);
	}
}

template <class T>
vector<T> operator *(T k, vector<T> u)
{
	vector<T> w(u.size);
	for (int i = 0; i < u.size; i++)
		w.v[i] = k * u.v[i];
	return w;
}

template<class T>
int size_of(vector<T> u)
{
	return u.size;
}

template<class T>
T& vector<T>::operator [] (int k)
{
	if (k < size)
		return v[k];
	else
	{
		cout << "Index out of bound !";
		exit(0);
	}
}

template <class T>
T norm(vector<T> u)
{
	T s = 0.0;
	for (int i = 0; i < u.size; i++)
		s = s + u.v[i] * u.v[i];
	return sqrt(s);
}
