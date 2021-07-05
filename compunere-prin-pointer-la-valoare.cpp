#include<iostream>
using namespace std;
#pragma warning ( disable: 4996)
#include<string>



class Erou {
private:

	char* nume;  // nume sa fie intotdeauna mai lung de 2 caractere  
	int nrPuteri;// numarul de puteri sa fie mai mare sau egal 0
	int* dmg;// dmg urile sa fie pozitive  
	char gen; // f  m  n   t   g  p     j   t g o // gen sa fie m sau f sau n 

	const int anCreare; // anul in care s a creat contul 

	static int limitaMinimaDuel; // limita de puteri ca un erou sa se paota duela cu alt erou


	// sa se genereze un id unic  constant pe baza unui camp static 

	const int id;
	static int nrEroi;


public:

	//  Erou           e1 ; 
	Erou(/* Erou* this */) :anCreare(2021), id(Erou::nrEroi++)      // cosntantul daor aici in lsita de initialziatori se initialzieaza nu se paote initializa in cosntrucotr intr e{}
	{
		this->gen = 'n';
		this->nrPuteri = 0;
		this->dmg = NULL;
		this->nume = new char[strlen("na") + 1];
		strcpy(this->nume, "na");

	}



	//  Erou      e2 (  2021,          "Gigel",        'G',            3,     new int[3]{ 345,655,200 });
	Erou(/*this*/    int anC, const char* numeDat, char genDat, int nrPuteriDat, int* dmgDat) :anCreare(anC), id(Erou::nrEroi++)
	{
		if (genDat == 'f' || genDat == 'm' || genDat == 'n')
		{
			this->gen = genDat;
		}
		else {
			this->gen = 'n';
		}


		if (nrPuteriDat > 0) {
			this->nrPuteri = nrPuteriDat;
			this->dmg = new int[nrPuteriDat];
			for (int i = 0; i < nrPuteriDat; i++) {
				if (dmgDat[i] >= 0) {
					this->dmg[i] = dmgDat[i];
				}
				else {
					this->dmg[i] = 0;
				}

			}

		}
		else {
			this->nrPuteri = 0;
			this->dmg = NULL;
		}


		if (strlen(numeDat) > 2) {

			this->nume = new char[strlen(numeDat) + 1];
			strcpy(this->nume, numeDat);
		}
		else {
			this->nume = new char[strlen("na") + 1];
			strcpy(this->nume, "na");
		}


	}


	// Erou    e3                 (e2);
	Erou(/*this*/  const   Erou& sursa) :anCreare(sursa.anCreare), id(Erou::nrEroi++)
	{

		this->gen = sursa.gen;
		this->nrPuteri = sursa.nrPuteri;
		this->dmg = new int[sursa.nrPuteri];
		for (int i = 0; i < sursa.nrPuteri; i++) {
			this->dmg[i] = sursa.dmg[i];
		}
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);

	}

	~Erou(/*this*/) //el primeste doar this ,,, ATAT  
	{

		if (this->dmg) {
			delete[] this->dmg;
		}
		if (this->nume) {
			delete[] this->nume;
		}
		Erou::nrEroi--;
	}


	//                     e2   =       e3
	Erou& operator = ( /*this*/ const  Erou& sursa)//nu scrii deloc an creare...  deoarece e2 a primit un an... si e3 a primit un an... acest an este cosntat... a fost pus de cosntructorii si nu se va mai modifica vreodata... 
	{
		// pentru a nu genera memory leaks trebuie sa dezalocam campurile this 
		if (this->dmg) {
			delete[] this->dmg;
		}
		if (this->nume) {
			delete[] this->nume;
		}

		// realocam memorie si copiem 

		this->gen = sursa.gen;
		this->nrPuteri = sursa.nrPuteri;
		this->dmg = new int[sursa.nrPuteri];
		for (int i = 0; i < sursa.nrPuteri; i++) {
			this->dmg[i] = sursa.dmg[i];
		}
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);


		return  *this;// ne ajuta la apelul in cascada


	}







	void setGen(/*this*/char genNou) {
		if (genNou == 'f' || genNou == 'm' || genNou == 'n')
		{
			this->gen = genNou;
		}
	}

	// e2.setNume(          "gigel");
	void setNume( /*this*/  const char* numeNou)
	{
		if (strlen(numeNou) > 2) {

			if (this->nume != NULL) {
				delete[] this->nume;
			}
			this->nume = new char[strlen(numeNou) + 1];
			strcpy(this->nume, numeNou);

		}
		//optional puteti trata si elseul..

	}

	// e2.setDmg(                  4,    new int[4]{445,450,100,200});
	void setDmg(/*this*/  int nrNouPuteri, int* dmgNou)
	{
		if (nrNouPuteri > 0) {
			//ca sa nu generam memory leaks stergem dmg urile vechi 
			if (this->dmg != NULL) {
				delete[] this->dmg;
			}
			this->nrPuteri = nrNouPuteri;
			this->dmg = new int[nrNouPuteri];
			for (int i = 0; i < nrNouPuteri; i++) {
				this->dmg[i] = dmgNou[i];
			}

		}



	}


	// Erou::setLimitaDuel(3);
	static void setLimita(int limNou) {
		if (limNou >= 0) {
			Erou::limitaMinimaDuel = limNou;
		}
	}




	// e2.getNrPuteri(); 
	int getNrPuteri(/*this*/) {

		return this->nrPuteri;

	}

	char* getNume() {
		return this->nume;// ne returneaza adresa de memorie a numelui 
	}

	char getGen() {
		return this->gen;
	}

	int* getDmg() {
		return this->dmg;
	}

	// get ii facem anului de creare? ii facem... ca getul ne da anul de creare... dar nu modifica acnul de creare 
	int getAnCreare() {
		return this->anCreare;
	}

	//  Erou::getLimitaDuel();
	// inseamna ca  fucntie getLimtiaDuel este statica ... adica se apelaza pt clasa
	static int getLimitaDuel() {
		return Erou::limitaMinimaDuel;
	}

	static int getNrEroi() {
		return Erou::nrEroi;
	}


	







 



	friend 	ostream& operator<< (ostream& o, Erou  sursa);


 



	friend istream& operator>> (istream& in, Erou& sursa);



	 


	 
 
 


 



};
int Erou::limitaMinimaDuel = 2;
int Erou::nrEroi = 0;


