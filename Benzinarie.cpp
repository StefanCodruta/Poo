#include <iostream>
#include <string>
#include <fstream>

using namespace std; 


class Benzinarie {
private:
	char* TipComustibil;
	float pret;
	int pompe;
	float CapacitateRezervor;
	const int id;
public:
	static int contor;

	char* getTipCombustibil() {
	
		return this->TipComustibil;
	}
	float getPret() {
		return this->pret;

	}
	int getPompe() {
		return this->pompe;
	}
	float getCapacitateRezrevor() {
		return this->CapacitateRezervor;
	}
	void setTipCombustibil(const char* nou) {
		if (this->TipComustibil != NULL) {
			delete[] this->TipComustibil;
		}
		this->TipComustibil = new char[strlen(nou) + 1];
		strcpy(this->TipComustibil, nou);

	 }
	void setPret(float pretNou) {
		if (this->pret > 0 && this->pret < 100) {
			this->pret = pretNou;
		}

	}
	void setPompe(int pompe) {
		this->pompe = pompe;
	}
	void setCapacitate(float CapacitateNou) {
		if (this->CapacitateRezervor < 100 && this->CapacitateRezervor < 1000) {
			this->CapacitateRezervor = CapacitateNou;
		}
	}


	
	
	
	Benzinarie() :id(contor++)
	{
		cout << endl << "apel constructor implicit";
		this->TipComustibil = new char[strlen("nimic") + 1];
		strcpy(this->TipComustibil, "nimic");
		this->pret = 0;
		this->pret = 0;
		this->CapacitateRezervor = 50;

	}
	Benzinarie(const char* tipcomb, float pret, int pompe, float capacitateRez) : id(contor++) {
		this->TipComustibil = new char[strlen(tipcomb) + 1];
		strcpy(this->TipComustibil, tipcomb);
		this->pret = pret;
		this->pompe = pompe;
		this->CapacitateRezervor = capacitateRez;

	}
	friend ostream& operator<<(ostream& out, Benzinarie& b) {
		out << "tipul de combustibil este " << b.getTipCombustibil() << " la pretul de  " << b.getPret() << " si se gaseste la pompa " << b.getPompe();
		out << endl << " ,iar capacitate rezervorului este " << b.getCapacitateRezrevor();
		return out;

	}
	Benzinarie& operator += (int nr) {
		if (this->getCapacitateRezrevor() > 0 ) {
			this->CapacitateRezervor = this->CapacitateRezervor+nr;

		}
		else {
			this->CapacitateRezervor = CapacitateRezervor;
		}
		return *this;
	}
	Benzinarie& operator -= (int nr) {
		this->CapacitateRezervor -= nr;
		return *this;
	}
	void CelMaiVandut(const char* tipCombustibil) {

	}
};
ofstream& operator<<(ofstream& out, Benzinarie& b) {
	out << "tipul de combustibil este " << b.getTipCombustibil() << " la pretul de  " << b.getPret() << " si se gaseste la pompa " << b.getPompe();
	out << endl << " ,iar capacitate rezervorului este " << b.getCapacitateRezrevor();
	return out;
}
class InvalidException : public exception {
	string mesaj = "";
	int codEroare = 0;
public:
	InvalidException() {

	}

	InvalidException(string mesaj, int cod) {
		this->mesaj = mesaj;
		this->codEroare = cod;
	}

	string getMesaj() {
		return this->mesaj;
	}

	int getCod() {
		return this->codEroare;
	}
};

int Benzinarie::contor = 0;
int main() {
	Benzinarie b1;
	Benzinarie b2("benzina", 4.8, 6, 99);
	cout << b1.getCapacitateRezrevor() << endl;
	cout << b2.getTipCombustibil() << endl;
	cout << b2 << endl;

	b2.setTipCombustibil("motorina");
	cout << b2;
	Benzinarie b3("motorina premium ", 5.0, 5, 19);
	cout << b3;

	b3 -= 20;
	cout << "b3 dupa golire din capacitate " << endl;
	cout << b3 << endl;
	b2 += 10;
	cout << "b2 dupa adaugare capacitate suplimentara "<<endl;
	cout << endl << b2;


	ofstream f("text.txt");
	f << b2;
	f << b3;
	try {
		Benzinarie e("motor",
			4, 5,50);
		
		cout << endl << "Sfarsit try";
		throw InvalidException();
	}
	catch (InvalidException ex) {
		cout << endl << "Avem o problema";
		cout << endl << "Detalii: " << ex.getMesaj();

	}
	
}


