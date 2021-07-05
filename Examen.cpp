#include<iostream>
#include<string>
using namespace std;

class Student {
private:
	const int id;
	static int nrOb;
	string dataExamen;
	int* noteExamen;
	string denumireMaterie;


protected:
	int nrNoteExamen;

public:

	Student() :id(nrOb++) {
		denumireMaterie = "NA";
		dataExamen = "NA";
		nrNoteExamen = 0;
		noteExamen = NULL;

	}

	Student(string den, string dat, int nr, int* note) :id(nrOb++) {
		if (den.length() > 3) {
			denumireMaterie = den;
		}
		else {
			denumireMaterie = "NA";
		}
		if (dat.length() == 10) {
			dataExamen = dat;
		}
		else {
			dataExamen = "na";
		}
		if (nr > 0) {
			nrNoteExamen = nr;
			noteExamen = new int[nr];
			for (int i = 0; i < nr; i++) {
				noteExamen[i] = note[i];
			}
		}
		else {
			nrNoteExamen = 0;
			noteExamen = NULL;
		}



	}


	Student(const Student& sursa) :id(nrOb++) {
		denumireMaterie = sursa.denumireMaterie;
		dataExamen = sursa.dataExamen;
		nrNoteExamen = sursa.nrNoteExamen;
		noteExamen = new int[sursa.nrNoteExamen];
		for (int i = 0; i < sursa.nrNoteExamen; i++) {
			noteExamen[i] = sursa.noteExamen[i];
		}
	}


	~Student() {
		if (noteExamen) {
			delete[]noteExamen;
		}
		nrOb--;
	}

	Student& operator=(const Student& sursa) {
		if (noteExamen) {
			delete[]noteExamen;
		}
		denumireMaterie = sursa.denumireMaterie;
		dataExamen = sursa.dataExamen;
		nrNoteExamen = sursa.nrNoteExamen;
		noteExamen = new int[sursa.nrNoteExamen];
		for (int i = 0; i < sursa.nrNoteExamen; i++) {
			noteExamen[i] = sursa.noteExamen[i];
		}
		return*this;

	}


	string getDenumire() {
		return denumireMaterie;
	}


	void setDenumire(string denumireNoua) {
		if (denumireNoua.length() > 3) {
			denumireMaterie = denumireNoua;
		}
	}


	friend ostream& operator<<(ostream& out, Student& sursa) {
		out << "Denumirea este: " << sursa.denumireMaterie << endl;
		out << "Data examenului: " << sursa.dataExamen<<endl;
		out << "Numarul de note de la examen: " << sursa.nrNoteExamen<<endl;
		for (int i = 0; i <sursa.nrNoteExamen; i++) {
			out << "Nota este: " << sursa.noteExamen[i] << endl;
		}
		return out;
	}

	bool operator!() {
		if (this->nrNoteExamen <= 0) {
			return true;
		}
		else {
			return false;
		}
	}

	int& operator[](int index) {
		if (index >= 0 && index < nrNoteExamen) {
			return noteExamen[index];
		}
		else {
			throw"Ai dat index gresit";
		}
	}


	int medieNote() {
		int med = 0;
		if (nrNoteExamen > 0) {
			for (int i = 0; i < nrNoteExamen; i++) {
				med += noteExamen[i];
		}
			med /= nrNoteExamen;
		}
		return med;
	}

	int CeaMaiMicaNota() {
		int min = 0;
		if (this->nrNoteExamen > 0) {
			min = noteExamen[0];
			for (int i = 0; i < nrNoteExamen; i++) {
				if (min > noteExamen[i]){
					min=noteExamen[i];
					}
			}
		}
		return min;
	}

	bool operator==(Student sursa) {
		return medieNote() == sursa.medieNote();
	}



	int suma() {
		int sum = 0;
		for (int i = 0; i < nrNoteExamen; i++)
		{
			sum += noteExamen[i];
		}
		return sum;
	}


};


int Student::nrOb = 0;

void main() {

	Student s;
	int vectNote[4] = { 8,5,7,6 };
	Student s1("Micro","15/06/2020",1, vectNote);
	Student s2(s1);
	s = s1;
	cout << s1<<endl;
	cout << !s1<<endl;//afiseaza false-0, deoarece s1 are note


	s1.setDenumire("Analiza");
	cout << s1.getDenumire()<<endl;

	try {
		s1[99];
	}
	catch (const char* mesaj) {
		cout << mesaj << endl;
	}

	if (s == s2) {
		cout << "Aceleasi note" << endl;
	}
	else {
		cout << "Note diferite" << endl;
	}

	cout<<s1.medieNote()<<endl;
	cout << s1.CeaMaiMicaNota()<<endl;

	
}