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


	virtual int getDmgTotal() {

		int s = 0;
		for (int i = 0; i < this->nrPuteri; i++) {
			s += this->dmg[i];
		}
		return s;
	}



	// supraincarcare-insemana sa declari aceasi fucntie cu acelasi nume dar cu lsita de parametri diferita .. 
	int getDmgTotal( int ajutorAtc_Coechipieri ) {

		int s = 0;
		for (int i = 0; i < this->nrPuteri; i++) {
			s += this->dmg[i];
		}
		s += ajutorAtc_Coechipieri;
		return s;
	}


	void marireDmguri(int x) {

		for (int i = 0; i < this->nrPuteri; i++) {
			this->dmg[i] += x;
		}
	}



	////  Erou           e1 ; 
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





class SuperErou : public Erou {
	//are si caracteristici comune... preluate de la erou...+ taote fucntiile 

	// caracteristicile speciale ale super eroului 
	char* superPutere;
	int atac; 

public:
	 
	// constructorii se destrctorul nu se mostenteste ... 
	// orice cosntructor pe care il vom implementa in calsa derivata (SuperErou)  va apela in mod  implicit  cosntrucotrul fara parametrii din calsa  (baza)Erou  ca sa coisntruiesca partea comuna... aia cu atributele  eroului, daca nu ai cosnt fara paramtrii inc alsa Erou ... PRIMESTI EROARE DE COMPILARE  ca nu o saiba cine sa cosntruaoisca aprtea de erou  
	//OBS! observam ca s a apelat mai itnai const fara pram dinc asla de baza apoi cosnt fara pram din clasa derivata ... asta inseamna ca cosntructorii se apelaza  descendent ... de la parinte (baza)   la copil(derivat)/...
	// OBS!  Daca nu dorim sa se mai apele const fara pramtri in mod feulat sa cosntruaisca partea de abza... Putem apela al cosntructor in mod explicit 

	SuperErou() {

		this->superPutere = new char[strlen("na") + 1];
		strcpy(this->superPutere, "na");
		this->atac = 0; 
	}


	// SuperErou se1(   2020,             "Fane",        'm',           2,   new int[2]{ 300, 200 },     "Atac fulger",  4500);
	SuperErou(int anC, const char* numeDat, char genDat, int nrPuteriDat, int* dmgDat, const char* sp, int at):Erou (anC, numeDat, genDat,nrPuteriDat,dmgDat)//in modmentuld e fata nu se mai apealza cosnt fara pramn dinc alsa de baza... se apealza in mod explciit ala cu param si ne face partea de baza cu valori date de noi la apel 
	{
		 
		this->atac = at;
		this->superPutere = new char[strlen(sp) + 1];
		strcpy(this->superPutere, sp);

	}



	SuperErou(int anc, const char* nu, const char* sp):Erou(  anc,nu, 'n', 0, NULL)
	{
		this->atac = 0;
		this->superPutere = new char[strlen(sp) + 1];
		strcpy(this->superPutere, sp);
	}


	//SuperErou se3                 (se1);
	SuperErou(      const SuperErou& sursa) :Erou ( (Erou)sursa   ) //am construit partea de baza pe baza surse care este un super erou convertit la erou 
	{
		

		this->atac = sursa.atac;
		this->superPutere = new char[strlen(sursa.superPutere) + 1];
		strcpy(this->superPutere, sursa.superPutere);

	}


	~SuperErou() {
		//stergem doar memoria dianmica din zona specifica... 
		if (this->superPutere) {
			delete[] this->superPutere;
		}
		//sa stiti ca destructorul se apelaza ascendent... adica mai intai se esterge partea specifica,,, apoi destructorula pealza in mod automat destrctroul dinc alsa de abza si sterge si partea de abza 
	}



	//                      se                =se1;
	SuperErou & operator = (  const SuperErou& sursa) 
	{
		//egalare parte de comuna baza ...
		this->Erou::operator=((Erou)sursa); //egaleaza partea de baza ...  

		//egalare parte specifica 
		if (this->superPutere) {
			delete[] this->superPutere;
		}

		this->atac = sursa.atac;
		this->superPutere = new char[strlen(sursa.superPutere) + 1];
		strcpy(this->superPutere, sursa.superPutere);
		return *this;
	}


