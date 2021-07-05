#include <iostream>
#include <fstream>
#include <conio.h>
#include <vector>
#include <string>
using namespace std;

class Produs {
private:
	char* denumire;
	double pret;
	int cantitate;

public:
	Produs() {
		denumire = new char[strlen("Produs") + 1];
		strcpy(denumire, "Produs");
		pret = 0.0;
		cantitate = 0;
	}

	Produs(char* denumire, double pret, int cantitate) {
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->pret = pret;
		this->cantitate = cantitate;
	}


	Produs(char* denumire, double pret) {
		this->denumire = new char[strlen(denumire) + 1];
		strcpy(this->denumire, denumire);
		this->pret = pret;
		this->cantitate = 0;
	}

	Produs(const Produs &p) {
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->pret = p.pret;
		this->cantitate = p.cantitate;
	}

	~Produs() {
		delete[] denumire;
	}

	double getPret() {
		return pret;
	}

	double getCantitate() {
		return cantitate;
	}

	void operator=(Produs p) {
		delete[] denumire;
		this->denumire = new char[strlen(p.denumire) + 1];
		strcpy(this->denumire, p.denumire);
		this->pret = pret;
		this->cantitate = cantitate;
	}

	Produs operator++() {  //prefixat ++p
		this->cantitate ++;

		return (*this);
	}

	Produs operator++(int) { //postfixat p++
		Produs temp = (*this);
		++(*this);
		return temp;
	}

	Produs operator+=(int x) {
		this->cantitate += x;
		return (*this);
	}

	virtual double getValoare() {
		return pret * cantitate;
	}

	char* getDenumire() {
		return denumire;
	}

	bool operator<(Produs p) {
		if (this->cantitate * this->pret < p.cantitate * p.pret) return true;
		else return false;
	}

	friend ostream& operator<<(ostream& out, Produs p) {
		out << p.denumire << " " << p.cantitate << " x " << p.pret << " RON\n";
		return out;
	}


	friend ofstream& operator<<(ofstream& out, Produs p) {
		out << p.denumire << " " << p.cantitate << " x " << p.pret << " RON\n";
		return out;
	}

};

class ProdusDiscount : public Produs {

private:
	double valoareDiscount;

public:
	ProdusDiscount(char *denumire, double pret, double valoareDiscount) : Produs(denumire, pret) {
		this->valoareDiscount = valoareDiscount;
	}

	double getValoare() {
		return this->getPret() * this->getCantitate() - this->valoareDiscount;
	}

	friend ostream& operator<<(ostream& out, ProdusDiscount pd) {
		out << pd.getDenumire() << " " << pd.getCantitate() << " x " << pd.getPret() << " - " << pd.valoareDiscount << " RON\n";
		return out;
	}

	friend ofstream& operator<<(ofstream& out, ProdusDiscount pd) {
		out << pd.getDenumire() << " " << pd.getCantitate() << " x " << pd.getPret() << " - " << pd.valoareDiscount << " RON\n";
		return out;
	}

};

class Cos {

private:
	Produs **produse;
	int n;

public:
	Cos() {
		n = 0;
		produse = NULL;
	}

	Cos operator+=(Produs *p) {
		Produs **prod;
		prod = new Produs*[n + 1];

		for (int i = 0; i < n; i++) {
			prod[i] = produse[i];
		}

		prod[n] = p;
		if (this->produse != NULL) delete[]this->produse;
		this->produse = prod; //aloca automat
		this->n++;

		return (*this);
	}

	double Total() {
		double sum = 0;
		for (int i = 0; i < n; i++) {
			sum += (*produse[i]).getValoare();
		}
		return sum;
	}

	friend ofstream& operator<<(ofstream &fout, Cos c){
		fout << "In cos exista " << c.n << " elemente: \n";
		for (int i = 0; i < c.n; i++) {
			fout << (*c.produse[i]);
		}

		return fout;
	}

	void scrieInFisier(ofstream &fout) {
		fout << (*this);
	}

	vector<string> obtineDenumiri() {
		vector<string> den;
		for (int i = 0; i < this->n; i++) 
			den.push_back((string)((*this->produse[i]).getDenumire()));
		
		return den;
	}
};

void main() {
	Produs mere("Mere", 4.1);
	Produs pere("Pere", 6.5);
	mere++; 
	pere++;
	mere += 5;
	cout << mere;
	cout << pere++;
	cout << pere;

	if (mere < pere) cout << "Valoarea merelor este mai mica." << endl;

	ProdusDiscount struguri("Struguri", 8, 15);
	struguri += 10;
	cout << struguri;

	Cos cos;
	cos += &struguri;
	cos += &pere;
	cos += &mere;
	cout << "TOTAL: " << cos.Total() << endl; //102.6

	ofstream fisier("date_cos.txt");
	cos.scrieInFisier(fisier);

	vector<string> denumiriProduse = cos.obtineDenumiri();
	cout << "Produse: ";
	vector<string> ::iterator i;
	for (i = denumiriProduse.begin(); i != denumiriProduse.end(); ++i){
		cout << (*i) << ' ';
	}

	_getch();
}