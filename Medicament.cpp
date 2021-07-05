#include <iostream>
#include <fstream>
#include <conio.h>
#include <list>

using namespace std;

class Medicament {
public:
	char* denumire;
	float pret;

	Medicament() {
		denumire = new char[strlen("Medicament") + 1];
		strcpy(denumire, "Medicament");
		pret = 0.0;
	}

	Medicament(char* denumire, double pret) {
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->pret = pret;
	}


	Medicament(const Medicament &p) {
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->pret = p.pret;
	}

	~Medicament() {
		delete[] denumire;
	}

	void operator=(Medicament p) {
		delete[]this->denumire;
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->pret = p.pret;
	}

	void setPret(float pret){
		this->pret = pret;
	}

	void setDenumire(char* denumire) {
		delete[] this->denumire;
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
	}

	friend ostream& operator<<(ostream& out, Medicament m){
		out << m.denumire << ": " << m.pret << " RON";
		return out;
	}
};

class Reteta {
public:
	Medicament *medicamente;
	int n;

	Reteta() {
		n = 0;
		medicamente = NULL;
	}

	Reteta(Medicament *medicamente, int n){
		this->n = n;
		this->medicamente = medicamente;
	}

	Reteta(const Reteta &r) {
		this->n = r.n;
		this->medicamente = r.medicamente;
	}

	friend ostream& operator<<(ostream& out, Reteta r) {
		out << "Reteta contine " << r.n << " medicamente: \n";
		for (int i = 0; i < r.n; i++) {
			out << i+1 << ". " << r.medicamente[i] << endl;
		}
		return out;
	}

	int getN() {
		return n;
	}

	Medicament operator[](int i) {
		return this->medicamente[i];
	}

	void adaugaMedicament(Medicament m) {
		this->n++;
		Medicament *med = new Medicament[this->n];
		for (int i = 0; i < this->n -1; i++) {
			med[i] = this->medicamente[i];
		}

		med[n - 1] = m;
		delete[] this->medicamente;
		this->medicamente = med;
	}

	virtual double GetValoare() {
		double sum = 0;
		for (int i = 0; i < n; i++) {
			sum += medicamente[i].pret;
		}
		return sum;
	}
};

class RetetaCompensata :public Reteta {
private:
	float procentCompensat;

public:
	RetetaCompensata(float procentCompensat) :Reteta() {
		this->procentCompensat = procentCompensat;
	}

	RetetaCompensata(Reteta r, float procentCompensat) :Reteta() {
		this->procentCompensat = procentCompensat;
		this->n = r.n;
		delete[] this->medicamente;
		this->medicamente = r.medicamente;
	}


	RetetaCompensata(Medicament *medicamente, int n, float procentCompensat) : Reteta(medicamente, n) {
		if (procentCompensat > 0 && procentCompensat <1) this->procentCompensat = procentCompensat;
		else cout << "Valoarea procentului trebuie sa fie intre 0 si 1)";
	}

	virtual double GetValoare() {
		double sum = 0;
		for (int i = 0; i < n; i++) {
			sum += medicamente[i].pret;
		}

		return sum - sum*procentCompensat;
	}

};

void main() {
	Medicament nurofen("Nurofen", 11.25f);
	Medicament aspirina = nurofen;
	aspirina.setDenumire("Aspirina");
	aspirina.setPret(4.5f);
	Medicament bixtonim("Bitxtonim", 8.2f);
	Medicament temp;
	temp = nurofen;
	cout << temp << endl;
	cout << nurofen << endl;
	cout << aspirina << endl;

	Medicament medicamente[] = { aspirina, nurofen };
	Reteta r0(medicamente, 2);
	cout << r0 << endl;
	Reteta r1;
	r1.adaugaMedicament(nurofen);
	r1.adaugaMedicament(aspirina);

	cout << "Ete medicamentele: \n";
	for (int i = 0; i < r1.getN(); i++) {
		cout << r1[i] << endl;
	}

	RetetaCompensata r2(0.5);
	r2.adaugaMedicament(bixtonim);
	r2.adaugaMedicament(aspirina);

	RetetaCompensata r3(r1, 0.2);
	Reteta *p = &r1;
	cout << p->GetValoare() << endl;
	p = &r3;
	cout << p->GetValoare() << endl;

	list<Reteta> lista;
	lista.push_back(r0);
	lista.push_back(r1);
	lista.push_back(r2);
	lista.push_back(r3);

	list<Reteta> ::iterator i;
	for (i = lista.begin(); i != lista.end(); i++) {
		cout << (*i) << endl << (*i).GetValoare() << endl << endl;
	}
	_getch();
}