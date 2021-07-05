#include <iostream>
#include <fstream>
#include <conio.h>
#include <list>

using namespace std;

class Avocat {
private:
	const int COD;
	char *nume;
	int onorariu;
	int nrProcese;
	int *vectorProcese;

public:
	Avocat(): COD(0) {
		nume = new char[strlen("Anonim") + 1];
		strcpy(nume, "Anonim");
		onorariu = 0;
		nrProcese = 0;
		vectorProcese = NULL;
	}

	Avocat(const int COD, char* nume, int onorariu, int nrProcese, int *vectorProcese): COD(COD) {
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
		this->onorariu = onorariu;
		this->nrProcese = nrProcese;

		this->vectorProcese = new int[this->nrProcese];
		for (int i = 0; i < this->nrProcese; i++) {
			this->vectorProcese[i] = vectorProcese[i];
		}
	}

	Avocat(const Avocat &a): COD(a.COD) {
		this->nume = new char[strlen(a.nume) + 1];
		strcpy(this->nume, a.nume);

		this->onorariu = a.onorariu;
		this->nrProcese = a.nrProcese;

		this->vectorProcese = new int[a.nrProcese];
		for (int i = 0; i < this->nrProcese; i++) {
			this->vectorProcese[i] = a.vectorProcese[i];
		}
	}

	~Avocat() {
		delete[] nume;
	}

	void operator=(Avocat a) {
		delete[] this->nume;
		this->nume = new char[strlen(a.nume) + 1];
		strcpy(this->nume, a.nume);

		this->onorariu = a.onorariu;
		this->nrProcese = a.nrProcese;

		this->vectorProcese = new int[a.nrProcese];
		for (int i = 0; i < this->nrProcese; i++) {
			this->vectorProcese[i] = a.vectorProcese[i];
	}

	char* getNume() {
		return nume;
	}
	
	void setNume(char* nume) {
		delete[] this->nume;
		this->nume = new char[strlen(nume) + 1];
		strcpy(this->nume, nume);
	}

	const int getIdentificator() {
		return COD;
	}

	int* getVectorProcese() {
		return vectorProcese;
	}

	void setVectorProcese(int *vectorProcese, int nrProcese) {
		this->nrProcese = nrProcese;

		delete[] this->vectorProcese;
		this->vectorProcese = new int[this->nrProcese];
		for (int i = 0; i < this->nrProcese; i++) {
			this->vectorProcese[i] = vectorProcese[i];
		}
	}

	double valMedieProces() {
		double sum = 0;
		for (int i = 0; i < nrProcese; i++) {
			sum += vectorProcese[i];
		}

		return sum / nrProcese;
	}

	Avocat operator+(int x) {
		Avocat temp = (*this);
		int *v = new int[temp.nrProcese];
		for (int i = 0; i < temp.nrProcese; i++)
			v[i] = temp.vectorProcese[i];

		temp.nrProcese++;
		delete[] temp.vectorProcese;
		temp.vectorProcese = new int[temp.nrProcese];

		for (int i = 0; i < temp.nrProcese - 1; i++) {
			temp.vectorProcese[i] = v[i];
		}

		temp.vectorProcese[temp.nrProcese - 1] = x;
		
		return temp;
	}

	Avocat& operator-=(int x) {
		this->onorariu -= x;

		return *this;
	}

	bool operator>(Avocat a) {
		if (this->nrProcese > a.nrProcese) return true;
		else return false;
	}

	bool operator<(Avocat a) {
		if (this->nrProcese < a.nrProcese) return true;
		else return false;
	}

	bool operator==(Avocat a) {
		if (this->nrProcese == a.nrProcese) return true;
		else return false;
	}

	int operator [](int i){
		return this->vectorProcese[i];
	}

	friend ostream& operator<<(ostream &out, Avocat a) {
		out << "Cod: " << a.COD << endl;
		out << "Nume: " << a.nume << endl;
		out << "Onorariu: " << a.onorariu << endl;
		out << "Vectorul de " << a.nrProcese << " procese: " << endl;
		for (int i = 0; i < a.nrProcese; i++) {
			out << a.vectorProcese[i] << " ";
		}

		out << endl << endl;
		return out;
	}

	friend ofstream& operator<<(ofstream &out, Avocat a) {
		out << "Cod: " << a.COD << endl;
		out << "Nume: " << a.nume << endl;
		out << "Onorariu: " << a.onorariu << endl;
		out << "Vectorul de " << a.nrProcese << " procese: " << endl;
		for (int i = 0; i < a.nrProcese; i++) {
			out << a.vectorProcese[i] << " ";
		}

		out << endl << endl;
		return out;
	}

	friend ifstream& operator>>(ifstream &in, Avocat &a) {
		char aux[50];

		in >> aux;

		delete[] a.nume;
		a.nume = new char[strlen(a.nume) + 1];
		strcpy(a.nume, aux);
		
		in >> a.onorariu;
		in >> a.nrProcese;
		delete[] a.vectorProcese;
		a.vectorProcese = new int[a.nrProcese];

		for (int i = 0; i < a.nrProcese; i++) {
			in >> a.vectorProcese[i];
		}
		return in;
	}
};

class AvocatOficiu : virtual public Avocat {
private:
	char* client;
	int durataProces;

public:
	AvocatOficiu(const int COD, char* nume, int onorariu, int nrProcese, int *vectorProcese, char *client, int durataProces) : Avocat(COD, nume, onorariu, nrProcese, vectorProcese){
		this->client = new char[strlen(client) + 1];
		strcpy(this->client, client);
		this->durataProces = durataProces;
	}

