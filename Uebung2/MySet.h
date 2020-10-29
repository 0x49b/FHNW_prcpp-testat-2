#pragma once

class Set {
protected:
	// protected Datenstruktur (erlaubt Vererbung
	size_t m_size;
	shared_ptr<int[]> m_values;
	explicit Set(size_t size);

	// gesch�tzte Instanzmethoden
	int* begin() const;						// gibt einen Zeiger auf das erste Element der Menge zur�ck (nullptr falls leer)
	int& operator[](size_t);				// gibt das i-te Element des Mengen-Arrays zurueck
	int operator[](size_t i) const;			// wie auf Zeile vorher, jedoch nur einen Lesezugriff

	Set merge(const Set& set) const;		// gibt als neue Menge die Vereinigunsmenge dieser Menge mit set zurueck
	Set difference(const Set& set) const;	//gibt als neue Menge die Differenzmenge zwischen set und dieser Methode (set \ this) zurueck
	Set intersection(const Set& set) const; // gibt als Menge die Schnittmenge dieser Menge mit set zur�ck


public:
	// Oeffentliche Methoden


	// Konstruktoren und Desktruktor
	//Konstruktor
	Set();				 // Default Konstruktor
	Set(const Set& set); // Copy Konstruktor
	Set(initializer_list<int> intializer_list);	// Typkonvertierungs Konstruktor

	// Destruktor
	~Set();

	// Instanzmethoden
	// testet ob die Menge e enth�lt; 
	bool contains(int e) const;

	// testet, ob diese Menge alle Elemente der andere Menge enh�lt (und somit deren Supermenge ist)
	bool containsAll(const Set& set) const;

	// testet ob die Menge leer ist
	bool isEmpty() const;

	// gibt die Anzahl Elemente in der Menge zurueck
	size_t size() const;

	// Gleichheitsoperator ('equals' in Java); inline Implementierung schon gegeben
	bool operator==(const Set& set) const { return size() == set.size() && containsAll(set) && set.containsAll(*this); }

	// Ausgabe-Operator fuer Output-Streams (Inline-Implementierung schon gegeben)
	friend ostream& operator<<(ostream& os, const Set& s) {
		const int* const vptr = s.begin();
		os << "{";
		if (!s.isEmpty()) os << vptr[0];
		for (size_t i = 1; i < s.m_size; ++i) { os << "," << vptr[i]; }
		os << "}";
		return os;
	}

	// Klassen-Methoden
	// Vereinigungsmenge (die Bezeichnung union ist nicht m�glich)
	static Set merge(const Set& set1, const Set& set2) { return set1.merge(set2); }

	//Differenzmenge
	static Set difference(const Set& set1, const Set& set2) { return set2.difference(set1); }

	//Schnittmenge
	static Set intersection(const Set& set1, const Set& set2) { return set1.intersection(set2); }

};