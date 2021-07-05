#include <iostream>
#include <fstream>
#include <conio.h>
#include <list>

using namespace std;

class Operatie {
private:
	char* denumire; 
	long double pret;

public:
	Operatie() {
		denumire = new char[strlen("Operatia x") + 1];
		strcpy(denumire, "Operatia x");
		pret = 0.0;
	}

	Operatie(char* denumire, long double pret) {
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->pret = pret;
	}

	Operatie(const Operatie &o) {
		this->denumire = new char[strlen(o.denumire) + 1];
		strcpy(this->denumire, o.denumire);
		this->pret = o.pret;
	}

	~Operatie() {
		delete[] denumire;
	}

	long double getPret() {
		return pret;
	}

	char* getDenumire() {
		return denumire;
	}

	void operator=(Operatie o) {
		delete[] this->denumire;
		this->denumire = new char[strlen(o.denumire) + 1];
		strcpy(this->denumire, o.denumire);
		this->pret = o.pret;
	}

	friend istream& operator >> (istream& in, Operatie &o) {
		char aux[50];
		cout << "Nume operatie: ";
		in >> aux;

		delete[] o.denumire;
		o.denumire = new char[strlen(aux) + 1];
		strcpy(o.denumire, aux);

		cout << "Pret operatie: ";
		in >> o.pret;

		return in;
	}

	friend ostream& operator << (ostream& out, Operatie o) {
		out << "Nume operatie: " << o.denumire << endl;
		out << "Pret operatie: " << o.pret << endl;
		
		return out;
	}

	friend ifstream& operator >> (ifstream& in, Operatie &o) {
		char aux[50];
		in >> aux;

		delete[] o.denumire;
		o.denumire = new char[strlen(aux) + 1];
		strcpy(o.denumire, aux);

		in >> o.pret;

		return in;
	}


	friend ofstream& operator << (ofstream& out, Operatie o) {
		out << o.denumire << endl;
		out << o.pret << endl;

		return out;
	}
};

class Revizie {
private:
	char numarAuto[15];
	int numarRevizie;
	long numarKilometri;
	char data[11];
	int nrOperatii;
	Operatie *operatii;

public:
	Revizie() {
		strcpy(numarAuto, "TR01IDK");
		numarRevizie = 0;
		numarKilometri = 0;
		strcpy(data, "01.01.2016");
		nrOperatii = 0;
		operatii = NULL;
	}

	Revizie(char numarAuto[15], int numarRevizie, long numarKilometri, Operatie operatie) {
		strcpy(this->numarAuto, numarAuto);
		this->numarRevizie = numarRevizie;
		this->numarKilometri = numarKilometri;
		this->nrOperatii = 1;
		operatii = new Operatie[this->nrOperatii];
		operatii[0] = operatie;
	}

	Revizie(char numarAuto[15], Operatie *operatii, int nrOperatii) {
		strcpy(this->numarAuto, numarAuto);
		this->nrOperatii = nrOperatii;
		this->operatii = new Operatie[this->nrOperatii];
		for (int i = 0; i < this->nrOperatii; i++) {
			this->operatii[i] = operatii[i];
		}
	}

	Revizie(char numarAuto[15], int numarRevizie, long numarKilometri) {
		strcpy(this->numarAuto, numarAuto);
		this->numarRevizie = numarRevizie;
		this->numarKilometri = numarKilometri;
		this->nrOperatii = 0;
		this->operatii = NULL;
	}

	long double getCostRevizie() {
		long double cost = 0;
		for (int i = 0; i < nrOperatii; i++) {
			cost += operatii[i].getPret();
		}

		return cost;
	}

	void setNumarAuto(char numarAuto[15]) {
		strcpy(this->numarAuto, numarAuto);
	}

