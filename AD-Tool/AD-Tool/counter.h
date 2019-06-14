#pragma once

#include<memory>

static unsigned int count = 0;

class counter {
private:
	unsigned int* pcount;
public:
	counter() {
		this->pcount = &(::count);
	}

	counter(unsigned int i) {
		this->pcount = &(::count);
		::count = i;
	}

	unsigned int getCount() const {
		return *pcount;
	}

	// pre-increment operator
	unsigned int operator++() {
		return ++(*pcount);
	}

	// pre-decrement operator
	unsigned int operator--() {
		if ((*pcount) != 0)
			return --(*pcount);
		else
			return (*pcount);
	}

	// post-increment operator
	unsigned int operator++(int) {
		unsigned int old = *pcount;
		++(*pcount);
		return old;
	}

	// post-decrement operator
	unsigned int operator--(int) {
		unsigned int old = *pcount;

		if (old != 0)
			--(*pcount);

		return old;
	}

	bool operator<(int i) {
		return ((*pcount) < i);
	}

	bool operator<(counter pi) {
		return ((*pcount) < pi.getCount());
	}

	bool operator>(int i) {
		return ((*pcount) > i);
	}

	bool operator>(counter pi) {
		return ((*pcount) > pi.getCount());
	}
};

bool operator<(int i, counter pi) {
	return (i < pi.getCount());
}

bool operator>(int i, counter pi) {
	return (i > pi.getCount());
}