//                       cout <<        e2;
ostream& operator<< (ostream& o, Erou  sursa)
{

	o << "ID " << sursa.id << endl;
	o << sursa.getAnCreare() << endl;
	o << sursa.nume << endl;
	o << sursa.gen << endl;
	o << sursa.nrPuteri << endl;

	for (int i = 0; i < sursa.nrPuteri; i++) {
		o << sursa.dmg[i] << "  ";
	}
	o << endl;

	return o;
}
 


 
//compunere prin pointer valoare ... sau  compunere prin obiect.. 
class Joc {

	char* nume;
	Erou * erou; //pentru ca am luat aceasta compunere  nu se mai apelaza in mod implciit cosnt fara pram din clasa erou sa ne aloce memorie... ca noi avem un pointer in obiectul joc.. 

public:

	Joc() {
		this->nume = new char[strlen("na") + 1];
		strcpy(this->nume, "na");
		this->erou = new  Erou(); // ai pus in this   erou o adresa de memorie a unui erou  cosntruit fara parametrii 
	}

	Joc(const char* numeJoc, Erou e ) {
		this->nume = new char[strlen(numeJoc) + 1];
		strcpy(this->nume,  numeJoc);
		this->erou =  new Erou(e) ;// s a apela const copeire si nea pus in thsi erou un erou facut cu cosntructoruld e copeire dupa eroul e dat ca param 
	}


	Joc(const Joc& sursa) {
		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);
		this->erou =  new  Erou (* sursa.erou) ; 
	}

	~Joc() {
		if (this->nume) {
			delete[] this->nume;
		}

		if (this->erou) {
			delete  this->erou;// fara sa mai pui [] ... ca avem doar un obiect, NU VECTOR 
		}

	}


	Joc& operator= (const Joc& sursa) {
		if (this->nume) {
			delete[] this->nume;
		}

		if (this->erou) {
			delete  this->erou;// fara sa mai pui [] ... ca avem doar un obiect, NU VECTOR 
		}

		this->nume = new char[strlen(sursa.nume) + 1];
		strcpy(this->nume, sursa.nume);
		this->erou = new  Erou(*sursa.erou);


		return *this;
	}


	friend ostream& operator<< (ostream& o, Joc sursa) {

		o << "NUme: " << sursa.nume << endl;
		o << *sursa.erou << endl;// s a apelat op<< din prima clasa ca sa iti afiseze eroul din joc... 

		return o;
	}


};



void main() {


	Erou e1;
	Erou e2(2021, "Gigel Baron", 'm', 3, new int[3]{ 300,600,200 });
 
	Joc j;
	Joc j1("Super mario", e2);
	Joc j2(j1);
	j = j2;

 	cout << j2;


}




