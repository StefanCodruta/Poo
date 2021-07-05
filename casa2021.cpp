#include<iostream>
#include<iostream>
#include<vector>
using namespace std;


class Casa {
	int const id;
	int suprafata;
	int nr_locatari;
	int nr_camere;
	int* camere;
	bool etaj;
public:
	Casa():id(0) {
		this->suprafata = 0;
		this->nr_locatari = 0;
		this->nr_camere = 0;
		this->camere = nullptr;
		this->etaj = false;

	}
	Casa(int supraf, int nr,int nr_c, int* camere, bool etaj) :id(id) {
		this->suprafata = supraf;
		this->nr_locatari = nr;
		this->nr_camere = nr_c;
		this->camere = new int[nr];
		for (int i = 0; i < nr; i++) {
			this->camere[i] = camere[i];
		}
	}

	Casa(const Casa& c):id(id) {
		this->suprafata = c.suprafata;
		this->nr_locatari = c.nr_locatari;
		this->nr_camere = c.nr_camere;
		this->camere = new int[c.nr_locatari];
		for (int i = 0; i < c.nr_locatari; i++) {
			this->camere[i] = camere[i];
		}

	}


	friend ostream& operator<<(ostream& os, Casa& c) {
		os << "Suprafata ;" << c.suprafata<<endl;
		os << "Nr locatari " << c.nr_locatari << endl;
		return os;
	}

	bool operator()(int a) {
		if (a > 0 &&  a < nr_camere) {
			if (nr_locatari > nr_camere)
			{
				return true;
			}

		}
		
		
	}
	bool operator==(Casa c) {
		if (nr_locatari > c.nr_locatari)
			return true;
		else
			return false;
	}
	~Casa() {
		delete[]camere;
	}


};

class Penthouse:public Casa {
	int nr_camere;
public:
	Penthouse() :Casa() {
		this->nr_camere = 0;
	}
	Penthouse(int nr_c, int supraf, int nr_l,int nr_m, int* camere, bool etaj) :Casa(supraf, nr_l,nr_m, camere, etaj) {
		this->nr_camere = nr_c;
	}
		
	friend ostream& operator<<(ostream& os, Penthouse& p) {
		os << "Nr camere :" << p.nr_camere;
		return os;
	}


	~Penthouse() {

	}

	};
	



void main() {
	Casa c1;
	Casa c2(123, 3,2, new int[3]{ 2,3,4 }, false);
	cout << c2;

	c2 == c1;

	Penthouse p1;
	Penthouse p2(3, 123, 2,2, new int[2]{ 1,2 }, true);

}