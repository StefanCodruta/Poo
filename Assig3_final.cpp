#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include <exception>
using namespace std;

class Assignment3Exception : public exception {

};


//clasa Card Fidelitate ce inregistreaza numarul de puncte castigate de client de fiecare data cand efectueaza o plata
class FidelityCard {
public:
	const int id;			//constant attribute - generated based on noCards value
private:
	char owner[50] = "";
	string cardType;		//the service that provides the card (ex. Rompetrol, Mega Image, etc)

	int* points = NULL;       //points accumulated each time the client buys something
	int noPayments = 0;			//number of pamyments done by the client

	static int noCards;		//incremented for each created card
public:
	const static int MIN_POINTS_FOR_PREMIUM = 1000;		//init with 1000 - the minimum points for becoming a premium member

public:
	/*


		//constructori

	*/

	// initializeaza numele cu John Doe si tipul cardului cu "None"
	FidelityCard() : id(noCards)
	{
		noCards += 1;
		cout << endl << "constructor implicit";
		strcpy(this->owner, "John Doe");
		this->cardType = "None";
		this->noPayments = 0;
		this->points = NULL;

	}
	FidelityCard(const char* name, string cardName) :id(noCards) {

		if (strlen(owner) <= 49) {
			strcpy(this->owner, name);
		}
		this->cardType = cardName;
		this->noPayments = 0;
		this->points = NULL;

		noCards++;

	}
	FidelityCard(const char* name, string cardName, int* existingPoints, int noPoints) :id(noCards++) {

		if (strlen(owner) <= 49) {
			strcpy(this->owner, name);
		}
		this->cardType = cardName;
		this->noPayments = noPoints;
		if (noPoints > 0 && existingPoints != NULL) {
			this->points = new int[noPayments];
			for (int i = 0; i < noPoints; i++)
				this->points[i] = existingPoints[i];

		}

	}

	//copy constructor
	//TO DO
	FidelityCard(const FidelityCard& c) :id(noCards) {

		this->cardType = c.cardType;
		this->noPayments = c.noPayments;
		if (c.points != NULL) {
			this->points = new int[this->noPayments];
			for (int i = 0; i < this->noPayments; i++)
				this->points[i] = c.points[i];



		}
		else this->points = NULL;
		strcpy(this->owner, c.owner);
		noCards++;
	}

	//destructor
	//TO DO
	~FidelityCard() {
		/*if (this->owner != nullptr)
			delete[] this->owner;*/
		if (points != NULL) {
			delete[] this->points;
		}
		if (this->noCards) {
			FidelityCard::noCards -= 1;
		}
	}

	/*


	//interfata publica

	*/


	//determina numarul total de puncte

	int getTotalPoints() {
		int total = 0;
		for (int i = 0; i < this->noPayments; i++)
		{
			total = total + points[i];
		}
		return total;
	}


	//returneaza numele de pe card

	char* getName() {
		return this->owner;
	}

	//returneaza numarul de puncte

	int getNoPayments() {
		return this->noPayments;
	}


	//returneaza punctele asociate cu o anumita plata
	//daca indexul primit este gresit (nu se afla intre limitele 0 si numarPuncte -1 ) atunci se arunca o exceptie de tip Assignment3Exception cu "throw new Assignment3Exception();"

	int getPayment(int index) {
		if (index >= 0 && index <= noPayments - 1) {

			return this->points[index];
		}
		else {
			throw new Assignment3Exception();
		}
	}

	//returneaza tipul cardului

	string getCardType() {
		return this->cardType;
	}


	//verifica daca clientul este unul premium - suma punctelor depaseste MIN_POINTS_FOR_PREMIUM

	bool isPremiumClient() {
		if (getTotalPoints() > MIN_POINTS_FOR_PREMIUM)
			return true;
		else
			return false;
	}


	//permite modificarea numarului de puncte de la o pozitie data
	//daca indexul primit este gresit (nu se afla intre limitele 0 si numarPuncte -1 ) si valoarea este negativa atunci se arunca o exceptie de tip Assignment3Exception cu "throw new Assignment3Exception();"

	void changePoints(int index, int value) {

		if (index <0 || index > this->noPayments - 1 || value < 0) {
			throw new Assignment3Exception();
		}
		else {
			this->points[index] = value;
		}
	}