	Revizie operator+=(Operatie o) {
		Operatie *op = new Operatie[this->nrOperatii];
		for (int i = 0; i < this->nrOperatii; i++) {
			op[i] = this->operatii[i];
		}

		this->nrOperatii++;
		delete[] this->operatii;
		this->operatii = new Operatie[this->nrOperatii];
		
		for (int i = 0; i < this->nrOperatii - 1; i++)
			this->operatii[i] = op[i];

		this->operatii[this->nrOperatii - 1] = o;

		return (*this);
	}

	Revizie operator-=(char *denumire) {
		int k = 0;
		Operatie *op = new Operatie[this->nrOperatii];
		Operatie *op2 = new Operatie[this->nrOperatii];

		for (int i = 0; i < this->nrOperatii; i++) {
			op[i] = this->operatii[i];
		}

		for (int i = 0; i < this->nrOperatii; i++) {
			if (strcmp(op[i].getDenumire(), denumire) == 0)
				k = i;
			else op2[i] = op[i];
		}

		if (k == this->nrOperatii - 1) {
			this->nrOperatii--;
			delete[] this->operatii;
			this->operatii = new Operatie[this->nrOperatii];

			for (int i = 0; i < this->nrOperatii; i++)
				this->operatii[i] = op2[i];
		} else{
			for (int i = k; i < this->nrOperatii - 1; i++)
				op2[i] = op2[i + 1];

			this->nrOperatii--;
			delete[] this->operatii;
			this->operatii = new Operatie[this->nrOperatii];
		
			for (int i = 0; i < this->nrOperatii; i++)
				this->operatii[i] = op2[i];
		}
		return (*this);
	}

	Revizie operator-=(Operatie o) {
		int k;
		Operatie *op = new Operatie[this->nrOperatii];
		Operatie *op2 = new Operatie[this->nrOperatii];

		for (int i = 0; i < this->nrOperatii; i++) {
			op[i] = this->operatii[i];
		}

		for (int i = 0; i < this->nrOperatii; i++) {
			if (strcmp(op[i].getDenumire(), o.getDenumire()) == 0)
				k = i;
			else op2[i] = op[i];
		}

		if (k == this->nrOperatii - 1) {
			this->nrOperatii--;
			delete[] this->operatii;
			this->operatii = new Operatie[this->nrOperatii];

			for (int i = 0; i < this->nrOperatii; i++)
				this->operatii[i] = op2[i];
		}
		else{
			for (int i = k; i < this->nrOperatii - 1; i++)
				op2[i] = op2[i + 1];

			this->nrOperatii--;
			delete[] this->operatii;
			this->operatii = new Operatie[this->nrOperatii];

			for (int i = 0; i < this->nrOperatii; i++)
				this->operatii[i] = op2[i];
		}
		return (*this);
	}

	operator double() {
		return this->getCostRevizie();
	}

	bool operator<(Revizie r) {
		if (this->getCostRevizie() < r.getCostRevizie()) return true;
		else return false;
	}

	bool operator>(Revizie r) {
		if (this->getCostRevizie() > r.getCostRevizie()) return true;
		else return false;
	}

	bool operator==(Revizie r) {
		if (this->getCostRevizie() == r.getCostRevizie()) return true;
		else return false;
	}

	Operatie operator[](int i) {
		if (i < this->nrOperatii)
			return this->operatii[i];
		else {
			cout << "Nu exista atatea operatii" << endl;
			Operatie o;
			return o;
		}
	}
	friend istream& operator >> (istream& in, Revizie &r) {
		cout << "Numar de inmatriculare: "; 
		in >> r.numarAuto;

		cout << "Numar revizie: ";
		in >> r.numarRevizie;

		cout << "Numar km: ";
		in >> r.numarKilometri;

		cout << "Data (dd.mm.yyyy): ";
		in >> r.data;

		cout << "Numar operatii: ";
		in >> r.nrOperatii;

		r.operatii = new Operatie[r.nrOperatii];
		for (int i = 0; i < r.nrOperatii; i++) {
			cout << "Operatia " << i << ": \n";
			in >> r.operatii[i];
		}

		return in;
	}

