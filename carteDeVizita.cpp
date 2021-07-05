//#include<iostream>
//#include<string>
//#include<fstream>
//
//using namespace std;
//class Card {
//private:
//	static int pretFabricatie;
//	char* tipMaterial;
//	int nrExemplare;
//	float costuri;
//public:
//	Card() {
//		this->tipMaterial = new char[strlen("MaterialDefault") + 1];
//		strcpy(this->tipMaterial, "MaterialDefault");
//		this->nrExemplare = 1;
//		this->pretFabricatie = 1;
//	}
//	Card(const char* tipMaterial,int nrExemplare,float costuri){
//		this->tipMaterial = new char[strlen(tipMaterial) + 1];
//		strcpy(this->tipMaterial, tipMaterial);
//		this->nrExemplare = nrExemplare;
//		this->costuri = costuri;
//	}
//	Card(const Card& c) {
//		this->tipMaterial = new char[strlen(c.tipMaterial) + 1];
//		strcpy(this->tipMaterial,c.tipMaterial);
//		this->nrExemplare = c.nrExemplare;
//		this->costuri = c.costuri;
//	}
//	Card& operator=(Card& c) {
//		if (this->tipMaterial) {
//			delete[]this->tipMaterial;
//}
//		this->tipMaterial = new char[strlen(c.tipMaterial) + 1];
//		strcpy(this->tipMaterial, c.tipMaterial);
//		this->nrExemplare = c.nrExemplare;
//		this->costuri = c.costuri;
//		return *this;
//	}
//	int getpretFab() {
//		return this->pretFabricatie;
//	}
//	char* getTipMaterial() {
//		return this->tipMaterial;
//	}
//	int getNrExemplare() {
//		return this->nrExemplare;
//	}
//	float getCosturi() {
//		return this->costuri;
//	}
//	friend ostream& operator<<(ostream& out, Card& c) {
//		
//		out << "Pret fabri: " << c.pretFabricatie << endl;
//		out << "Tip material: " << c.tipMaterial << endl;
//		out << "Nr Exemplare: " << c.nrExemplare<< endl;
//		out << "Costuri: " << c.costuri << endl;
//		return out;
//	}
//	bool operator>=(Card&c) {
//		if (this->costuri >= c.costuri) {
//			return true;
//		}
//		else {
//			return false;
//		}
//	}
//	void setTip(const char* tip) {
//		if (strlen(tip) > 2) {
//			this->tipMaterial = new char[strlen(tip) + 1];
//			strcpy(this->tipMaterial, tip);
//		}
//	}
//	friend istream& operator>>(istream& in, Card& c) {
//		
//		char buffer[25];
//		cout << "Tip: ";
//		in >> buffer;
//		c.setTip(buffer);
//		cout << "nr ex: ";
//		in >> c.nrExemplare;
//		cout << "costuri: ";
//		in >> c.costuri;
//		return in;
//	}
// virtual void afisare() {
//		cout << "card"<<endl;
//	}
//
//};
//class CartedeVizitaElectronica :public Card {
//private:
//	int memorieOcupata;
//public:
//	CartedeVizitaElectronica() :Card() {
//		this->memorieOcupata = 1;
//	}
//	CartedeVizitaElectronica(int memorieOcupata, const char* tipMaterial,int nrExemplare,float costuri) :Card(tipMaterial,nrExemplare,costuri) {
//		this->memorieOcupata = memorieOcupata;
//	}
//	CartedeVizitaElectronica(const CartedeVizitaElectronica& ce):Card(ce) {
//		this->memorieOcupata = ce.memorieOcupata;
//	}
//	CartedeVizitaElectronica& operator=(CartedeVizitaElectronica& ce) {
//		Card::operator=(ce);
//		this->memorieOcupata = ce.memorieOcupata;
//		return *this;
//
//	}
//	int getMemorie() {
//		return this->memorieOcupata;
//	}
//	void afisare() {
//		cout << *this;
//	}
//};
//int Card::pretFabricatie = 2;
//void main() {
//	Card c;
//	Card c2("plastic", 40, 2);
//	//cout << c2;
//	if (c >= c2) {
//		cout << "c are preturile cel putin eagel cu c2" << endl;
//	}
//	else {
//		cout << "c are costuri mai mici" << endl;
//	}
//	///cin >> c;
//	//cout << c;
//
//	CartedeVizitaElectronica ce1;
//
//	c.afisare();
//	ce1.afisare();
//}
//