	//down casting 
	SuperErou(const Erou& sursa) :Erou(sursa) {
		this->superPutere = new char[strlen("na") + 1];
		strcpy(this->superPutere, "na");
		this->atac = 0;
	}



	friend 	ostream& operator<< (ostream& o, SuperErou  sursa) {

		o << "Putere super: " << sursa.superPutere << endl;
		o << "Atac: " << sursa.atac << endl;
		o << (Erou)sursa << endl; //afiseaza sursa care e un supererou ca pe un Erou 

		return  o; 
	}



	// suprasciere/supradefinire ==>  sa declari inc alsa derivata aceasi fucntie cu acelasi tip returnat cu acealsi nume si aceasi lsita de aprmetri ... dar sa fac ceva diferit fata de prima 

	int getDmgTotal() {

		int s = 0;
		for (int i = 0; i < this->getNrPuteri(); i++) {
			s += this->getDmg()[i];
		}
		s += this->atac;
		return s;
	}


	
};



 


void main() {


	Erou e1;
	Erou e2(2021, "Gigel Baron", 'm', 3, new int[3]{ 300,600,200 });
 
	e1 = e2;
	e1.operator=(e2);
	Erou* pe = &e1;
	pe->operator=(e2);


	SuperErou se;
	SuperErou se1(2020, "Fane", 'm', 2, new int[2]{ 300, 200 }, "Atac fulger", 4500);
	SuperErou se2(2021, "Costel", "Vartejul Sabiei");


	// up casting.... este o functie a compilatorului care converteste un SuperErou la erou... se numeste up ... ca il converteste pe asta de jos la ala de sus... jso e Super eurpul... sus este Erou.. 

	 Erou e3= (Erou)se1; // se returneaza un erou creat pe baza lui se1... daca vrei il poti si salva intr un erou 
 
	 // Obs! daca nu avem cosntructor de copiere inc alsa se va apela cosnt copeire al compilatorului... cosntrucotruld e copiere al compilatorului apeleaza in  mod implicit cosntruoturl de copiere al calsei Erou si egaleaza partea de abza... dar pentru partea specifica face shallow copy...
	//pt ca shallow copy nu stie sa gestioneze pointeri vom crea inc sla super erou propuiul cosnt de copiere... care sa fac un deep copy corect.. 
	 SuperErou se3 (se1);
		

	 // daca nu ai op=- ... face la fael ca la cosnt de coipeire... egaleaza aprtea de abza corect dar la partea specifica face shallo copy .. asa ca o sa implementat propriul op=
	 se = se1;


	 // down casting ... converteste de la Erou la SuperErou ... dar trebuie sa o implementam noi... 
	 (SuperErou)e2;// convertim pe e2 care e Erou la Super erou... 


	 //daca nu avewm op<< in calsa  super erou se apealz adefault ala dinc asla erou afiseaza super eroul ca un erou 
	 //daca vrem sa il afiseze ca pe un super erou ... suprascriem iop<< in calsa derivata  Super erou 
	// cout << se1 << endl;

	//  cout << se1.getDmgTotal() << endl;
	 
	// cout<< e1.getDmgTotal(650)<<endl;


	 

	 //   virtualizare - latebinding 
	 // o derivare... implentant conceptul is a... 
	 // trebuie sa avem o fucntie/metoda (NU OPERATOR!!!) suprascrisa supradefinita ... 
	 //fucntia supradefinita sa o face virtuala in clasa de baza ... 

	 // iti mai trebuie un vector de pointeri la calsa de baza...  in care sa punem adrese de Erou si adrese de SUperErou
	 Erou* vectorPointeri[3] = { &e1, &se1, &e2 };  // am pus si adrese din alea si din alea ...  adica e un vector mixt.. 

	 //acum apelam fucntia supradefinita virtuala  pt vectorul nsotru de pointeri la calsa de abza...
	 //acum acesta fucntie ... se va comporta in mod specific fiecurai tip de adresa... cand gaseste adresa de e1 se apealza aia dinc alsa de abza ... cand gaste adresa de erou se apealszsa fducntia dinc alsa de abza... cnad gaseste adresa de super erou se apealza dinc alsa derivata ... 
	 for (int i = 0; i < 3; i++) {
		 cout << vectorPointeri[i]->getDmgTotal() << endl;
	 }



	 Erou;


	 SuperErou 


}








































