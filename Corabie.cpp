
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>

using namespace std;

class Corabie {
private:
	const int COD;
	float greutate;
	int nrVele;
	float* vele;
	string nume; //orice corabie are un nume si putem folosi aceasta variabila pentru operatorii de afisare si citire pentru a conferi autenticitate
	int nrMarinari; //putem 

public:
	Corabie() :COD(123) {
		this->greutate = 1000;
		this->nrVele = 2;
		this->vele = new float[this->nrVele];
		this->vele[0] = 3.5;
		this->vele[1] = 2.6;
		this->nume = "Corsaru";
		this->nrMarinari = 10;
	}

	Corabie(float greutate, int nrVele, float* vele, string nume, int nrMarinari, int cod) :COD(cod) {
		if (greutate > 0) {
			this->greutate = greutate;
		}
		if (nrVele > 0) {
			this->nrVele = nrVele;
		}
		this->vele = new float[this->nrVele];
		for (int i = 0; i < this->nrVele; i++) {
			this->vele[0] = vele[i];
		}
		this->nume = nume;
		this->nrMarinari = nrMarinari;
	}

	~Corabie() {
		if (this->vele != NULL) {
			delete[]this->vele;
		}
	}

	Corabie(const Corabie& c) :COD(c.COD) {
		this->greutate = c.greutate;
		this->nrVele = c.nrVele;
		this->vele = new float[this->nrVele];
		for (int i = 0; i < this->nrVele; i++) {
			this->vele[0] = c.vele[i];
		}
		this->nume = c.nume;
		this->nrMarinari = c.nrMarinari;
	}

	void setNume(string nume) {
		this->nume = nume;
	}

	void setNrMarinari(int nrMarinari) {
		this->nrMarinari = nrMarinari;
	}

	string getNume() {
		return this->nume;
	}

	int getNrMarinari() {
		return this->nrMarinari;
	}

	Corabie operator=(Corabie c) {
		this->greutate = c.greutate;
		this->nrVele = c.nrVele;
		if (this->vele != c.vele) {
			delete[]this->vele;
		}
		this->vele = new float[c.nrVele];
		for (int i = 0; i < c.nrVele; i++) {
			this->vele[i] = c.vele[i];
		}
		this->nume = c.nume;
		this->nrMarinari = c.nrMarinari;

		return *this;
	}

	friend ostream& operator<<(ostream& iesire, const Corabie& c);
};

ostream& operator<<(ostream& iesire, const Corabie& c) {
	iesire << c.greutate << " ";
	iesire << c.nrVele << " ";
	iesire << c.COD << " ";
	iesire << c.nume << " ";
	iesire << c.nrMarinari << " ";
	for (int i = 0; i < c.nrVele; i++) {
		iesire << "Vela " << i + 1 << ": " << c.vele[i] << " ";
	}
	return iesire;
}

void main() {
	Corabie c1;
	Corabie c2;

	cout << c2.getNrMarinari() << endl;
	cout << c2.getNume() << endl;

	Corabie c3 = c2;
	cout << c2 << endl;

	cout << c1;
}