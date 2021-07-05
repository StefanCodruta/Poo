#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class Petitie {
private:
	string DataInreg;
	char* numePersoana;
	int nrCategorii;
	bool areRaspuns;
	string* DescriereCategorii;
	const int id;
	static int NrPetitii;

public:
	void setDataInreg(string DataNoua) {
		this->DataInreg = DataNoua;
	}
	void setNume(const char* Numenou) {
		if (strlen(Numenou) > 6) {

			if (this->numePersoana != NULL) {
				delete[] this->numePersoana;
			}
			this->numePersoana = new char[strlen(Numenou) + 1];
			strcpy(this->numePersoana, Numenou);
		}
	}

	void setDescriere(int nrCateg, string* descriereNoua) {
		if (nrCateg > 0) {
			if (this->DescriereCategorii != NULL) {
				delete[] this->DescriereCategorii;
			}
			this->nrCategorii = nrCateg;
			this->DescriereCategorii = new string[nrCateg];
			for (int i = 0; i < nrCateg; i++) {
				this->DescriereCategorii[i] = descriereNoua[i];
			}
		}
	}

	int getNrCateg() {
		return this->nrCategorii;
	}
	char* getNume() {
		return this->numePersoana;

	}
	bool getRaspuns() {
		return this->areRaspuns;
	}

	void afisare() {
		cout << this->numePersoana << endl;
		cout << this->nrCategorii << endl;
		cout << this->areRaspuns << endl;
		cout << this->id << endl;
		cout << this->DataInreg << endl;
		for (int i = 0; i < this->nrCategorii; i++)
		{
			cout << this->DescriereCategorii[i] << endl;
		}
	}

	// ********CONSTRUCTORI*************
	Petitie() :id(NrPetitii++) {
		this->DataInreg = "20/03/2020";
		this->areRaspuns = true;
		this->nrCategorii = 0;
		this->DescriereCategorii = NULL;
		this->numePersoana = new char[strlen("gigel") + 1];
		strcpy(this->numePersoana, "gigel");
		
	}

	Petitie(string data, const char* nume, int nr, string* descriere, bool esteCetatean) : id(NrPetitii++) {
		this->DataInreg = data;
		this -> areRaspuns = esteCetatean;
		
		if (nr > 0) {
			this->nrCategorii = nr;
			this->DescriereCategorii = new string[nr];
			for (int i = 0; i < nr; i++) {
				if (DescriereCategorii[i].size() >= 0) {
					this->DescriereCategorii[i] = descriere[i];
				}
				else {
					this->DescriereCategorii = "na";
				}
			}
		}
		else {
			this->nrCategorii = 0;
			this->DescriereCategorii = NULL;
		}
		
			this->numePersoana = new char[strlen(nume) + 1];
			strcpy(this->numePersoana, nume);
	
	}

	~Petitie() {
		if (this->DescriereCategorii) {
			delete[] this->DescriereCategorii;
		}
		if (this->numePersoana) {
			delete[] this->numePersoana;
		}
	}
	//operator ! pt a indica daca o petitie nu are raspuns si a depasit termenul legal de zile
	bool operator!() {
	
		return !this->areRaspuns;
	}
	friend ofstream& operator<<(ofstream& out, Petitie& p) {
		out << p.DataInreg << endl << p.numePersoana << endl << p.nrCategorii << endl;
		for (int i = 0; i < p.nrCategorii; i++) {
			out << p.DescriereCategorii[i];
		}
		return out;
	}
	friend ifstream& operator>>(ifstream& in, Petitie& p) {
		if (p.DescriereCategorii != NULL)
			delete[] p.DescriereCategorii;
		if (p.numePersoana != NULL) {
			delete[] p.numePersoana;

		}
		in >> p.nrCategorii;
		in >> p.DataInreg;

		string aux;
		getline(in, aux);
		strcpy(p.numePersoana, aux.c_str());
		for (int i = 0; i < p.nrCategorii; i++) {
			in >> p.DescriereCategorii[i];
		}
		return in;
	}

	//virtual void Rezolvata() = 0;


};
class Primarie : public Petitie {
private :
	int personal;
public:
	void Rezolvata() {
		if (!personal) {
			cout << endl << "nu avem personalul necesar";
		}
		else {
			cout << endl << " avem personal necesar";
		}
	}
};

int Petitie::NrPetitii = 0;

void main() {

	//Petitie* petitii = NULL;

	Petitie p1;
	Petitie p2("20nov2020", "gigiel maria", 4, new string[4]{ "cate1","c2","c3","c4" }, true);
	Petitie p3("20nov2020", "gigiel maria", 4, new string[4]{ "cate1","c2","c3","c4" }, false);

	if (!p3) {
		cout << "nu are raspuns";
	}

	p1.afisare();
	p2.afisare();

	p1.setDataInreg("30ian2020");
	p1.setNume("cineva");
	p1.afisare();



	ofstream f("Fisiere.txt", ios::out);
	f << p2;
	cout << "Fisierul a fost scris" << endl;
	f.close();

	/*petitii = &p3;
	petitii->Rezolvata();
	cout << endl;
}*/
}