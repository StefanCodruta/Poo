#include<iostream>
#include<string>
#include<fstream>


using namespace std;

class Student {
private :
	const int id;
	static int nrOb;
	string dataExamen;
	int *noteEx;
	string denumireMaterie;

protected:
	int nrnoteEx;

public: 
	Student() :id(nrOb++) {
		denumireMaterie = "";
		dataExamen = "";
		nrnoteEx = 0;
		noteEx = NULL;

	}

	//constructor cu parametrii 
	Student(string nume, string data, int nr, int*note) :id(nrOb++) {
		if (nume.length() > 3) {
			denumireMaterie = nume;
		}
		else {
			denumireMaterie = "";
		}
		if (data.length() == 10) {
			dataExamen = data;
		}
		else {
			dataExamen = "";
		}
		if (nr > 0) {
			nrnoteEx = nr;
			noteEx = new int[nr];
			for (int i = 0; i < nr; i++) {
				noteEx[i] = note[i];
			}
		}
		else {
			nrnoteEx = 0;
			noteEx = NULL;
		}
	}
	//constr de copiere
	Student(const Student& sursa) :id(nrOb++) {
		denumireMaterie = sursa.denumireMaterie;
		dataExamen = sursa.dataExamen;
		nrnoteEx = sursa.nrnoteEx;
		noteEx = new int[sursa.nrnoteEx];
		for (int i = 0; i < sursa.nrnoteEx; i++) {
			noteEx[i] = sursa.noteEx[i];
		}
	}
	//destructor
	~Student() {
		if (noteEx) {
			delete[] noteEx;
		}
		nrOb--;

	}
	//operator=
	Student& operator=(const Student& dest) {
		if (noteEx) {
			delete[] noteEx;
		}
		denumireMaterie = dest.denumireMaterie;
		dataExamen = dest.dataExamen;
		nrnoteEx = dest.nrnoteEx;
		noteEx = new int[dest.nrnoteEx];
		for (int i = 0; i < dest.nrnoteEx; i++) {
			noteEx[i] = dest.noteEx[i];
		}
		return *this;
	}

	//accesori 
	string getDenumire() {
		return denumireMaterie;
	}
	void setDenumire(string denumireNoua) {
		if (denumireNoua.length() > 3) {
			denumireMaterie = denumireNoua;
		}
	}

	//afisare consola
	friend ostream& operator<<(ostream& out, Student& dest) {
		out << "denumirea:" << dest.denumireMaterie << endl;
		out << "data :" << dest.dataExamen << endl;
		out << "nr de note de la examen:" << dest.nrnoteEx << endl;
		for (int i = 0; i < dest.nrnoteEx; i++) {
			out << "nota este:" << dest.noteEx[i] << endl;
		}
		return out;
	}
	//daca aere note sau nu
	bool operator!() {
		if (this->nrnoteEx <= 0) {
			return true;
		}
		else {
			return false;
		}
	}

	int& operator[](int index) {
		if (index >= 0 && index < nrnoteEx) {
			return noteEx[index];
		}
		else {
			throw "ai dat index-ul gresit";
		}
	}

	//media notelor
	int Medienota() {
		int medie = 0;
		if (nrnoteEx > 0) {
			for (int i = 0; i < nrnoteEx; i++) {
				medie += noteEx[i]; //avem suma in medie 
			}
			medie /= nrnoteEx; //aflam media
		}
		return medie;  //se returneza in caz ca nu am note
		
	}
	/*friend ifstream& operator>>(ifstream& in, Student& a) {
		
		string temp;
		getline(in, temp);

		if (a.noteEx != NULL) {
			delete[]a.noteEx;
		}
		


		getline(in, temp);
		a.denumireMaterie = temp;

		getline(in, temp);
		a.dataExamen = stoi(temp);

		getline(in, temp);
		a.nrnoteEx = stoi(temp);

		return in;

	}*/

