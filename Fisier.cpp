#include<iostream>

using namespace std;

class Fisier {
	const int codFisier=10;
	string numeFisier = "";

	int nrAccessori=0;
	string* editori=NULL;


	static int nr_cuvinte; //camp static, comun pentru toate obiectele il folosim cu scopul de a diferentia codfisierului prin nr de cuvinte asociate
public: 
	Fisier() :codFisier(nr_cuvinte++){
		cout << endl << "apel constructor implicit";
			this->numeFisier = "";
			this->nrAccessori = 0;
			this->editori = NULL;

	}
	Fisier(string numeFisier, int nrAccessori, string* editori) :codFisier(nr_cuvinte++) {
		this->numeFisier = numeFisier;
		this->nrAccessori = nrAccessori;
		this->editori = new string[nrAccessori];
		for (int i = 0; i < nrAccessori; i++) {
			this->editori[i] = editori[i];
		}
	}

	~Fisier() {
		if (this->editori != NULL)
			delete[] this->editori;
	}

	string getNume() {
		return this->numeFisier;
	}
	int getNrAccesori() {
		return this->nrAccessori;
	}
	string* getEditori() {
		if (this->editori != NULL) {
			string* f = new string[nrAccessori];
			for (int i = 0; i < nrAccessori; i++) {
				f[i] = editori[i];
			}
			return f;
		}
		return NULL;
	}
	void set_name(string numeNou) {
		if (numeNou.length() >= 0) {
			numeFisier = numeNou;
		}
	}
	void set_editori(string* edit, int nrAccesori) {
		if (this->editori != NULL)
			delete[] this->editori;
		if (edit != NULL)
		{
			editori = new string[nrAccesori];
			nrAccesori = nrAccesori;
			for (int i = 0; i < nrAccesori; i++) {
				editori[i] = edit[i];
			}
		}
		else {
			editori = NULL;
			nrAccesori = 0;
		}

	}
	Fisier(const Fisier& copie) : codFisier(copie.nr_cuvinte) {
		this->numeFisier = copie.numeFisier;
		this->nrAccessori = copie.nrAccessori;
		if (this->nrAccessori) {
			this->editori = new string[copie.nrAccessori];
			for (int i = 0; i < copie.nrAccessori; i++) {
				this->editori[i] = copie.editori[i];
			}
		}
		else {
			this->editori = NULL;
		}
	}
	Fisier operator=(const Fisier& fis)  {
		this->numeFisier = fis.numeFisier;
		this->nrAccessori = fis.nrAccessori;
		if (this->editori != NULL) {
			delete[] this->editori;
		}
		if (this->nrAccessori) {
			this->editori = new string[fis.nrAccessori];
			for (int i = 0; i < fis.nrAccessori; i++) {
				this->editori[i] = fis.editori[i];
			}
		}
		else {
			this->editori = NULL;
		}
		return fis;
	}

	/*int determinareNumarAccesori(string editor) {
		if (nrAccessori > 0) {
			
		}
		else {
			throw"nu exista accesari";
		}
	}*/

	bool operator>(Fisier f) {
		if (numeFisier.length() > f.numeFisier.length()) {
			return true;
		}
		else {
			return false;
		}

	}
	//& imi permite si modificarea indexului 
   string& operator[](int index) {
		return editori[index];
	}

	friend ostream& operator<<(ostream& out, Fisier& f);
};

int Fisier::nr_cuvinte = 0;

ostream& operator<<(ostream& out, Fisier& f) {

	out << endl << "-------------------------";
	out << endl << "nume fisier:" << f.numeFisier;
	out << endl << "nr de accesori:" << f.nrAccessori;
	if (f.editori != NULL) {
		for (int i = 0; i < f.nrAccessori; i++) {
			out << endl << "editori:" << i + 1 << "";
			out << f.editori[i];
		}
	}

	return out;
}
int main() {

	string text[2] = { "ceva","altceva" };
	Fisier f1("fisier", 2, text);
	
	cout << f1;
	Fisier f2 = f1;
	cout << f2;

	Fisier f3("fisierul3", 2, text);
	f2 = f3;

	if (f3 > f1) {
		cout << endl << "numele fisierului este mai mare";
	}
	cout << f3;

	f1[1] = "cineva";
	cout << f1[1];

}