	friend ostream& operator<<(ostream &out, AvocatOficiu ao) {
		out << (Avocat) ao;
		out << "Nume client: " << ao.client << endl;
		out << "Durata proces: " << ao.durataProces << endl;
		out << endl << endl;
		return out;
	}

};

void main() {
	int vectProc1[3] = { 500, 900, 1200 };
	int vectProc2[4] = { 1100, 700, 2300, 3000 };
	int vectProc3[3] = { 5000, 6500, 4200 };

	//1p
	Avocat a1;
	Avocat a2(123, "Georgescu Vasile", 120.0, 3, vectProc1);
	cout << a2;
	//1p
	cout << a2.getNume() << endl;
	a2.setNume("Paraschivescu Gigel");
	cout << a1.getIdentificator() << endl;
	int * v = a2.getVectorProcese();
	for (int i = 0; i < 3; i++)
		cout << v[i] << " ";
	a2.setVectorProcese(vectProc2, 4);

	//1p
	Avocat a3 = a2;
	Avocat a4; 
	a4 = a2;
	cout << endl << endl << a1 << a2 << a3 << a4;

	//1p
	a3 = a3 + 2000;
	a2 -= 30;
	cout << a3;
	cout << a2;
	cout << "Valoarea media a unui proces este: " << a3.valMedieProces() << endl;

	//1p
	if (a3 > a2) cout << "Avocatul a3 are mai multe procese ca a2" << endl;
	else if (a3 < a2) cout << "Avocatul a3 are mai putine procese ca a2" << endl;
	else cout << "Avocatul a3 are acelasi numar de procese ca a2" << endl;

	//1p
	ofstream fisOut("iesire.txt");
	fisOut << a4;
	fisOut.close();
	ifstream fisIn("intrare.txt", ios::in);
	fisIn >> a4;
	cout << endl << a4;
	fisIn.close();
	
	//1p
	cout << a2[3] << endl;

	//1p
	AvocatOficiu ao1(123, "George Vasile", 120.0, 3, vectProc3, "Popescu Ion", 4);
	cout << ao1;

	//1p
	list <Avocat> barou;
	barou.push_back(a1);
	barou.push_back(a2);
	barou.push_back(a3);
	barou.push_back(a4);
	barou.push_back(ao1);
	list<Avocat>::iterator i;
	cout << "---------------------------------------------------------------\n";
	for (i = barou.begin(); i != barou.end(); ++i) {
		cout << (*i);
	}

	barou.sort();

	cout << "---------------------------------------------------------------\n";

	for (i = barou.begin(); i != barou.end(); ++i) {
		cout << (*i);
	}
	_getch();
}