#include<iostream>
#include<fstream>
#include<list>
#include<string>
using namespace std;

enum Functie {
	servant, sefformatie, voluntar, sofer

};


class Pompier {
	// dand aici in descriere valorile am suplinit const default 
	const int idPompier= nrPompieri++;
	static int nrPompieri;// staticul ce ne ajuta sa generam id ul 
	string nume="na";
	Functie functie=servant;
	int nrInterventii = 0;
	int* durate = NULL;

public:

	string getNUme() {
		return nume;
	}

	Pompier() {

	}


	Pompier(string nu , Functie fu) {

		if (nu.length() > 2) {
			nume = nu;
		}

		if (fu == servant || fu == sefformatie || fu == voluntar || fu == sofer) {
			functie = fu;
		}

		//nu le mai dam ca sunt initializate in descriere 
		//durate = NULL;
		//nrInterventii = 0;
	}



	Pompier(string nu, Functie fu, int nr,  int* du) {

		if (nu.length() > 2) {
			nume = nu;
		}

		if (fu == servant || fu == sefformatie || fu == voluntar || fu == sofer) {
			functie = fu;
		}
		if (nr > 0 && du != NULL) {

			nrInterventii = nr;
			durate = new int[nr];
			for (int i = 0; i < nr; i++) {
				durate[i] =du[i];
			}
		}
		//nu le mai dam ca sunt initializate in descriere 
		//durate = NULL;
		//nrInterventii = 0;
	}






	Pompier(const Pompier& sursa) {
		if (sursa.nume.length() > 2) {
			nume = sursa.nume;
	}

		if (sursa.functie == servant || sursa.functie == sefformatie || sursa.functie == voluntar || sursa.functie == sofer) {
			functie = sursa.functie;
		}
		if (sursa.nrInterventii > 0 && sursa.durate != NULL) {

			nrInterventii = sursa.nrInterventii;
			durate = new int[sursa.nrInterventii];
			for (int i = 0; i < sursa.nrInterventii; i++) {
				durate[i] = sursa.durate[i];
			}
		}
	}



	// p4=p4;
	Pompier& operator=(const Pompier& sursa) {
		if (this != &sursa) {//verificare sa nu se faca auto atribuire sau auto-asignare

		//	cout << this << endl;
	//		cout << &sursa << endl;
			if (durate) {
				delete[] durate;
			}
			if (sursa.nume.length() > 2) {
				nume = sursa.nume;
			}

			if (sursa.functie == servant || sursa.functie == sefformatie || sursa.functie == voluntar || sursa.functie == sofer) {
				functie = sursa.functie;
			}
			if (sursa.nrInterventii > 0 && sursa.durate != NULL) {

				nrInterventii = sursa.nrInterventii;
				durate = new int[sursa.nrInterventii];
				for (int i = 0; i < sursa.nrInterventii; i++) {
					durate[i] = sursa.durate[i];
				}
		}
			else {
				nrInterventii = 0;
				durate = NULL;
			}
		}
		else {
			cout << "Adrese la fel" << endl;
			cout << this << endl;
			cout << &sursa << endl;
		}

		return *this;

	}


	friend ostream& operator<<(ostream& out, const Pompier& sursa) {
		out << "ID " << sursa.idPompier << endl;
		out << "Pompier " << sursa.nume << endl;

		switch (sursa.functie)
		{
		case 0: {
			out << "Functie servant " << endl;
			break;
		}
		case 1: {
			out << "Functie sef formatie " << endl;
			break;
		}
		case 2: {
			out << "Functie  sofer " << endl;
			break;
		}
		case 3: {
			out << "Functie  voluntar " << endl;
			break;
		}
		default:
			out << "Functie servant " << endl;
			break;
		}


		out << "Numar interventii " << sursa.nrInterventii << endl;
		for (int i = 0; i < sursa.nrInterventii; i++) {
			out << "Interventia " << i + 1<<":" << sursa.durate[i] <<" minute"<< endl;
		}



		return out;
	}







	friend ofstream& operator<<(ofstream& out, const Pompier& sursa) {
		//nu se scrie cosntantul in fisier 

		int nrBytesNume = sursa.nume.length() + 1;
		out.write((char*)&nrBytesNume, sizeof(int));
		char buff[500];
		strcpy(buff, sursa.nume.c_str());
		out.write((char*)buff, nrBytesNume);


		int funct = 0;

		switch (sursa.functie)
		{
		case 0: {
			funct = 0;
			break;
		}
		case 1: {
			funct = 1;
			break;
		}
		case 2: {
			funct = 2;
			break;
		}
		case 3: {
			funct = 3;
			break;
		}
		default:
			funct = 0;
			break;
		}

		out.write((char*)& funct, sizeof(int));
		out.write((char*)& sursa.nrInterventii, sizeof(int));
		for (int i = 0; i < sursa.nrInterventii; i++) {
			out.write((char*)& sursa.durate[i], sizeof(int));

		}

		return out;
	}


