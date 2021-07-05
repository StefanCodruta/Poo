#include<iostream>
#include<string>

using namespace std;
class Vapor {
	int capacitate;
	int nrPersImbarcate;

	int* varstePasageri;
	string denumire;

	static int contor;
public:
	Vapor() {
		cout << endl << "apel const implicit";
		this->capacitate = 0;
		this->nrPersImbarcate = 0;
		this->nrPersImbarcate = NULL;
		this->denumire = " ";

		contor++;
	}
	Vapor(int capacitate, int nrPersImbarcate, int* varstaPasageri, string denumire) {

		this->capacitate = capacitate;
		this->nrPersImbarcate = nrPersImbarcate;
		this->varstePasageri = new int[nrPersImbarcate];
		for (int i = 0; i < nrPersImbarcate; i++) {
			this->varstePasageri[i] = varstaPasageri[i];
		}
		this->denumire = denumire;

		contor++;

	}
	~Vapor() {
		if (this->varstePasageri != NULL)
			delete[]this->varstePasageri;
	}

	int getCapacitate() {
		return this->capacitate;
	}
	string getDenumire() {
		return this->denumire;
	}
	void set_capacitate(int capacitate) {
		
		if (this->nrPersImbarcate < this->capacitate) {
			this->capacitate = capacitate;
		}
		else {
			throw"nr persoanele depaseste limita vaporului";
		}
	}
	Vapor(const Vapor& copie) {

		this->capacitate = copie.capacitate;
		this->denumire = copie.denumire;
		this->nrPersImbarcate = copie.nrPersImbarcate;
		this->varstePasageri = new int[copie.nrPersImbarcate];
		for (int i = 0; i < copie.nrPersImbarcate; i++) {
			this->varstePasageri[i] = copie.varstePasageri[i];
		}
	}

	Vapor operator=(const Vapor& v) {
		this->capacitate = v.capacitate;
		this->denumire = v.denumire;
		this->nrPersImbarcate = v.nrPersImbarcate;
		if (this->varstePasageri != NULL)
			delete[] this->varstePasageri;

		this->varstePasageri = new int[v.nrPersImbarcate];
		for (int i = 0; i < v.nrPersImbarcate; i++) {
			this->varstePasageri[i] = v.varstePasageri[i];
		}
		return v;
	}

	int calculareVarstaMedie() {
		int medie = 0;
		for (int i = 0; i < this->nrPersImbarcate; i++) {
			medie += this->varstePasageri[i]/ 2;
		}
		return medie;
	}

	//cast
	//explicit operator int() {
	//	for (int i = 0; i < nrPersImbarcate; i++) {
	//		if (this->varstePasageri[i] < 18)
	//			return this->nrPersImbarcate;
	//		else
	//			return this->nrPersImbarcate;
	//	}
	//}
	//
 //operator functie
	//int operator()() {
	//	return this->capacitate - this->nrPersoaneImbarcate;
	//}

	friend ostream& operator<<(ostream& out, Vapor& v);
};

ostream& operator<<(ostream& out, Vapor& v) {
	out << endl << "---------------------------";
	out << endl << "denumire" << v.denumire;
	out << endl << "capacitate: " << v.capacitate;
	out << endl << "nr pers imbarcate:" << v.nrPersImbarcate;
	for (int i = 0; i < v.nrPersImbarcate; i++) {
		out << "varste:" << i + 1 << ":" << v.varstePasageri[i] << " ";
	}
	return out;
}

int Vapor::contor = 0;
int main() {

	Vapor v1;
	int v[] = { 20,40,30 };

	Vapor v2(100, 3,v, "ancora");
	cout << v1;

	cout << v2;
	cout << v2.calculareVarstaMedie();

	Vapor v3 = v2;
	cout << v3;

	Vapor v4;
	v4 = v1;
	cout <<v1;

	int t[] = { 16, 20 };
	Vapor v5(100, 2, t, "ancora2");
	
	cout << (int)v5 << endl;


 }