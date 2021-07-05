#include<iostream>

using namespace std;

class Cuvant {
private:
	const int cheieUnica = 500;

	string valoare = "";
	unsigned nrSinonime = 0;
	string* sinonime=NULL;

	static int NR_CUVINTE;
public:
	Cuvant(): cheieUnica(NR_CUVINTE++){
		cout << endl << "apel constructor implicit";
		this->valoare = "";
		this->nrSinonime = 0;
		this->sinonime = NULL;
		
	}
	Cuvant(string valoare, unsigned nrSinonime, string* sinonime) : cheieUnica(NR_CUVINTE++) {
		this->valoare = valoare;
		this->nrSinonime = nrSinonime;
		this->sinonime = new string[nrSinonime];
		for (unsigned i = 0; i < nrSinonime; i++) {
			this->sinonime[i] = sinonime[i];
		}

	}
	Cuvant(const Cuvant& copie):cheieUnica(copie.NR_CUVINTE) {
		this->valoare = copie.valoare;
		this->nrSinonime = copie.nrSinonime;
		if (this->nrSinonime) {
			this->sinonime = new string[copie.nrSinonime];

			for (unsigned i = 0; i < copie.nrSinonime; i++) {
				this->sinonime[i] = copie.sinonime[i];
			}
		}
		else {
			this->sinonime = NULL;
		}
	}
	~Cuvant() {
		if (this->sinonime != NULL)
			delete[]this->sinonime;
	}
	string getValoare() {
		return this->valoare;
	}
	unsigned getNrSinonime() {
		return this->nrSinonime;
	}
	string* getSinonime() {
		if (sinonime != NULL) {
			string* c = new string[nrSinonime];
			for (unsigned i = 0; i < nrSinonime; i++) {
				c[i] = sinonime[i];
			}
			return c;
		}
		return NULL;
	}

	//operatori 
	Cuvant operator=(Cuvant& cuv) {
		this->valoare = cuv.valoare;
		this->nrSinonime = cuv.nrSinonime;
		if (this->sinonime != NULL)
			delete[] this->sinonime;
		if (this->nrSinonime) {
			this->sinonime = new string[cuv.nrSinonime];

			for (unsigned i = 0; i < cuv.nrSinonime; i++) {
				this->sinonime[i] = cuv.sinonime[i];
			}
		}
		else {
			this->sinonime = NULL;
		}
		return *this;
	}
	/*void adaugaSinonim(string sinonim) {
		if (sinonim.length() > 0 && sinonim.length() <= 100) {
			string* sinonim = new string[this->nrSinonime + 1];
			for (unsigned i = 0; i < nrSinonime; i++) {
				sinonim[i] = this->sinonime[i];
			}
			this->nrSinonime += 1;
			delete[] this->sinonime;
		}
		else {
			throw" sinonime invalide";
		}
	}*/
	bool areNumarPardeSinonime() {
		if (nrSinonime % 2 == 0) {
			return true;
		}
		else {
			return false;
		}
	}
	bool operator!() {
		if (this->nrSinonime > 3)
			return true;
		else
			return false;
	}
	void operator-=(unsigned val) {
		this->nrSinonime -= val;
	}

	friend ostream& operator<<(ostream& out, Cuvant& c);
	friend istream& operator>>(istream& in, Cuvant& c);
};

int Cuvant::NR_CUVINTE = 0;

istream& operator>>(istream& in, Cuvant& c) {
	cout << "valoare";
	in >> c.valoare;

	cout << "nr sinonime";
	in >> c.nrSinonime;

	for (int i = 0; i < c.nrSinonime; i++) {
		cout << "sinonime" << (i + 1) << " ";
		in >> c.sinonime[i];
	}
	return in;
}
ostream& operator<<(ostream& out, Cuvant& c) {
	out << endl << "----------------------------------";
	out << endl << "valoarea" << c.valoare;
	out << endl << "nr sinonime" << c.nrSinonime;
	if (c.sinonime != NULL) {
		for (unsigned i = 0; i < c.nrSinonime; i++) {
			out << endl << "sinonime:" << i + 1 << "";
			out<< c.sinonime[i]<<endl;
		}
	}

	return out;
}
int main() {

	string text[2] = { "ceva","altceva" };
	Cuvant c1("tom cruise",2,text);
	cout << c1;
	Cuvant c2 = c1;
	cout << c2;
	
	Cuvant c3;
	c3 = c1;
	cin >> c3;
	string s[3] = { "pampam","hehe","lala" };

	Cuvant c4("aikido", 3, s);

	 /*if (!c4)
		 cout << endl << "nr sinonime mai mare de 3";
	 else
		 cout << endl << "nr de sinonime mai mic de 3";
	 cout << c4;*/

	// c4.areNumarPardeSinonime(c4);
	
	 c4 -= 1;
	 cout << c4;

}