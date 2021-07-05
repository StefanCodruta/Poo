#include<iostream>
#include<string>
using namespace std;

class Apartament {
private:
	string locatie;
	float pret;
	int nrCamere;
	float *suprafeteCamere;

public:
	Apartament() {
		this->locatie = " ";
		this->pret = 0;
		this->nrCamere = 0;
		this->suprafeteCamere = NULL;
	}

	Apartament(string locatie, float pret) {
		this->locatie = locatie;
		this->pret = pret;
		this->nrCamere = 0;
		this->suprafeteCamere = NULL;
	}

	Apartament(string locatie, float pret, int nrCamere, float* suprafeteCamere) {
		this->locatie = locatie;
		this->pret = pret;
		this->nrCamere = nrCamere;
		if (nrCamere) {
			this->suprafeteCamere = new float[nrCamere];
			for (int i = 0; i < nrCamere; i++) {
				this->suprafeteCamere[i] = suprafeteCamere[i];
			}
		}
		else {
			this->suprafeteCamere = NULL;
		}
	}

	//copy constr
	Apartament(const Apartament &a){
		this->locatie = a.locatie; 
		this->pret = a.pret;
		this->nrCamere = a.nrCamere;
		if (this->nrCamere) {
			this->suprafeteCamere = new float[this->nrCamere];
			for (int i = 0; i < this->nrCamere; i++) {
				this->suprafeteCamere[i] = a.suprafeteCamere[i];
			}
		}
		else {
			this->suprafeteCamere = NULL;
		}
	}

	~Apartament() {
		if (this->suprafeteCamere != NULL) {
			delete[] this->suprafeteCamere;
		}
	}

	void print_data() {
		cout << "locatie: " << this->locatie << endl;
		cout << "pret: " << this->pret << endl;
		cout << "nr camere: " << this->nrCamere << endl;
		if(this->nrCamere){
			for (int i = 0; i < nrCamere; i++) {
				cout << "suprafata camera" << (i + 1) << ": " << suprafeteCamere[i] << endl;
			}
		}
		cout << "------------------------------------" << endl;
	}

	//setteri

	void set_suprafete(int nrCamere, float* suprafeteCamere) {

		if (this->suprafeteCamere != NULL) {
			delete[] this->suprafeteCamere;
		}
		this->nrCamere = nrCamere;
		if (this->nrCamere) {
			this->suprafeteCamere = new float[this->nrCamere];
			for (int i = 0; i < this->nrCamere; i++) {
				this->suprafeteCamere[i] = suprafeteCamere[i];
			}
		}
		else {
			this->suprafeteCamere = NULL;
		}

	}
	//operatori

	Apartament& operator=(const Apartament &a) {
		this->locatie = a.locatie;
		this->pret = a.pret;

		if (this->suprafeteCamere != NULL) {
			delete[] this->suprafeteCamere;
		}

		this->nrCamere = a.nrCamere;
		if (this->nrCamere) {
			this->suprafeteCamere = new float[this->nrCamere];
			for (int i = 0; i < this->nrCamere; i++) {
				this->suprafeteCamere[i] = a.suprafeteCamere[i];
			}
		}
		else {
			this->suprafeteCamere = NULL;
		}

		return *this;
	}

	Apartament& operator++() {
		this->pret++;
		return *this;
	}

	Apartament operator++(int i) {
		Apartament copie = *this;
		this->pret++;
		return copie;
	}


	//+ adauga o camera cu suprafata value
	Apartament operator+(float value) {
		Apartament copie = *this;
		float *v = new float[copie.nrCamere+1];
		for (int i = 0; i < copie.nrCamere; i++) {
			v[i] = copie.suprafeteCamere[i];
		}
		v[copie.nrCamere] = value;
		copie.nrCamere++;
		delete[] copie.suprafeteCamere;
		copie.suprafeteCamere = v;
		return copie;
	}

	float sum() {
		float suma = 0;
		if (suprafeteCamere != NULL) {
			for (int i = 0; i < nrCamere; i++) {
				suma += suprafeteCamere[i];
			}
		}
		return suma;
	}


	void useSpace(float amount) {
		if (amount > 0 && amount < this->sum()) {
			float suma = 0; int i;
			for (i = 0; suma < amount; i++) {
				suma += suprafeteCamere[i];
			}
			float *v = new float[nrCamere - i];
			int j = 0;
			for (int k = i; k < nrCamere; k++) {
				v[j] = suprafeteCamere[k];
				j++;
			}
			delete[] suprafeteCamere;
			nrCamere = nrCamere - i;
			suprafeteCamere = v;
		}
	}

//sterge suprafa value
	Apartament operator-(float value) {
		Apartament copie = *this;
		int k = 0;
		for (int i = 0; i < copie.nrCamere; i++) {
			if (copie.suprafeteCamere[i] <= value && value > 0) {
				k++;
				value -= copie.suprafeteCamere[i];
			}
			else {
				copie.suprafeteCamere[i] -= value;
				value = 0;
			}
		}
		float *v = new float[copie.nrCamere - k];
		int j = 0;
		for (int i = k; i < copie.nrCamere; i++) {
			v[j] = copie.suprafeteCamere[i];
			j++;
		}
		delete[] copie.suprafeteCamere;
		copie.nrCamere -= k;
		copie.suprafeteCamere = v;
		return copie;
	}

//adauga o camera cu supraf value
	Apartament& operator+=(float value){
		float *v = new float[nrCamere + 1];
		for (int i = 0; i < nrCamere; i++) {
			v[i] = suprafeteCamere[i];
		}
		v[nrCamere] = value;
		nrCamere++;
		delete[] suprafeteCamere;
		suprafeteCamere = v;
		return *this;
	}

//sterge suprafata value
	Apartament& operator-=(float value) {
		int k = 0;
		for (int i = 0; i < nrCamere; i++) {
			if (suprafeteCamere[i] <= value && value > 0) {
				k++;
				value -= suprafeteCamere[i];
			}
			else {
				suprafeteCamere[i] -= value;
				value = 0;
			}
		}
		float *v = new float[nrCamere - k];
		int j = 0;
		for (int i = k; i < nrCamere; i++) {
			v[j] = suprafeteCamere[i];
			j++;
		}
		delete[] suprafeteCamere;
		nrCamere -= k;
		suprafeteCamere = v;

		return *this;
	}

