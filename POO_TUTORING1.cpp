#include <iostream>
#include <string>
#define _CRT_SECURE_NO_WARNINGS

using namespace std;

enum TipEmail 
{
	Normal, Important=100, Eveniment
};

class Email 
{  
	const int idEmail=0; //obligatoriu

	char subject[50]; //obligatoriu
	string from;     //oblugatoriu
	string *to= NULL; //vector dinamic de stringuri--0xcccc
	int  nrAdreseDestinatie=0;
	char* continut = NULL;

	TipEmail tip;  //obligatoriu
	 
	int zi;        //obligatoriu
	int luna;      // -"-
	int an;        //--"--

public:

	Email(int id, const char* sub, string from, TipEmail tip, int zi, int luna, int an):idEmail(id)
	{
		this->zi = zi;
		strcpy(this->subject, subject);
		this->from = from;
		this->tip = tip;
		this->luna = luna;
		this->an = an;

	}
	//au un parametru implicit intotdeauna
	void oFunctie() {
		int an = this->an;
	}

	int getId() {
		return this->idEmail;
	}
	~Email() {
		if (this->continut != NULL)
			delete[] this->continut;
		delete[] this->to; //scapam de memory leak 
	}

	friend void operator<<(ostream& consola, Email& email);
	friend void operator >>(istream& in, Email& email);
	Email operator +(const char* adresa) //elementul din tipul clasei nu se mai scrie atunci cand ii incarcam in clasa, gen email(vine prin this)
	{

		//facem o copie pentru this prin constructori cu parametri atunci cand nu avem constr de copiere
		Email rezultat(this->idEmail, this->subject, this->from, this->tip, this->zi, this->luna, this->an);




		string adresaNoua = string(adresa);
		// adresaNoua.c_str(); ---- conversie string to char*---
		string* destinatari = new string[this->nrAdreseDestinatie + 1];
		for (int i = 0; i < nrAdreseDestinatie; i++) {
			destinatari[i] = this->to[i];
			destinatari[this->nrAdreseDestinatie] = adresaNoua;
            strcpy(rezultat.subject, this->subject);
			rezultat.nrAdreseDestinatie = this->nrAdreseDestinatie += 1;
			delete[] this->to;
			this->to = destinatari;
			rezultat.to = destinatari;
			return rezultat;


		}
	}

	void operator=(const Email& email) 
	{
		strcpy(this->subject, email.subject);
		this->from = from;
		this->zi = email.zi;
		this->luna = email.luna;
		this->an = email.an;

		delete[]this->continut;
		if (email.continut != NULL) {
			this->continut = new char[strlen(email.continut) + 1];
			strcpy(this->continut, email.continut);
		}
		else this->continut = NULL;

		delete[]this->to;
		if (email.nrAdreseDestinatie != 0) {


			this->to = new string[email.nrAdreseDestinatie];
			for (int i = 0; i < email.nrAdreseDestinatie; i++)
				this->to[i] = email.to[i];
			this->nrAdreseDestinatie = email.nrAdreseDestinatie;
		}
		else {
			this->nrAdreseDestinatie = 0;
			this->to = NULL;
		}
		this->tip = email.tip;

	}

	//constr de copiere
	Email(const Email& email) :idEmail(email.idEmail)
	{
		strcpy(this->subject, email.subject);
		this->from = from;
		this->zi = email.zi;
		this->luna = email.luna;
		this->an = email.an;

		if (email.continut != NULL) {
			this->continut = new char[strlen(email.continut) + 1];
			strcpy(this->continut, email.continut);
		}
		else this->continut = NULL;
		if (email.nrAdreseDestinatie != 0) {


			this->to = new string[email.nrAdreseDestinatie];
			for (int i = 0; i < email.nrAdreseDestinatie; i++)
				this->to[i] = email.to[i];
			this->nrAdreseDestinatie = email.nrAdreseDestinatie;
		}
		else {
			this->nrAdreseDestinatie = 0;
			this->to = NULL;
		}
		this->tip = email.tip;

	}

	


};

//supraincarcare operatori globali 
void operator <<(ostream& consola, Email& email) {
	consola << std::endl << "---------------------";
	consola << endl << email.getId();
	consola << endl << "from: " << email.from;
	consola << endl << "subiect: " << email.subject;
	consola << endl << "data: " << email.zi<< "// "<<email.luna<< "//"<<email.an;
	consola << endl << "tip: " << email.tip;

	//validam ca sa nu crape
	if (email.continut == NULL)
		consola << endl << "fara continut";
	else consola << endl << email.continut;

	if (email.nrAdreseDestinatie == 0)
		consola << endl << "to: --";
	else {
		consola << endl << "to: ";
		for (int i = 0; i < email.nrAdreseDestinatie; i++)
			consola << email.to[i] << ";";
	}


}
void operator >>(istream& in, Email& email) 
{
	cout << endl << "Date email ";

	//..este constant nu se mai poate modifica
	//cout << endl << "NOUL ID: ";
	//cons >> email.idEmail;

	cout << endl << "subiect: ";
	in >> email.subject;

	cout << endl << "from: ";
	in >> email.from;
	cout << endl << "continut: ";

	char buffer[10000];
	in >> buffer;

	if (email.continut != NULL) //ne asiguram ca nu lasam valorile anterioare in memorie
		delete[] email.continut;

	email.continut = new char[strlen(buffer) + 1];
	strcpy(email.continut, buffer);

	/*var2
	email.continut = new char[10000];
	in >> email.continut;*/
	 
	cout << endl << "numar destinatari: ";
	in >> email.nrAdreseDestinatie;

	if (email.to != NULL)
		delete[] email.to;

	email.to = new string[email.nrAdreseDestinatie];
	for (int i = 0; i < email.nrAdreseDestinatie; i++) {
		cout << endl << "to: ";
		in >> email.to[i];
	}
	cout << endl << "tip email: (1-important, 2-normal, 3-evenimente) ";
	int tipCitit;
	in >> tipCitit;
	switch (tipCitit) {
	case 1 :
		email.tip = TipEmail::Important;
		break;
	case 2:
		email.tip = TipEmail::Normal;
		break;
	case 3:
		email.tip = TipEmail::Eveniment;
		break;
	default:
		email.tip = TipEmail::Normal;
	}
	
	cout << endl << "zi: ";
	in >> email.zi;
	cout << endl << "luna: ";
	in >> email.luna;
	cout << endl << "an: ";
	in >> email.an;

}

int main() {
	Email email(1, "tutoring c++", "mail@csie.ro", TipEmail::Important, 25, 3, 2020);//se stiva

	//obiect in heap 
	Email* pEmail=new Email(2, "tutoring c++", "mail@csie.ro", TipEmail::Important, 25, 3, 2020);

	cout << email;
	cout << *pEmail; //afiseaza un numar adica un pointer

	//cin >> email;
	
	//cout << email;
	//delete pEmail;
	 
	//int vb1 = 10;
	//int vb2 = vb1 + 10;

	 
 

	email = email + "test@ase.ro";

	Email email2 = email;
	email2 = email2 + "zoom@ase.ro";
	cout << email2;


}