	friend  ifstream& operator>>(ifstream& in, Pompier& sursa) {
		int nrBytesNume;


		in.read((char*)&nrBytesNume, sizeof(int));
		char buffNume[500];
		in.read((char*)buffNume, nrBytesNume);


		int funct = 0;
		in.read((char*)&funct, sizeof(int));
		Functie auxFun;

		switch ( funct)
		{
		case 0: {
			auxFun = servant;
			break;
		}
		case 1: {
			auxFun = sefformatie;
			break;
		}
		case 2: {
			auxFun = sofer;

			break;
		}
		case 3: {
			auxFun = voluntar;

			break;
		}
		default:
			auxFun = servant;
			break;
		}

		int nrInt;
		in.read((char*)&nrInt, sizeof(int));

		int* durateNoi = new int[nrInt];

		for (int i = 0; i < nrInt; i++) {
			in.read((char*)& durateNoi[i], sizeof(int));

		}

		sursa = Pompier(buffNume, auxFun, nrInt, durateNoi);// am egala sursa obiectului pentru care s a apelat op>> cu Pompier obiect local creat pe baza la ce s a citit din fisierul binar 

		return in;
	}








	~Pompier() {
		if (durate) {
			delete[] durate;
		}
		nrPompieri--;
	}

	void adaugaInterventie(int InterventieNoua) {

		int* vn = new int[nrInterventii + 1];
		for (int i = 0; i < nrInterventii; i++) {
			vn[i] = durate[i];
		}
		vn[nrInterventii] = InterventieNoua;
		if (durate) {
			delete[] durate;
		}
		durate = vn;
		nrInterventii++;// actualziarea corespunzatoare a nr itnerventii




	}



	float getMedie() {
		float med = 0;
		if (nrInterventii > 0) {
			for (int i = 0; i < nrInterventii; i++) {
				med += durate[i];//avem suma in med acum
			}
			med /= nrInterventii;//acum am  aflat media 
			return med;//returnez media
		}
		return med;//returnez media in caz de nu am itnerventii ... 0 ... cu cat e sus initializata 
	}

	int getSuma() {//suma durate pt un pompier
		int  sum = 0;
		
			for (int i = 0; i < nrInterventii; i++) {
				sum += durate[i];//avem suma in med acum
			}			
		
		return sum;//returnez media in caz de nu am itnerventii ... 0 ... cu cat e sus initializata 
	}



	int getNrInterventiiMaiMariCa(int x) {
		int  contorInterventiiMaiMariCaX = 0;
		for (int i = 0; i < nrInterventii; i++) {
			if (durate[i] >= x) {
				contorInterventiiMaiMariCaX++;
}
		}
		return contorInterventiiMaiMariCaX;
	}



	//ca sa faci consultare si modificare trebuie sa pui la tipul returnat & 
	int& operator[](int i) {
		if (i >= 0 && i < nrInterventii) {
			return durate[i];
		}
		else {
			throw new exception();
		}
	}




};
int Pompier::nrPompieri = 0;




class FormatieInterventie{
	char idFormatie[30]{"na"};
	int nrPompieri=0;
	Pompier ** pompieri = NULL;

public:
	
	
	FormatieInterventie() {

	}




	//cosntructorul clasei'
	FormatieInterventie(const char* idfor, int nrp, Pompier** po)
	{
		strcpy(idFormatie, idfor);
		if (nrp > 0 && po !=NULL) {
			nrPompieri = nrp;
			pompieri = new Pompier*[nrp];
			for (int i = 0; i < nrPompieri; i++) {
				pompieri[i] = new Pompier(*po[i]);
			}
		}

	}

	~FormatieInterventie() {
		for (int i = 0; i < nrPompieri; i++) {
			if (pompieri[i]) {
				delete pompieri[i];//fara paranteze patrate ca stergem un singur obiect din fiecare pointer
			}
		}

		if (pompieri) {
			delete[] pompieri;//cu [] ca stergem tot vectorul de pointeri 
		}
		//ps mai itnai facem stergerea cu for sa stergem fiecare obiect apoi vectorul ....

	}

	FormatieInterventie(const FormatieInterventie& sursa)
	{
		strcpy(idFormatie, sursa.idFormatie);
		if (sursa.nrPompieri > 0 && sursa.pompieri != NULL) {
			nrPompieri = sursa.nrPompieri;
			pompieri = new Pompier*[sursa.nrPompieri];
			for (int i = 0; i < sursa.nrPompieri; i++) {
				pompieri[i] = new Pompier(*sursa.pompieri[i]);
			}
		}

	}

