#include <iostream>
#include<string>
#include <fstream>
using namespace std;

class Ferma {
private:
	const int id;
	string denumire;
	int cifraAfaceri;
	static int nrFerma;
	int* incasari;

public:
	Ferma() :id(nrFerma++) {
		cout << "apel constructor implicit" << endl;
		this->denumire = "ferma1";
		this->cifraAfaceri = 100.2;
		this->incasari = nullptr;

	}
	Ferma(string denumire, int* incasari, int nr) :id(nrFerma++) {
		this->denumire = denumire;
		this->cifraAfaceri = nr;
		this->incasari = new int[nr];
		for (int i = 0; i < cifraAfaceri; i++) {
			this->incasari[i] = incasari[i];
		}

	}
	string getDenumire() {
		return this->denumire;

	}
	double getCifra() {
		return this->cifraAfaceri;
	}
	int* getIncasari() {
		return this->incasari;
	}
	void setDenumire(string denumireNoua) {
		this->denumire = denumireNoua;
	}
	void setCifra(int cifraNoua) {
		this->cifraAfaceri = cifraNoua;
	}
	void setIncasari(int cifra, int* incasariNoi) {
		if (this->incasari != NULL) {
			delete[] this->incasari;
		}
		this->cifraAfaceri = cifra;
		this->incasari = new int[this->cifraAfaceri];
		for (int i = 0; i < this->cifraAfaceri; i++) {
			this->incasari[i] = incasariNoi[i];
		}
	}
	Ferma(const Ferma& sursa) :id(nrFerma++) {
		this->denumire = sursa.denumire;
		this->cifraAfaceri = sursa.cifraAfaceri;
		if (sursa.incasari != NULL) {
			this->incasari = new int[sursa.cifraAfaceri];
			for (int i = 0; i < sursa.cifraAfaceri; i++) {
				this->incasari[i] = sursa.incasari[i];
			}
		}
		else {
			this->incasari = NULL;
		}

	}
	~Ferma() {
		if (this->incasari != NULL)
			delete[] this->incasari;
	}
	Ferma& operator=(const Ferma& sursa) {

		if (this->incasari != NULL)
			delete[] this->incasari;

		this->denumire = sursa.denumire;
		this->cifraAfaceri = sursa.cifraAfaceri;
		if (this->cifraAfaceri) {
			this->incasari = new int[sursa.cifraAfaceri];
			for (int i = 0; i < sursa.cifraAfaceri; i++) {
				this->incasari[i] = sursa.incasari[i];
			}
		}
		else {
			this->incasari = NULL;

		}
		return *this;
	}
	virtual float calculVenit() {
		
	}

	friend ostream& operator<<(ostream& out, Ferma f) {
		out << "denumirea fermei este " << f.denumire << endl;
		out << "cu o cifra de afaceri de " << f.cifraAfaceri << endl;
		out << " aceasta are id-ul " << f.id << endl;
		out << " nr de ferma aferent id-ului " << f.nrFerma << endl;
		if (f.cifraAfaceri != NULL) {
			for (int i = 0; i < f.cifraAfaceri; i++) {
				out << " incasarile datorate ciferi sunt " << f.incasari[i] << endl;
			}
		}
		return out;
	}
};
int Ferma::nrFerma = 0;


class FermaVegetala : public Ferma {
	int suprafataHa = 0;
	float venitLaHectar = 0;


public:
	FermaVegetala() {
		suprafataHa = 0;
		venitLaHectar = 0;
		//ferma = NULL;
	}
	FermaVegetala(string denumire, int* incasari, int nr, int suprafata, float venitLaHectar) :Ferma(denumire, incasari, nr) {

		this->suprafataHa = suprafata;
		this->venitLaHectar = venitLaHectar;
	}
	//pentru a adauga n ha 
	FermaVegetala& operator+=(int value) {

		this->suprafataHa += value;
		return *this;
	}
	float calculVenit() {

		cout << " calculul pe venit este : " << endl;
		return suprafataHa * venitLaHectar;
	}
	friend ostream& operator<<(ostream& out, FermaVegetala f) {
		out << "suprafata " << f.suprafataHa << " cu un venit la hectar de " << f.venitLaHectar << endl;
		out << (Ferma)f << endl;
		return out;
	}
};
class FermaZootehnica : public Ferma {
	int nrAnimale = 0;
	float venitPeAnimal = 0;
	//Ferma* ferme;

public:
	FermaZootehnica& operator+=(int value) {


		this->nrAnimale += value;
		return *this;
	}
	FermaZootehnica(string denumire, int* incasari, int nrA, int nr, float venitAnimal) :Ferma(denumire, incasari, nrA) {
		this->nrAnimale = nr;
		this->venitPeAnimal = venitAnimal;
	}
	float calculVenit() {
		cout << " calculul pe venit este : " << endl;
		return nrAnimale * venitPeAnimal;
	}
	friend ostream& operator<<(ostream& out, FermaZootehnica f) {

		out << "nr de naimale din ferma " << f.nrAnimale << "aduc un venit per animal de " << f.venitPeAnimal << endl;
		out << (Ferma)f << endl;
		return out;
	}
};

void main() {


	Ferma f1;
	f1.setCifra(2000.04);
	f1.setDenumire("ferma verde");

	int v[4] = { 100, 40, 20, 230 };
	Ferma f2("gigica", v, 4);
	Ferma f3(f2);

	f2 = f3;
	cout << f2;

	FermaVegetala v1("ferma noua", v, 4, 2000, 3568);
	FermaZootehnica z1("ferma zoo", v, 4, 100, 50);
	cout << v1;
	cout << z1;

	//cout << v1.calculVenit() << endl;
	//out<< z1.calculVenit() << endl;

	v1 += 100;
	cout << "operator +=" << v1 << endl;
	z1 += 200;;
	cout << "operator +=" << z1 << endl;

}