	//permite modificarea numelui proprietarului
	//daca newOwnerName are mai putin de 3 caractere si mai mult de 49 se arunca o exceptie de tip Assignment3Exception cu "throw new Assignment3Exception();"
	void changeOwner(const char* newOwnerName) {
		if (strlen(newOwnerName) <= 3 || strlen(newOwnerName) >= 49) {
			throw new Assignment3Exception();

		}
		else {
			strcpy(this->owner, newOwnerName);
		}

	}


	//adauga (concateneaza) vectorul newPoints la cel existent; daca cel existent este NULL, atunci este creat si ia valorile
	//daca newPoints este NULL atunci arunca o exceptie Assignment3Exception
	//without | fara MEMORY LEAKS

	void transferPoints(int* newPoints, int noPoints)
	{
		if (newPoints == NULL) {
			throw new Assignment3Exception();
		}
		if (points != NULL) {

			int* temp = new int[noPayments];
			for (int i = 0; i < noPayments; i++) {
				temp[i] = points[i];
			}
			delete[] this->points;
			points = new int[noPayments + noPoints];

			for (int i = 0; i < noPayments; i++) {
				points[i] = temp[i];
			}
			int j = 0;
			for (int i = noPayments; i < noPayments + noPoints; i++) {
				points[i] = newPoints[j];
				j++;
			}
			noPayments += noPoints;
		}
		else {
			points = new int[noPoints];
			for (int i = 0; i < noPoints; i++) {
				points[i] = newPoints[i];

			}
			noPayments = noPoints;
		}



	}




	// functia permite clientilor sa utilizeze punctele pentru a cumpara servicii / produse noi 
	// functia va elimina primele n valori din vectorul de puncte, a caror suma este >= cu amount
	// daca amount este <= 0 sau > suma tuturor punctelor se arunca o exceptie Assignment3Exception
	void usePoints(int amount) {
		if (amount <= 0 || getTotalPoints() < amount) {
			throw new Assignment3Exception();

		}
		if (amount == getTotalPoints()) {
			delete[] points;
			points = NULL;
			noPayments = 0;
		}
		else {
			int* temp;
			int tot = 0, i = 0;
			for (i = 0; tot < amount; i++) {
				tot += points[i];
			}
			if (amount == tot) {
				temp = new int[noPayments - i];
				int j = 0;
				for (int k = i; k < noPayments; k++) {
					temp[j] = points[k];
					j++;
				}
				noPayments = noPayments - i;
			}
			else {
				temp = new int[noPayments - i + 1];
				temp[0] = tot - amount;
				int j = 1;
				for (int k = i; k < noPayments; k++) {
					temp[j] = points[k];
					j++;
				}
				noPayments = noPayments - i + 1;
			}
			delete[] this->points;
			points = temp;
		}
	}


	/*

		//operators
		//operatori

	*/

	//TO DO
	//implementeaza operatorii indicati in main ca functii membre in clasa sau functii globale, astfel incat exemplele din main vor rula
	FidelityCard& operator=(const FidelityCard& card) {
		this->cardType = card.cardType;
		if (this->points != NULL) {
			delete[] this->points;
		}
		this->noPayments = card.noPayments;
		if (this->noPayments) {
			this->points = new int[this->noPayments];
			for (int i = 0; i < this->noPayments; i++)
				this->points[i] = card.points[i];


		}
		else {
			this->points = NULL;
		}
		strcpy(this->owner, owner);

		return *this;

	}
	FidelityCard operator-(int nr) {
		FidelityCard copy = *this;
		int k = 0;
		for (int i = 0; i < copy.noPayments; i++) {
			if (copy.points[i] <= nr && nr > 0) {
				k++;
				nr -= copy.points[i];
			}
			else {
				copy.points[i] -= nr;
				nr = 0;
			}
		}
		int* v = new int[copy.noPayments - k];
		int j = 0;
		for (int i = k; i < copy.noPayments; i++) {
			v[j] = copy.points[i];
			j++;
		}
		delete[] copy.points;
		copy.noPayments -= k;
		copy.points = v;
		return copy;
	}


