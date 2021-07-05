#include<iostream>
#include <exception>
#pragma once
#include<sstream>

using namespace std;

// do not remove or change
class ExceptieAssignment2 : public std::exception {


};

/*
input
- un vector de numere intregi
- dimensiunea vectorului
- o valoare data
return
- numarul de elemente din vector ce sunt mai mari sau egale cu valoarea data
*/



int numarElementeMaiMari(int* valori, int nrValori, int valoarePrag) {

	int rezultat = 0;


	for (int i = 0; i < nrValori; i++) {
		if (valori[i] >= valoarePrag)
			rezultat++;
	}

	//return -1;
	return rezultat;
}

/*
Functia extrage dintr-un vector dat toate elementele ce sunt mai mari sau egale cu o valoare prag data

input
- un vector de numere intregi
- dimensiunea vectorului
- o valoare data
return
- un vector nou (creat in HEAP) ce contine toate elementele mai mari sau egale cu valoarea prag
- nullptr daca in vectorul initial nu exista elemente mai mari sau egale
*/


int* filtrareElementeMaiMari(int* valori, int nrValori, int valoarePrag) {

	int rezultat = numarElementeMaiMari(valori, nrValori, valoarePrag);
	//int rezultat = filtrareElementeMaiMari(valori, nrValori, valoarePrag);
	if (rezultat == 0) {
		return nullptr;
	}
	else if (rezultat > 0) {
		int* vectorNou = new int[rezultat];
		int j = 0;
		for (int i = 0; i < nrValori; i++) {
			if (valori[i] >= valoarePrag) {
				vectorNou[j] = valori[i];
				j++;

			}

		}
		return vectorNou;
	}


}


/*
Functia extrage dintr-un vector dat toate elementele ce sunt mai mari sau egale cu o valoare prag data

input
- un vector de numere intregi
- dimensiunea vectorului
- o valoare data
return
- un vector nou ce contine toate elementele mai mari sau egale cu valoarea prag; pointerul catre noul vector este primit in lista de argumente
- nullptr daca in vectorul initial nu exista elemente mai mari sau egale
*/


void filtrareElementeMaiMari2(int* valori, int nrValori, int valoarePrag, int** valoriMaiMari) {

	//int rezultat = numarElementeMaiMari(valori, nrValori, valoarePrag);
	*valoriMaiMari = nullptr;
	int rezultat = numarElementeMaiMari(valori, nrValori, valoarePrag);

	if (rezultat > 0) {
		*valoriMaiMari = new int[rezultat];
		int j = 0;
		for (int i = 0; i < nrValori; i++) {
			if (valori[i] >= valoarePrag) {
				(*valoriMaiMari)[j] = valori[i];
				j++;

			}

		}

	}

}

/*
Functia extrage elementul de pe pozitia index

input
- un vector de numere intregi
- dimensiunea vectorului
- indexul elementului (valoare pentru index trebuie sa fie validata)
- daca valoarea pentru index nu este ok atunci se arunca o exceptie de tip
		ExceptieAssignment2 cu "throw ExceptieAssignment2()"
return
- elementul de pe pozitia index
- exceptie daca indexul nu este valid
*/


int getElement(int* valori, int nrValori, int index)
{
	if (index < 0 || index >= nrValori) {
		throw ExceptieAssignment2();
	}
	else {

		return valori[index];

	}
}


/*
Functia extrage un subvector din vectorul primit - [index_start, index_final]

input
- un vector de numere intregi
- dimensiunea vectorului
- index start si index final
- daca valoarea pentru oricare index nu este ok atunci se arunca o exceptie de tip ExceptieAssignment2 cu "throw ExceptieAssignment2()"
- daca index start este egal cu index final atunci se returneaza un sub-vector ce contine elementul de pe pozitia index start
- daca index start este mai mare decat index final atunci se arunca o exceptie de tip ExceptieAssignment2
return
- un vector nou
- dimensiunea vectorului nou este returnata prin referinta dimensiuneSubvector din lista de argumente
- exceptie daca indexul nu este valid
*/


int* slice(int* valori, int nrValori, int indexStart, int indexFinal, int& dimensiuneSubvector) {

	int* vectornou = nullptr;
	//dimensiuneSubvector = 0;

	if (indexStart < 0 || indexStart >= nrValori || indexFinal < 0 || indexFinal >= nrValori || indexStart>indexFinal) {
		throw ExceptieAssignment2();;
	}
	else if (indexStart == indexFinal) {

		dimensiuneSubvector = 1;
		vectornou = new int[dimensiuneSubvector];
		vectornou[0] = valori[indexStart];
	}
	else {

		dimensiuneSubvector = indexFinal - indexStart + 1;
		vectornou = new int[dimensiuneSubvector];
		int j = 0;
		for (int i = indexStart; i <= indexFinal; i++) {
			vectornou[j] = valori[i];
			j++;
		}
	}
	return vectornou;
}