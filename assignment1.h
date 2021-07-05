#pragma once
#include <iostream>
#include <gtest\internal\gtest-string.h>
#include <gtest\internal\gtest-string.h>
using namespace std;
/*
Sa se implementeze functia withdraw ce accepta doi parametri:
- balance - reprezinta balanta contului curent
- amount - reprezinta suma pe care dorim sa o extragem din
cont
Functia trebuie sa respecte urmatoarele cerinte:
- La apelul functiei withdraw se va extrage din balanta suma
dorita
(Exemplu: In urma apelului withdraw(2000, 1000), balanta va
avea valoarea 1000)
- Daca balanta este negativa si se incearca efectuarea unei
tranzactii
se va aplica o penalizare de 10% asupra balantei, fara a
efectua tranzactia
(Exemplu: pentru o balanta de -1000, la incercarea efectuarii
unei tranzactii
balanta va avea valoarea de -1100).
- Daca suma pe care dorim sa o extragem este negativa, se va
efectua operatia de
depunere. (pentru o balanta de 1000, la apelul functiei cu un
amount de -200, vom
obtine balanta cu valoarae 1200)
- Daca suma dorita este mai mare decat valoarea balantei, nu
se va efectua nicio operatie
- Daca se va efectua operatia de withdraw cu amount 0, se va
aplica o penalizare de 5% asupra balantei
*/

void withdraw(double* balance, double amount) {

	
	if ((*balance) < 0) {
		*balance = *balance + (*balance) * 0.1;

	}
	else {
		if (amount < 0) {
			*balance = *balance - amount;
		}
		else if (amount > * balance) {
			cout << endl << "amount > balance";
		}

		else if (amount == 0) {
			*balance = 0.95 * (*balance);
		}
		else {
			*balance = *balance - amount;
		}
	}
}

	
/*
Aceeasi cerinta si pentru withdraw2
Same requirement for withdraw2
*/

void withdraw2(double& balance, double amount) {

	if (balance < 0) {
		balance = balance + 0.1 * balance;

	}
	else if (amount < 0) {
		balance = balance - amount;
	}
	else if (amount > balance) {
		
		cout << endl << "amount > balance";
	}
	else if (amount == 0) {
		balance = 0.95 * balance;
	}

	else {
		balance = balance - amount;
	}

	
}			


/*
Sa se implementeze metoda toTitleCase(char* text) care
transforma un text primit in formatul Title Case
- toate cuvintele incep cu majuscula
- ex: "salut. acesta este un test" devine "Salut. Acesta Este
Un Test"
*/


char* toTitleCase(char* text) {

	char* newText = new char[strlen(text) + 1];
	strcpy(newText, text);
	newText[0] = toupper(newText[0]);
	for (unsigned int i = 0; i < strlen(newText) - 1; i++)
	{
		if (newText[i] == ' ' && newText[i + 1] != ' ')
		{

			newText[i + 1] = toupper(newText[i + 1]);

			
		}
	}
	//return nullptr;
	return newText;
}

/*
Sa se implementeze metoda removeSpaces(char* text) care
elimina toate spatiile dintr-un text primit
- se iau in considerare toate spatiile (la inceput, la final
si in interior)
- ex: " salut. acesta este un test " devine
"salut.acestaesteuntest"
*/

char* removeSpaces(char* text) {

	char* newText = new char[strlen(text) + 1];
	strcpy(newText, text);
	*std::remove(newText, newText + strlen(newText), ' ') = 0;
	
	//return nullptr;
	return newText;
}


