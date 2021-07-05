#include <iostream>
#include<string>
#include<fstream>

using namespace std; 

class DosarAdmitere {
private:

	char* CI;
	int* facultati;
	int nroptiuni;
	string NumeStudent;
	const int id;
public:
	static int contorId;

public:
	// *********metode de acces ale clasei***

	int getNroptiuni() {
		return this->nroptiuni;
	}
	void setOptiuni(int nroptiruninoi) {
		this->nroptiuni=nroptiruninoi;
	}
	int* getFacultati() {
		return this->facultati;
	}
	void setFacultati(int* OptiuniExtra, int optiuni) {
		if (this->facultati != NULL) {
			delete[] this->facultati;
		}
		this->nroptiuni = optiuni;
		this->facultati = new int[this->nroptiuni];
		for (int i = 0; i < optiuni; i++) {
			this->facultati[i] = OptiuniExtra[i];
		}
	}

	char* getCi(){
		return this->CI;
	}
	void setCi(const char* ci) {
		delete[]this->CI;
		this->CI = new char[strlen(CI) + 1];
		strcpy(this->CI, ci);
	}
	string getNumeStd() {

		return this->NumeStudent;
	}
	void setNumeStd(string numenou) {
		this->NumeStudent = numenou;
	}
	

	//***********constructori**************
	DosarAdmitere():id(contorId++) {
		cout << endl << "apel constructor implicit";
		this->CI = new char[strlen("anonim") + 1];
		strcpy(this->CI, "anonim");
		this->nroptiuni = 0;
		this->facultati = NULL;
		this->NumeStudent = "";

	}
	DosarAdmitere(const char* CI, int nroptiuni, int* facultati, string nume) : id(contorId++) {
		if (strlen(CI) >= 2) {
			this->CI = new char[strlen(CI) + 1];
			strcpy(this->CI, CI);
		}
		else {
			throw new exception("serie buletin invalida");
		}
		this->facultati = new int[nroptiuni + 1];
		for (int i = 0; i < this->nroptiuni; i++) {
			this->facultati[i] = facultati[i];
		}
		if (nroptiuni < 2) {
			throw new exception("optiuni prea putine pentru validare");
		}
		else {
			this->nroptiuni = nroptiuni;

		}
		this->NumeStudent = nume;

	}
	DosarAdmitere operator+(int nr) {
		DosarAdmitere copie = *this;
		copie.nroptiuni += nr;
		return copie;
	}
	DosarAdmitere operator+(int facultate) {
		for (int i = 0; i > this->nroptiuni; i++) {
			this->facultati[i] = this->facultati[i] + facultate;
		}
		return *this;
	}

	//metoda statica pt afisarea nr total de dosare create la un moment dat .
	//contorizeaza dosarele create daca NU AU FOST DEPUSE LA FACULTATE
	void TotalDosare(int x) {
		int contordosarenedepuse= 0;
		for (int i = 0; i < this->nroptiuni; i++)
		{
			if (facultati[i] <= x)
				contordosarenedepuse++;
		}
		return contordosarenedepuse;
	}
	


	friend ostream& operator<<(ostream& out, const DosarAdmitere& s);
	friend ofstream& operator<< (ofstream& fout, DosarAdmitere& ds);
	friend DosarAdmitere operator+(int facultate, DosarAdmitere& ds);
};

DosarAdmitere operator+(int facultate, DosarAdmitere& ds) {
	for (int i = 0; i < ds.nroptiuni; i++) {
		ds.facultati[i] = ds.facultati[i] + facultate;
	}
	return ds;
}
int DosarAdmitere::contorId = 0;
ostream& operator<<(ostream& out, const DosarAdmitere& s) {
	out << s.CI << endl;
	out << s.nroptiuni << endl;
	out << s.NumeStudent << endl;
	for (int i = 0; i < s.nroptiuni; i++) {
		out << s.facultati[i] << endl;
	}
	return out;
}
ofstream& operator<< (ofstream &fout, DosarAdmitere & ds) {
	if (fout) {
		fout << ds.getCi() << endl;
		fout << ds.getNroptiuni() << endl;
		fout << ds.getNumeStd() << endl;
		for (int i = 0; i < ds.getNroptiuni(); i++) {
			fout << ds.facultati[i] << endl;
		}

	}
}


//**relatia has a 
//relatie de incluziune, compunere a datelor 
// secretara pentru DosarAdmitere 
//dosarele de admitere sunt gestionate de catre secretarele ficarei sectii a facultatii 

void main(){

	DosarAdmitere d1;
	DosarAdmitere d2("rd 1875", 4, { 4,8,5,5 }, "gigel");

	d1.setCi("rd 18769");
	d1.setNumeStd("gigelfrone");

	cout<< d1 + 5;
	cout << d1;

	//d1.getNroptiuni(4);
	//d1.getFacultati(5);
	ofstream out;
	out.open("fisier.txt", ios::out);
	out << d1 << endl;
	out.close();



	//** utilizarea try catch pt a gestiona modificarea unui atribut pt care a fost
	// implementata metoda setterillor.Metoda setter trb sa genereze o exceptie specifica aplicatiei
	//pt date invalide. Utilizatorul este avertizat daca introduce date invalide de la consola avand posibilitatea sa le reintroduca



}