	//fisier binar
	friend ofstream& operator<<(ofstream &out, Student& s) {

		int nrBytes = s.denumireMaterie.length() + 1;

		out.write((char*)&nrBytes, sizeof(int));
		char buff[100];
		strcpy(buff, s.denumireMaterie.c_str());
		out.write((char*)buff, nrBytes);

		out.write((char*)&s.nrnoteEx, sizeof(int));
		for (int i = 0; i < s.nrnoteEx; i++) {
			out.write((char*)&s.noteEx[i], sizeof(int));
		}
		out.write((char*)&s.dataExamen, sizeof(string));

		return out;
	}
	//fisier binar
	friend ifstream& operator >>(ifstream& in, Student& su) {
		
		//string den;
		//in.read((char*)&den, sizeof(string));
		//string data;
		//in.read((char*)&data, sizeof(string));
		//int nrint;
		//in.read((char*)&nrint, sizeof(int));
		//int* notenoi = new int[nrint];
		//for (int i = 0; i < nrint; i++) {
		//	in.read((char*)&notenoi[i], sizeof(int));
		//}
		////su = Student(nrint, notenoi);
		//

		int nrBytes;
		in.read((char*)&nrBytes, sizeof(int));
		char buffDen[100];
		in.read((char*)buffDen, nrBytes);

		int nrNote;
		in.read((char*)&nrNote, sizeof(int));

		int* notenoi = new int[nrNote];
		for (int i = 0; i < nrNote; i++) {
			in.read((char*)&notenoi[i], sizeof(int));
		}
		//su = Student(buffDen, nrNote, notenoi);
		return in;
	}
	void adauganota(int notaadaugata) {
		int* no= new int[nrnoteEx + 1];
		for (int i = 0; i < nrnoteEx; i++) {
			no[i] = noteEx[i];
		}
		no[nrnoteEx] = notaadaugata;
		if (noteEx) {
			delete[] noteEx;
		}
		noteEx = no;
		nrnoteEx++;

	}

 };
 int Student::nrOb = 0;



 class Examen : public Student {
	 int nrStudenti = 0;
	 Student** studenti = NULL;

 public:

	 Examen(){}

	 Examen(int nr, Student** stu) {
		 if (nr > 0 && stu != NULL) {
			 nrStudenti = nr;
			 studenti = new Student*[nr];
			 for (int i = 0; i < nrStudenti; i++) {
				 studenti[i] = new Student(*stu[i]);
			 }
		 }
	 }
	 ~Examen() {
		 for (int i = 0; i < nrStudenti; i++) { //stergem fiecare obiect din vector si apoi vect 
			 if (studenti[i]) {
				 delete studenti[i];//stergere student din fiecare pointer
			 }
		 }
		 if (studenti) {
			 delete[] studenti; //stergem vect de pointeri
		 }
	 }
	 Examen(const Examen& dest) {
		 if (dest.nrStudenti > 0 && dest.studenti != NULL) {
			 nrStudenti = dest.nrStudenti;
			 studenti = new Student*[dest.nrStudenti];
			 for (int i = 0; i < dest.nrStudenti; i++) {
				 studenti[i] = new Student(*dest.studenti[i]);
			 }
		 }
	 }

	 Examen& operator=(const Examen& dest) {
		 if (this != &dest) {
			 for (int i = 0; i < nrStudenti; i++) {
				 if (studenti[i]) {
					 delete studenti[i];
				 }
			 }

			 if (studenti) {
				 delete[] studenti;
			 }

			 if (dest.nrStudenti > 0 && dest.studenti != NULL) {
				 nrStudenti = dest.nrStudenti;

				 studenti = new Student*[dest.nrStudenti];
				 for (int i = 0; i < dest.nrStudenti; i++) {
					 studenti[i] = new Student(*dest.studenti[i]);
				 }
			 }
			 else {
				 nrStudenti = 0;
				 studenti = NULL;
			 }
		 }
		 return *this;
	 }

	 friend ostream& operator<<(ostream& out, const Examen &ex) {
		 out << "nr studenti in examen: " << ex.nrStudenti << endl;
		 for (int i = 0; i < ex.nrStudenti; i++) {
			 out << *ex.studenti[i] << endl;
		 }
		 return out;
	 }

	 friend ofstream& operator<<(ofstream& out,const Examen& dest) {

		 out.write((char*)&dest.nrStudenti, sizeof(int));
		 for (int i = 0; i < dest.nrStudenti; i++) {
			 out << *dest.studenti[i];
		 }
		 return out;

	 }

	 friend ifstream& operator>>(ifstream& in, Examen& dest) {

		 int auxnr;
		 in.read((char*)&auxnr, sizeof(int));

		 Student** so = new Student*[auxnr];

		 for (int i = 0; i < auxnr; i++) {
			 so[i] = new Student();
			 in >> *so[i];
		 }
		 dest = Examen(auxnr, so);
		 for (int i = 0; i < auxnr; i++) {
			 if (so[i]) {
				 delete so[i];
			 }
		 }
		 if (so) {
			 delete[] so;
		 }
		 return in;
	 }

 };

void main() {

	 Student s;
	 int vectNote[4] = { 8,6,7,6 };

	 Student stud4;
	 Student stud1("gigel", "10/03/2019", 4,new int [4] { 7,6,5,3 });
	 Student stud2("ioana", "20/03/2019", 4, new int[4]{ 7,6,5,3 });
	 cout<< stud1 << endl;
	 cout << !stud1 << endl;// afiseaza false daca studentul are note

	 stud4.adauganota(5);
	 stud1.setDenumire("mate");
	 cout << stud1.getDenumire() << endl;

	 ofstream studenti("studenti.txt");
	 studenti << stud1;
	 studenti << stud2;

	 studenti.close();

	 ifstream dateFisier("studenti.txt");
	 if (dateFisier.is_open()) {
		 string linie;
		 while (!dateFisier.eof()) {
			 dateFisier >> linie;
			 cout << endl << "Continut al fisierului : " << linie;
		 }
		 dateFisier.close();
	 }
	 else cout << endl << "********************* eroare deschidere fisier";

	 ofstream fout;
	 fout.open("fisierBinar.bin", ofstream::out | ofstream::binary);
	 if (fout.is_open()) {
		 fout << stud4;
		 fout.close();
	 }

	 ifstream fin;
	 fin.open("fisierBinar.bin", ifstream::in | ifstream::binary);
	 if (fin.is_open()) {
		 fin >> stud2;
		 fin.close();
	 }

	 //*****************************************
	Examen ex;
	Student e[3] = { stud4, stud2, stud1 };
	Examen ex1(100, e);
	Examen ex2(ex1);
	//ex = ex1;

	Examen ex4;



 }