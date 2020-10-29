#include "MySet.h"
#include <iostream>

using namespace std;


// Konstruktoren
Set::Set(size_t capacity) : m_values(make_unique<int[]>(capacity)), m_size(0) {
	cout << "private-ctor" << endl;
}

// "Standart" Konstruktor
Set::Set() : m_size(0) {}

// Kopierkonstruktor
Set::Set(const Set& set) : m_values(set.m_values), m_size(set.m_size) {}

// Typkonvertkonstruktor: Test Driven aus UnitTest.cpp --> TEST_METHOD(Creation) s4
// Set::Set(initializer_list<int> intializer_list){}

// Destruktor, mit Ausgabe für debugging purposes (in Kapitel 1.2.2 empfohlen)
Set::~Set() {
	cout << "Set destruktor aufgerufen" << endl;
	//https://en.cppreference.com/w/cpp/memory/shared_ptr/reset
	m_values.reset();
}


// Pruefen ob e in set enthalten ist
bool Set::contains(int e) const {
	for (size_t i = 0; i < m_size; i++) {
		if (m_values[i] == e) return true;
	}
	return false;
}

// Pruefen ob alle Elemente enthalten sind
bool Set::containsAll(const Set& set) const {
	for (size_t i = 0; i < m_size; i++) {
		if (!contains(set[i])) return false;
	}
	return true;
}

// Pruefen ob empty
bool Set::isEmpty() const {
	return 0 == m_size;
}

// Groesse zuruekgeben
size_t Set::size() const {
	return m_size;
}

// Liefert einen Pointer auf m_values start
int* Set::begin() const {

	// https://en.cppreference.com/w/cpp/memory/shared_ptr/get
	return m_values.get();
}

//TODO
int& Set::operator[](size_t) {
	// TODO: hier return-Anweisung eingeben
}

//TODO
int Set::operator[](size_t i) const {
	return 0;
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

//TODO
Set Set::difference(const Set& set) const{
	return Set();
}

// TODO
Set Set::intersection(const Set& set) const{
	return Set();
}