	friend ostream& operator << (ostream& out, Revizie r) {
		out << "Numar de inmatriculare: " << r.numarAuto << endl;
		out << "Numar revizie: " << r.numarRevizie << endl;
		out << "Numar km: " << r.numarKilometri << endl;
		out << "Data reviziei: " << r.data << endl;
		out << "Numar operatii: " << r.nrOperatii << endl;
		out << "Operatii: \n";
		
		for (int i = 0; i < r.nrOperatii; i++) {
			out << r.operatii[i];
		}

		return out;
	}


	friend ofstream& operator << (ofstream& out, Revizie r) {
		out << r.numarAuto << endl;
		out << r.numarRevizie << endl;
		out << r.numarKilometri << endl;
		out << r.data << endl;
		out << r.nrOperatii << endl;
		for (int i = 0; i < r.nrOperatii; i++) {
			out << r.operatii[i] << " ";
		}

		return out;
	}

	friend ifstream& operator >> (ifstream& in, Revizie &r) {
		in >> r.numarAuto;
		in >> r.numarRevizie;
		in >> r.numarKilometri;
		in >> r.data;
		in >> r.nrOperatii;
		r.operatii = new Operatie[r.nrOperatii];
		
		for (int i = 0; i < r.nrOperatii; i++) {
			in >> r.operatii[i];
		}

		return in;
	}
	
};

class RevizieSpeciala : public Revizie {
private:
	float reducere;

public:
	RevizieSpeciala(char numarAuto[15], int numarRevizie, long numarKilometri, Operatie operatie, float reducere) :Revizie(numarAuto, numarRevizie, numarKilometri, operatie) {
		this->reducere = reducere;
	}

	friend ostream& operator<<(ostream &out, RevizieSpeciala rs){
		out << (Revizie)rs;
		out << "Reducere acordata: " << rs.reducere << endl;

		return out;
	}

};

void main() {
	//5p
	Revizie r1, r4;
	Operatie o1("SchimbareUlei", 150);
	Operatie o2("InlocuireFiltruAer", 99);
	Operatie o3("InlocuireFiltruPolen", 55);
	Operatie o4 = o1;
	Revizie r2("B99ABC", 1, 10000);
	Revizie r3("B99ABC", 2, 20000, o4);

	cout << r3.getCostRevizie() << endl;
	cin >> r4;
	Operatie operatii[] = { o1, o2, o3, o4 };
	Revizie r5("B111XYZ", operatii, 4);
	cout << r1 << r2 << r3 << r4 << r5;
	cout << r1;

	//1p
	r1.setNumarAuto("TX11111A");
	r1 += o1;
	r1 += o2;
	r1 += o3;
	cout << r1;
	r1 -= "Schimbare ulei";
	cout << r1;
	r1 -= o2;
	cout << r1;

	//1p
	cout << "Costul reviziei este: " << (double)r1 << endl;
	if (r1 < r2) cout << "Revizia r2 este mai scumpa decat r1" << endl; 
	else cout << "Revizia r2 este mai ieftina decat r1" << endl;
	cout << r1[4];
	cout << r1;

	//1p
	ofstream out("revizii.bin");
	out << r1;
	out.close();

	ifstream in("revizii.bin");
	Revizie r6;
	in >> r6;
	cout << r6 << endl;

	//1p
	RevizieSpeciala rs("B123KLM", 1, 25000, o1, 0.25);
	rs += o2;
	cout << rs;
	cout << (double)rs;

	//1p
	list <Revizie> revizii;
	revizii.push_back(r1);
	revizii.push_back(r2);
	revizii.push_back(r3);
	revizii.push_back(r4);
	revizii.push_back(r5);
	revizii.push_back(rs);

	double incasari = 0;

	list<Revizie> :: iterator i;
	for (i = revizii.begin(); i != revizii.end(); ++i) {
		incasari += (*i).getCostRevizie();
	}

	cout << "Incasarile totale ale service-ului auto sunt: " << incasari;

	_getch();
}