	FidelityCard& operator+=(int nr) {
		int* v = new int[noPayments + 1];
		for (int i = 0; i < noPayments; i++) {
			v[i] = points[i];
		}
		v[noPayments] = nr;
		noPayments++;
		delete[] points;
		points = v;
		return *this;
	}
	FidelityCard& operator-=(int nr) {
		int k = 0;
		for (int i = 0; i < noPayments; i++) {
			if (this->points[i] <= nr && nr > 0) {
				k++;
				nr -= points[i];
			}
			else {
				points[i] -= nr;
				nr = 0;
			}
		}
		int* v = new int[noPayments - k];
		int j = 0;
		for (int i = k; i < noPayments; i++) {
			v[j] = points[i];
			j++;
		}
		delete[] points;
		noPayments -= k;
		points = v;

		return *this;
	}
	bool operator!() {
		if (this->points != NULL) {
			return false;
		}
		else { return true; }
	}
	bool operator>(FidelityCard& f) {
		if (this->getTotalPoints() > f.getTotalPoints()) {
			return true;
		}
		return false;
	}
	bool operator<(FidelityCard& f) {
		if (this->getTotalPoints() < f.getTotalPoints()) {
			return true;
		}
		return false;
	}
	bool operator>=(FidelityCard& f) {
		if (this->getTotalPoints() >= f.getTotalPoints()) {
			return true;
		}
		return false;
	}
	FidelityCard& operator++() {
		int* v = new int[noPayments + 1];
		for (int i = 0; i < noPayments; i++) {
			v[i] = points[i];
		}
		v[noPayments] = 10;
		noPayments++;
		delete[] points;
		points = v;
		return *this;
	}
	FidelityCard operator++(int i) {
		FidelityCard copie = *this;
		int* v = new int[noPayments + 1];
		for (int i = 0; i < noPayments; i++) {
			v[i] = points[i];
		}
		v[noPayments] = 10;
		noPayments++;
		delete[] points;
		points = v;
		return copie;
	}
	FidelityCard& operator--() {
		int* v = new int[noPayments - 1];
		for (int i = 0; i < noPayments - 1; i++) {
			v[i] = points[i];
		}
		delete[] points;
		noPayments--;
		points = v;

		return *this;
	}

	FidelityCard operator--(int) {
		FidelityCard temp = *this;
		int* v = new int[noPayments - 1];
		for (int i = 0; i < noPayments - 1; i++) {
			v[i] = points[i];
		}
		delete[] points;
		noPayments--;
		points = v;
		return temp;
	}

	FidelityCard operator+(int newpoints) {
		FidelityCard copie = *this;
		int* v = new int[copie.noPayments + 1];
		for (int i = 0; i < copie.noPayments; i++) {
			v[i] = copie.points[i];
		}
		v[copie.noPayments] = newpoints;
		copie.noPayments++;
		delete[] copie.points;
		copie.points = v;
		return copie;
	}

	bool operator==(FidelityCard& c) {
		if (c.getTotalPoints() == this->getTotalPoints()) {
			return true;
		}
		else {
			return false;
		}
	}
	explicit operator int() {
		return this->getTotalPoints();
	}

	int& operator[](int index) {
		if (index < 0 || index <= this->getTotalPoints() || index < this->noPayments) {
			return this->points[index];

		}

	}
	/*FidelityCard& operator*(int nr) {
		points *= nr;
		return *this;

	}*/


	int partialSum(int index1, int index2) {
		int sumapart = 0;
		for (int i = index1; i <= index2; i++) {
			sumapart += points[i];
		}
		return sumapart;
	}
	friend ostream& operator<<(ostream& consola, FidelityCard& c);
	friend FidelityCard operator+(int newpoints, FidelityCard f);
	friend istream& operator >>(istream& in, FidelityCard& f);
};


ostream& operator<<(ostream& consola, FidelityCard& c) {
	consola << endl << "---------------------------";
	consola << endl << "Owner :" << c.getName();
	consola << endl << "Payments :" << c.getNoPayments();
	consola << endl << "Card type :" << c.getCardType();
	if (c.points != NULL) {
		cout << endl;
		for (int i = 0; i < c.getNoPayments(); i++) {
			consola << c.points[i] << ",";
		}
	}
	consola << endl << "Total points: " << c.getTotalPoints();

	return consola;
}
istream& operator >>(istream& in, FidelityCard& f) {
	cout << "owner ";
	in >> f.getName();

	/*cout << "payments";
	in >> f.getNoPayments();

	cout << "card type";
	in >> f.getCardType();*/

	for (int i = 0; i < f.getNoPayments(); i++) {
		cout << "puncte";
		in >> f.points[i];
	}
	return in;
}
FidelityCard operator+(int newpoints, FidelityCard f) {

	int* v = new int[f.noPayments + 1];
	for (int i = 0; i < f.noPayments; i++) {
		v[i] = f.points[i];
	}
	v[f.noPayments] = newpoints;
	f.noPayments++;
	delete[] f.points;
	f.points = v;
	return f;
}
int FidelityCard::noCards = 0;
//const int FidelityCard::MIN_POINTS_FOR_PREMIUM = 1000;

