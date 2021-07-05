#include<iostream>
#include<string>
#include<fstream>

using namespace std;

class FirmaCatering {
private:
	char* denumireClient;
	char dataEveniment[14];
	int nrProduse;
	int* caintitatiProduse;
	float pret;

	const int idProdus;
	static int nrComenzi;

public:
	FirmaCatering() :idProdus(FirmaCatering::nrComenzi++) {
		
		this->nrProduse = 0;
		this->denumireClient = new char[strlen("ceva") + 1];
		strcpy(this->denumireClient, "ceva");
		strcpy(this->dataEveniment, "zz/ll/nnnn/hh");
		this->caintitatiProduse = nullptr;
		this->pret = 0;

	}
	FirmaCatering(const char* denumire, const char* data, float pret, int nrProduse, int* cantitati) : idProdus(FirmaCatering::nrComenzi++) {

		this->denumireClient = new char[strlen(denumire) + 1];
		strcpy(this -> denumireClient, denumire);
		if (pret > 0) {
			this->pret = pret;

		}
		if (nrProduse > 0) {
			this->nrProduse = nrProduse;
			this->caintitatiProduse = new int[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
			if (cantitati[i] > 0) {
					this->caintitatiProduse[i] = cantitati[i];
				}
			}else{
			this->caintitatiProduse = 0;
		}
		strcpy(this->dataEveniment, data);
	}
	~FirmaCatering() {
		if (this->denumireClient != NULL)
		{
			delete[]this->denumireClient;
		} 
		if (this->caintitatiProduse != NULL) {
			delete[]this->caintitatiProduse;
		}
	}
	 char* getDenumire() {
		return this->denumireClient;
	}
	void setDenumire( char* denumireNoua) {
		this->denumireClient = denumireNoua;
	}

	float getPret() {
		return this->pret;
	}
	void setPret(float PretNou) {
		
		if(PretNou>0)
		this->pret = PretNou;
	}

	void setCantitati(int nrProduse, int* cantitati) {
	
		if (nrProduse > 0) {
			this->nrProduse = nrProduse;
			this->caintitatiProduse = new int[this->nrProduse];
			for (int i = 0; i < this->nrProduse; i++)
				if (cantitati[i] > 0) {
					this->caintitatiProduse[i] = cantitati[i];
				}
		}
		else {
			this->caintitatiProduse = 0;
		}
	}

	friend ostream& operator<<(ostream& out, FirmaCatering& f) {
		out << "denumire :" << f.denumireClient << ", pret comanda:  " << f.pret << ", produse :  " << f.nrProduse << ", plasata la data de " << f.dataEveniment << " si cu cantitatile de " << endl;
		for (int i = 0; i < f.nrProduse; i++) {
			out << f.caintitatiProduse[i] << endl;
		}
		return out;

	}
	
	FirmaCatering(const FirmaCatering& sursa) :idProdus(sursa.nrComenzi){
		
		this->denumireClient = new char[strlen(sursa.denumireClient)+1];
		strcpy(this->denumireClient, sursa.denumireClient);
		strcpy(this->dataEveniment, sursa.dataEveniment);
		this->pret = sursa.pret;
		this->nrProduse = sursa.nrProduse;
		this->caintitatiProduse = new int[sursa.nrProduse];
		for (int i = 0; i < sursa.nrProduse; i++) {
			this->caintitatiProduse[i] = sursa.caintitatiProduse[i];
		}


	}

	FirmaCatering operator=(const FirmaCatering& sursa) {

		if (this->denumireClient != NULL) {
			delete[]this->denumireClient;
		}
		if (this->caintitatiProduse != NULL) {
			delete[]this->caintitatiProduse;
		}

		this->denumireClient = new char[strlen(sursa.denumireClient) + 1];
		strcpy(this->denumireClient, sursa.denumireClient);
		strcpy(this->dataEveniment, sursa.dataEveniment);
		this->pret = sursa.pret;
		this->nrProduse = sursa.nrProduse;
		this->caintitatiProduse = new int[sursa.nrProduse];
		for (int i = 0; i < sursa.nrProduse; i++) {
			this->caintitatiProduse[i] = sursa.caintitatiProduse[i];
		}
		return *this;
	}

	int& operator[](int index) {

		if (index < 0 || index >= this->nrProduse) {
			cout << " index in afara limitelor"<<endl;

		}
		else {
			cout << "-----------------------------" << endl;
			return this->caintitatiProduse[index];
		}
	}
	//f1+=2;
	FirmaCatering& operator+=(int val) {

		int* vectorNou = new int[nrProduse + 1];
		for (int i = 0; i < this->nrProduse; i++) {
			vectorNou[i] = this->caintitatiProduse[i];
		}

		if (this->cantitatiProduse )
			delete[]this->caintitatiProduse;
		this->caintitatiProduse = vectorNou;
		this->nrProduse++;

		return *this;

	}
	//f2-1;
	FirmaCatering operator+(int pozitie) {
		
		FirmaCatering copie = *this;

		if (pozitie > 0 || pozitie < this->nrProduse) {
			int* vectorNou = new int[this->nrProduse + 1];
			int k = 0;
			for (int i = 0; i < this->nrProduse; i++) {
				if (i != pozitie) {
					vectorNou[k++] = copie.caintitatiProduse[i];
				}
			}
			delete[]copie.caintitatiProduse;
			copie.caintitatiProduse = vectorNou;
		}
		return copie;
		}
		//--f2;
	FirmaCatering& operator++() {

		if (this->nrProduse >= 0) {
			int* vectorNou;
			vectorNou = new int[this->nrProduse + 1];
			for (int i = 0; i < this->nrProduse + 1; i++) {
				vectorNou[i] = caintitatiProduse[i];
			}

			if(this->caintitatiProduse)
			 delete[]this->caintitatiProduse;


			vectorNou = caintitatiProduse;
			this->nrProduse++;
		}
		return *this;
	}


	friend ofstream& operator<<(ofstream& out, FirmaCatering& f) {
		
		out << f.denumireClient;
		out << f.dataEveniment;
		out << f.pret;
		out << f.nrProduse;
		for (int i = 0; i < f.nrProduse; i++) {
			out << f.caintitatiProduse;
		}
		return out;
	}
};

int FirmaCatering::nrComenzi = 0;

void main() {

	FirmaCatering f1;
	//f1.setDenumire("gigel ionescu");
	f1.setPret(100);
	FirmaCatering f2("ionescu marina", "22/02/2020/60", 100, 4, new int[] {2, 5, 4, 3});

	cout << f1;
	cout << f2;
	
	FirmaCatering f3(f2);
	//f3 += 1;
	//f3 + 1;
	++f1;
	cout << f3;
	//f1 = f2;
	cout<< f2[0];
	
	ofstream f("Text.txt");
	f << f2;
	f << f3;
	f << f1;
}