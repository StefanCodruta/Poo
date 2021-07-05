#include <iostream>
#include <string>
using namespace std;

class LocDeParcare
{
public:
	enum TipLoc { autoturism = 1, microbuz = 2, handicap = 3 };
private:
	int nrLoc;
	TipLoc tipLoc;

	//1. Creati un constructor implicit pentru clasa LocDeParcare
//acesta va initializa nrLoc cu 0 si tipLoc cu autoturism
public:
	LocDeParcare() {
		cout << endl << "apel cst implicit";
		this->nrLoc = 0;
		this->tipLoc = autoturism;
	}
	LocDeParcare(int nrLoc, TipLoc tip) {
		this->nrLoc = nrLoc;
		this->tipLoc = tip;
	}
	int getNr() {
		return this->nrLoc;
	}

};

class Parcare
{
private:
	string adresa;
	LocDeParcare* locuriDeParcare;
	int nrLocuri;
public:
	const int idParcare = 0;
	static int nrParcari;

	//2. Modificati constructorul implicit din clasa Parcare de mai sus
//acesta va initializa adresa cu "Bucuresti"
//locuriDeParcare cu nullptr si nrLocuri cu 0
	Parcare() :idParcare(nrParcari)
	{
		cout << endl << "constr parcare";
		this->adresa = "Bucuresti";
		this->locuriDeParcare = nullptr;
		this->nrLocuri = 0;
	}

	//3. Modificati constructorul cu 3 parametri: adresa, locuriDeParcare, nrLocuri
//acesta va initializa cele 3 atribute cu valorile primite
//daca parametrul locuriDeParcare este nullptr, la fel se va initializa si atributul

	//4. Modificati cei doi constructori din clasa Parcare pentru a intializa si campul constant idParcare
//idParcare va fi calculat automat pe baza campului static
//(campul static va fi incrementat in cei doi constructori, iar idParcare va lua valoarea acestuia)
//de ex: prima parcare va avea id-ul 1, a doua id-ul 2, s.a.m.d.
	Parcare(string adresa, LocDeParcare* locuriDeParcare, int nrLocuri) :idParcare(nrParcari++)
	{
		this->nrLocuri = nrLocuri;
		this->adresa = adresa;
		this->locuriDeParcare = new LocDeParcare[nrLocuri];
		for (int i = 0; i < nrLocuri; i++) {
			this->locuriDeParcare[i] = locuriDeParcare[i];
		}

	}
	//5. Adaugati un destructor in clasa Parcare pentru a dezaloca
//campul(urile) alocate dinamic
	~Parcare() {
		if (this->locuriDeParcare != NULL)
			delete[] this->locuriDeParcare;
	}
	//7. Modificati supraincarcarea pentru operator=
//aceasta va realiza o copie in profunzime (deep copy) a atributelor
//operatorul accepta apeluri in cascada

	Parcare& operator=(const Parcare& p)
	{
		if (this->locuriDeParcare != p.locuriDeParcare) {
			this->adresa = p.adresa;
			this->nrLocuri = p.nrLocuri;
			if (this->locuriDeParcare != NULL) {
				delete[] this->locuriDeParcare;
			}
			this->locuriDeParcare = new LocDeParcare[nrLocuri];
			for (int i = 0; i < nrLocuri; i++) {
				this->locuriDeParcare[i] = p.locuriDeParcare[i];
			}
		}
		return *this;
	}
	LocDeParcare* getLocuri() {
		return this->locuriDeParcare;
	}

	// 8. Modificati metoda setLocuriParcare astfel incat sa modifice vectorul de locuri de parcare
		//metoda valideaza parametrii si setaza vectorul nullptr si numarul de locuri 0
		//daca vectorul primit ca parametru este null sau numarul de locuri mai mic sau egal decat 0
	void setLocuriParcare(LocDeParcare* locuri, int nr_locuri)
	{
		if (locuriDeParcare >= 0) {
			if (this->locuriDeParcare != NULL) {
				delete[]this->locuriDeParcare;
			}
			this->locuriDeParcare = new LocDeParcare[nrLocuri];
			for (int i = 0; i < nrLocuri; i++) {
				this->locuriDeParcare[i] = locuriDeParcare[i];
			}
			this->nrLocuri = nrLocuri;
		}
	}

	//6. Adaugati clasei un constructor de copiere astfel incat
	//sa se realizeze o copie in profunzime (deep copy) a atributelor
	//se va realiza si copierea campului constant
	Parcare(const Parcare& p) : idParcare(p.nrParcari) {
		this->adresa = p.adresa;
		this->nrLocuri = p.nrLocuri;
		this->locuriDeParcare = new LocDeParcare[nrLocuri];
		for (int i = 0; i < p.nrLocuri; i++) {
			this->locuriDeParcare[i] = p.locuriDeParcare[i];
		}
	}

	//9. Supraincarcati operatorul de cast explicit la int in clasa Parcare
	//acesta va returna numarul de locuri de parcare
	operator unsigned int() {
		return this->nrLocuri;
	}

     friend ostream& operator<<(ostream& out, Parcare& p);
};
int Parcare::nrParcari = 0;

//10. Supraincarcati operatorul de afisare la consola pentru clasa Parcare
//acesta va afisa adresa pe prima linie si numarul de locuri de parcare pe o linie noua
//Exemplu de afisare la consola:
//Bucuresti
//25
//(parcare din Bucuresti cu 25 de locuri)
ostream& operator<<(ostream& out, Parcare& p) {

	out << endl << "-------------------------------------------";
	out << endl << "adresa" << p.adresa;
	out << endl << "nr locuri" << p.nrLocuri;

	for (int i = 0; i < p.nrLocuri; i++) {
		out << p.getLocuri()[i];
	}
	return out;
}
// !!!CITITI CU ATENTIE!!!
//- Sunt punctate doar solutiile originale si individuale
//- Orice incercare de frauda va duce la pierderea intregului punctaj de seminar
//- Signatura functiilor nu se poate modifica, doar continului lor
//- Solutiile cu erori de compilare nu vor fi evaluate
//- Subiectele pot fi tratate in orice ordine, cu exceptia constructorilor
//- Fiecare cerinta valoareaza 1 punct

int main()
{
	LocDeParcare l1;
	//Playgroud
	//Testati aici functiile dorite si folositi debugger-ul pentru eventualele probleme

	LocDeParcare p[2];
	Parcare p1("bucuresti",p ,2);
	LocDeParcare v[3];
	Parcare p2("brasov", v, 3);

	cout << p2;
	Parcare p3 = p2;

	 p3.setLocuriParcare(v,3);
	 cout << p3;

	p1 = p3; 

	unsigned int nrLocuri = p3;

}