	FormatieInterventie& operator=(const FormatieInterventie& sursa)
	{
		if (this != &sursa) {
			for (int i = 0; i < nrPompieri; i++) {
				if (pompieri[i]) {
					delete pompieri[i]; 
				}
			}

			if (pompieri) {
				delete[] pompieri;
			}
			strcpy(idFormatie, sursa.idFormatie);
			if (sursa.nrPompieri > 0 && sursa.pompieri != NULL) {
				nrPompieri = sursa.nrPompieri;
				
				pompieri = new Pompier*[sursa.nrPompieri];
				for (int i = 0; i < sursa.nrPompieri; i++) {
					pompieri[i] = new Pompier(*sursa.pompieri[i]);
				}
			}
			else {
				nrPompieri = 0;
				pompieri = NULL;
			}
		}
	
		return *this;
	}



	friend ostream& operator<<(ostream& out, const FormatieInterventie& sursa) {

		out << "ID Ft ormatie " << sursa.idFormatie << endl;
		out << "Nr pompieri in formatie " << sursa.nrPompieri << endl;
		for (int i = 0; i < sursa.nrPompieri; i++) {
			out << *sursa.pompieri[i]<<endl;
		}
		return out;
	}



	friend ofstream& operator<<(ofstream& out, const FormatieInterventie& sursa) {
		//nu se scrie cosntantul in fisier 

		int nrBytesIDFOR = strlen(sursa.idFormatie)+ 1;
		out.write((char*)&nrBytesIDFOR, sizeof(int));
		
	
		out.write((char*)sursa.idFormatie, nrBytesIDFOR);



		out.write((char*)& sursa.nrPompieri, sizeof(int));
	
		for (int i = 0; i < sursa.nrPompieri; i++) {
			out << *sursa.pompieri[i];
		}

		return out;
	}


	friend  ifstream& operator>>(ifstream& in, FormatieInterventie& sursa) {
		int nrBytesIDF;


		in.read((char*)&nrBytesIDF, sizeof(int));
		char idfor[30];
		in.read((char*)idfor, nrBytesIDF);


	
		int AuxNrPompieri;
		in.read((char*)&AuxNrPompieri, sizeof(int));

		Pompier** po = new Pompier*[AuxNrPompieri];


		for (int i = 0; i < AuxNrPompieri; i++) {
			po[i] = new Pompier();
			in >> *po[i];
		}

		sursa = FormatieInterventie(idfor, AuxNrPompieri, po);
		for (int i = 0; i < AuxNrPompieri; i++) {
			if (po[i]) {
				delete po[i];
			}
		}
		if (po) {
			delete[] po;
		}

		return in;
	}

};


void main() {


	Pompier p;
	Pompier p1;
	Pompier p2("Gabriel", servant);
	Pompier p3(p2);
	Pompier p4("Gigel", sefformatie, 3, new int[3]{ 23,43,54 });
	//cout << p4;
	p4 = p2;
	p4.adaugaInterventie(233);
	p4.adaugaInterventie(23);
	//cout << p4;
	//cout << p4.getMedie() << endl;

	//cout<<	p4.getNrInterventiiMaiMariCa(30)<<endl;
	p4[1] = 2322;// modificare ... 
	//cout << p4[1]; // consultare
	//cout << p4;


	ofstream fout;
	fout.open("fisierBinar.bin", ofstream::out | ofstream::binary);
	if (fout.is_open()) {
		fout << p4;
		fout.close();
	}

	ifstream fin;
	fin.open("fisierBinar.bin", ifstream::in | ifstream::binary);
	if (fin.is_open()) {
		fin >> p;
		fin.close();
	}
	//cout << p;


	FormatieInterventie fp;
	//vector de poitneri static vp
	Pompier * vp[3] = {& p4,&p2,&p3 };
	FormatieInterventie fp1("123POM", 3, vp);
	FormatieInterventie fp2(fp1);
	fp = fp1;

	FormatieInterventie fp4;
	ofstream fout1;
	fout1.open("fisierBinar1.bin", ofstream::out | ofstream::binary);
	if (fout1.is_open()) {
		fout1 << fp1;
		fout1.close();
	}

	ifstream fin1;
	fin1.open("fisierBinar1.bin", ifstream::in | ifstream::binary);
	if (fin1.is_open()) {
		fin1 >> fp4;
		fin1.close();
	}
	//cout << fp4;


	// container de tip stl LIST
	list <Pompier> listaPompieri;
	listaPompieri.push_front( p4 );
	listaPompieri.push_front(p2);
	listaPompieri.push_front(p3);
	//mai sus am adaugat la inceputul listei cate un obiect de tip pompier...

	list<Pompier >::iterator it;
	for (it = listaPompieri.begin(); it != listaPompieri.end(); it++) {
		cout << "Pompierul " << (*it).getNUme() << " a lucrat in total " << (*it).getSuma() << " minute in toate interventiile" << endl;
	}

}