int main() {

	//test class functions

	int somePoints[] = { 15,5,10,30 };
	int noPoints = 4;
	FidelityCard card3("John", "ACME Inc", somePoints, noPoints);
	//cout << card3.getTotalPoints();
	//card3.changeOwner("ionica");
	//card3.changePoints(8,6);
   // card3.changePoints(2,6);
   // card3.transferPoints(somePoints,noPoints);
	//card3.usePoints(27);
	//card3.usePoints(15);
	//card3.usePoints(60);
	//cout << card3;

	//test destructor


	//operators section

	FidelityCard card1("No Name", "Blank");
	//FidelityCard card2 = card1;

	///*cout << card1;
	//cout << card2;
	//cin >> card1;
	//cout << card1;*/

	//int somePoints[] = { 15,5,10,30 };
	//int noPoints = 4;
	//FidelityCard card3("John", "ACME Inc", somePoints, noPoints);
	//FidelityCard card4 = card3;


	//operator =
	//without MEMORY LEAKS
	 //card2 = card1;		//copy data to card 1 from card 2 | copiaza datele cardului 1 in cardul 2
	 //cout << card2;


	card1 = card3 + 15;   //adds new points | adauga puncte noi
	//card1 = 20 + card1;   //adds new points | adauga puncte noi
	//card1 += 10;		  //adds new points | adauga puncte noi

	cout << card1;

	FidelityCard card5("No Name", "Blank");
	//card5 = card1 - 20;		//spends 20 points | utilizeaza 20 de puncte de pe card
	//card1 -= 10;			//spends 10 more points | utilizeaza inca 10 de puncte de pe card

	//card5 = card5 * 2;			//doubles all existing points | dubleaza toate punctele existente
	//cout << card5;

	FidelityCard card6("No Name", "Blank");

	////postincrement
	//card6 = card3++;		// adds 10 more points | adauga inca 10 puncte
	//cout << card6;
	//cout << card3;


	//////preincrement
	//card6 = ++card1;		// adds 10 more points | adauga inca 10 puncte
	//cout << card6;
	//cout << card3;

	//////postdecrement
	//card6 = card3--;		// removes the last entr in the points array
	//cout << card6;
	//cout << card3;


	//////*predecrement
	//card6 = --card1;		// removes the last entry in the points array
	//cout << card6;
	//cout << card3;


	//if (card6 > card2) {
	//	cout << endl << card6.getName() << " has more points than " << card2.getName();
	//}

	//if (card6 < card2) {
	//	cout << endl << card6.getName() << " has less points than " << card2.getName();
	//}

	/*if (card6 == card2) {
		cout << endl << card6.getName() << " has the same amount of points as " << card2.getName();
	}*/

	/*if (card6 >= card2) {
		cout << endl << card6.getName() << " has more or equal points than " << card2.getName();
	}*/


	//explicit cast
	//int totalPoints = (int)card3;		//get total points on the card | determina numarul total de puncte


	//int somePoints = card3[1];			//returns the number of points from the array on index 1 | intorce numarul de puncte de pe pozitia 1 din vectorul de puncte
	//card3[0] = 25;						//allows you to change the points value at index 0 in the array | iti permite sa modifici numarul de puncte de la index 0 in vectorul de puncte					
	//cout << card3;

	//int partialSum = card3(1, 3);			//determines the sum of points from index 1 to 3 (including 3) | determina numarul de puncte de la indexul 1 pana la 3 (inclusiv)
	//cout << endl << card3.partialSum(1, 3);

	//card6 = !card3;						//returns a copy of card with 0 points | returneaza o copie a cardului 3 fara a pastra punctele


}