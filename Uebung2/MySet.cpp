#include "MySet.h"
#include <iostream>

using namespace std;

Set::Set(size_t size) m_values(make_unique<int[]>(capacity)), m_size(0) {
	cout << "private-ctor" << endl;
}



// Vorgegeben aus Kapitel 1.2.3
Set Set::merge(const Set& set) const {
	//erstelle eine neue Menge mit allen Elementen von this
	Set result(m_size + set.m_size);
	std::copy_n(begin(), m_size, result.begin());
	result.m_size = m_size;

	// fuege nur jene Elemente von set dazu, die in this noch nicht enthalten sind

	for (size_t i = 0; i < set.m_size; ++i) {
		if (!contains(set[i])) result[result.m_size++] = set[i];
	}

	return result;
}