	Apartament& operator--() {
		float *v = new float[nrCamere - 1];
		for (int i = 0; i < nrCamere - 1; i++) {
			v[i] = suprafeteCamere[i];
		}
		delete[] suprafeteCamere;
		nrCamere--;
		suprafeteCamere = v;
		return *this;
	}

	Apartament operator--(int) {
		Apartament copie = *this;
		float *v = new float[nrCamere - 1];
		for (int i = 0; i < nrCamere - 1; i++) {
			v[i] = suprafeteCamere[i];
		}
		delete[] suprafeteCamere;
		nrCamere--;
		suprafeteCamere = v;
		return copie;
	}

//compara suprafete
	bool operator>(Apartament &a) {
		bool comp = this->sum() > a.sum();
		return comp;
	}

	bool operator>=(Apartament &a) {
		bool comp = this->sum() >= a.sum();
		return comp;
	}

	bool operator<(Apartament &a) {
		bool comp = this->sum() < a.sum();
		return comp;
	}

	bool operator<=(Apartament &a) {
		bool comp = this->sum() <= a.sum();
		return comp;
	}

	bool operator==(Apartament &a){
		bool comp = this->sum() == a.sum();
		return comp;
	}

	float getSpace(int index) {
		return suprafeteCamere[index];
	}

	float &operator[](int index){
		if (index >= 0 && index < nrCamere) {
			return suprafeteCamere[index];
		}
	}

	float partialSum(int index1, int index2){
		float sumapart = 0;
		for (int i = index1; i <= index2; i++) {
			sumapart += suprafeteCamere[i];
		}
		return sumapart;
	}

	Apartament  operator!() {
		Apartament copie = *this;
		copie.suprafeteCamere = NULL;
		return copie;
	}
	

	friend istream& operator>>(istream&, Apartament&);
	friend Apartament operator+(float, Apartament);
	friend ostream& operator<<(ostream&, Apartament &); 

};


Apartament operator+(float value, Apartament a) {
	float *v = new float[a.nrCamere + 1];
	for (int i = 0; i < a.nrCamere; i++) {
		v[i] = a.suprafeteCamere[i];
	}
	v[a.nrCamere] = value;
	a.nrCamere++;
	delete[] a.suprafeteCamere;
	a.suprafeteCamere = v;
	return a;
}

ostream& operator<<(ostream& out, Apartament &a) {
	out << "locatie:" << a.locatie << endl;
	out << "pret:" << a.pret << endl;
	out << "nr camere:" << a.nrCamere << endl;
	if (a.suprafeteCamere != NULL) {
		for (int i = 0; i < a.nrCamere; i++) {
			out << "suprafata camerei " << (i + 1) << ": " << a.suprafeteCamere[i]<< endl;
		}
	}
	return out;
}

istream& operator>>(istream& in, Apartament &a) {
	cout << "locatie:";
	in >> a.locatie;

	cout << "pret:";
	in >> a.pret;

	cout << "nr camere:";
	in >> a.nrCamere;

	for (int i = 0; i < a.nrCamere; i++)
	{
		cout << "suprafata camera" << (i + 1) << ":";
		in >> a.suprafeteCamere[i];
	}

	return in;
}



int main() {

	Apartament a1;
	float w[] = { 15,12,10 };
	Apartament a2("Brasov", 90, 3, w);
	a1.print_data();
	a2.print_data();

	Apartament a3 = a2;
	a3.print_data();

	Apartament a4;
	a4 = a3;
	
	++a3;
	
	Apartament a5 = a2 + 12;
	Apartament a6 = 15 + a3;
	Apartament a7 = a4++;
	Apartament a8;
	cin >> a8;
	
	float *v=NULL;
	a8.set_suprafete(3, w);

	a8.set_suprafete(0, v);


	a4.useSpace(20);

	a8 = a2 - 20;
	
	//cout << a8;

	a8 += 12;

	//cout << a8;

	a8 -= 10;

	//cout << a8;

	Apartament a9 = --a8;

	//cout << a9;

	a9 = a8--;

	//cout << a8;
	//cout << a9;

	if (a9 > a8) cout << "da" << endl;
	if (a9 < a8) cout << "da"; else cout << "nu";

	a9[0] = 12;

	cout << a9;

	cout << endl << a2.partialSum(0, 1) << endl;

	Apartament a11 = a2;
	a11.useSpace(15);
	a11.print_data();

	//a9 = !a2;

	//int total = (float)a2;
	//cout << total;

}