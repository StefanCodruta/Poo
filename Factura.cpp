#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <list>
using namespace std;

class Factura {
private:
    const int idProdus;
    string data;
    float pretUnitar;
    int cantitate;
protected:
    string denumire;
public:
    static int  nrFacturi;

    Factura() :idProdus(nrFacturi) {
        data = "";
        pretUnitar = 0;
        denumire = "";
        cantitate = 0;
        nrFacturi++;
    }

    Factura(string den, string d, float pret, int can) :idProdus(nrFacturi) {
        if (den != "" && d != "" && pret > 0 && can > 0) {
            denumire = den;
            data = d;
            pretUnitar = pret;
            cantitate = can;
            nrFacturi++;
        }
        else {
            data = "";
            pretUnitar = 0;
            denumire = "";
            cantitate = 0;
            nrFacturi++;
            cout << "Unul din parametrii nu este bun";
        }

    }

    Factura(const Factura & f):idProdus(nrFacturi) {
        denumire = f.denumire;
        data = f.data;
        pretUnitar = f.pretUnitar;
        cantitate = f.cantitate;
        nrFacturi++;
    }

    ~Factura() {
        cout << endl << "Destructor factura";
    }
    

    friend ostream& operator <<(ostream&, Factura&);

    Factura& operator =(const Factura& f) {
        if (this == &f) {
            return *this;
        }
        else {
            denumire = f.denumire;
            data = f.data;
            pretUnitar = f.pretUnitar;
            cantitate = f.cantitate;
        }
        return *this;
    }

    bool operator < (const Factura& f) {
        if (this->pretUnitar * this->cantitate < f.cantitate * f.pretUnitar) {
            return true;
        }
        else {
            return false;
        }
    }

    Factura& operator + (unsigned i) {
        this->pretUnitar += i;
        return *this;
    }

    Factura& operator -(unsigned i) {
        if (this->pretUnitar - i > 0) {
            this->pretUnitar -= i;
            return *this;
        }
    }
    
    //setteri
    void set_pret(float pret) {
        if (pret > 0) {
            this->pretUnitar = pret;
        }
        else {
            cout <<endl<< "Pretul nu poate fi 0 sau negativ";
        }
    }
    void set_cantitate(int cantitate) {
        if (cantitate > 0) {
            this->cantitate = cantitate;
        }
        else {
            cout << endl << "Cantitatea nu poate fi 0 sau negativa";
        }
    }

    void set_denumire(string d) {
        if (d == "") {
            cout << endl << "Denumirea nu poate fi nula";
            exit(0);
        }
        else {
            denumire = d;
        }
    }

    void set_data(string d) {
        if (d == "") {
            cout << endl << "Data nu poate fi nula";
            exit(0);
        }
        else {
            data = d;
        }
    }

    //getteri

    float get_Pret() {
        return pretUnitar;
    }

    int get_cantitate() {
        return cantitate;
    }

    float valoare() {
        return pretUnitar * cantitate;
    }

    string  spune_luna() {
        return data.substr(3,2);
    }

    //declarea friend pentru citirea si scriearea in fisier
    friend ofstream& operator  <<(ofstream&, Factura&);
    friend ifstream& operator  >>(ifstream&, Factura&);
    
};

ofstream& operator <<(ofstream& fout, Factura& f) {
    if (fout.is_open()) {
        fout << f.denumire<<endl;
        fout << f.data<<endl;
        fout << f.cantitate<<endl;
        fout << f.pretUnitar<<endl;
    }
    return fout;
}

ifstream& operator >>(ifstream& fin, Factura& f) {
    char n[30];   fin.getline(n, 30);  f.set_denumire(n);

    char d[30];   fin.getline(d, 30);  f.set_data(d);

    int cant;     fin >> cant;   f.set_cantitate(cant);
    int p;  fin >> p; f.set_pret(p);

    fin.get();
    return fin;
}

ostream& operator <<(ostream& out, Factura& f) {
    out << endl;
    out << "Factura este emisa pentru produsul cu codul: " << f.idProdus << " cu denumirea " << f.denumire << " emisa la data " << f.data<<".";
    out <<endl<< "Acesta are un pret unitar de " << f.pretUnitar << " si s-a vandut in catitate de " << f.cantitate<<" unitati.";
    out << endl;
    return out;
}

int Factura::nrFacturi = 0;

class GeestionareFacturi {
    Factura** facturi ;
    int nr;
public:

    GeestionareFacturi() {
        facturi = NULL;
        nr = 0;
    }

    GeestionareFacturi(const  GeestionareFacturi& g) {
        if (g.nr == 0) {
            this->facturi = NULL;
            this->nr = 0;
        }
        else {
            this->nr = g.nr;
            this->facturi = new Factura * [g.nr];
            for (int i = 0; i < g.nr; i++) {
                this->facturi[i] = g.facturi[i];
            }
        }
    }

    GeestionareFacturi & operator =(const GeestionareFacturi & g) {
        if (this == &g) {
            return *this;
        }
        if (this->facturi != NULL) {
            delete[] this->facturi;
        }
        if (g.nr > 0) {
            this->facturi = new Factura* [g.nr];
        }
        for (int i = 0; i < g.nr; i++) {
            this->facturi[i] = g.facturi[i];
        }
        return *this;
       
    }

     


    GeestionareFacturi& operator +(  Factura &f) {
        GeestionareFacturi rezultat = *this;
        Factura** temp = new Factura*[nr + 1];
        for (int i = 0; i < nr; i++) {
            temp[i] = facturi[i];
        }
       // Factura copy = f;
        temp[nr] = &f;
        rezultat.nr = this->nr + 1;
        rezultat.facturi = temp;
     //   return *this;
        return rezultat;
    }

    

   

    int get_Nr() {
        return nr;
    }

    Factura & operator [](unsigned index) {
        if (index >= nr) {
            cout << "Index inafara parametrilor";
            exit(0);
        }
        else {
            return *facturi[index];
        }

    }

    int  operator()(float criteriu) {
        int k = 0;
        for (int i = 0; i < nr; i++) {
            if (facturi[i]->valoare() > criteriu) {
                k++;
            }
        }
        return k;
    }

    ~GeestionareFacturi() {
        if (facturi != NULL) {
            delete[] facturi;
            cout << "facturi nu a fost NULL";
        }
        cout << endl << "Destructor Gestionare Facturi!";
    }
};

//class Gestiune {
//public:
//    Factura* facturi=NULL;
//    int nr=0;
//
//    Gestiune() {
//
//    }
//
//    Gestiune(const Gestiune& g) {
//        if (g.nr == 0) {
//            facturi = NULL;
//            nr = 0;
//        }
//        else {
//            nr = g.nr;
//            facturi = new Factura[nr];
//            for (int i = 0; i < nr; i++) {
//                facturi[i] = g.facturi[i];
//            }
//        }
//    }
//
//    Gestiune& operator =(const Gestiune& g) {
//        if (this == &g) {
//            return *this;
//        }
//        else {
//            if (g.nr == 0) {
//                nr = 0;
//                facturi = g.facturi;
//                return *this;
//            }
//            else {
//                if (facturi != NULL) {
//                    delete[] facturi;
//                }
//                nr = g.nr;
//                facturi = new Factura[g.nr];
//                for (int i = 0; i < nr; i++) {
//                    facturi[i] = g.facturi[i];
//                }
//                return *this;
//            }
//        }
//    }
//    Gestiune& operator +(const Factura& f) {
//        Gestiune  aux = *this;
//        Factura* temp = new Factura[this->nr];
//        for (int i = 0; i < this->nr; i++) {
//            temp[i] = this->facturi[i];
//        }
//        Factura copy = f;
//        temp[this->nr] = copy;
//        aux.nr = this->nr + 1;
//        aux.facturi = temp;
//
//        return aux;
//    }
//};

int main()
{
    {
        Factura f1;
        Factura f2("Malai", "20.12.2020", 2, 200);
        Factura f3 = f2;
        Factura f4;
        f4 = f2;
        Factura f5("Faina", "12.10.2019", 4, 500);
        Factura f6("Ovaz", "13.12.2018", 5, 100);
        cout << f4;

        //operatori 
        //<
        if (f2 < f5) {
            cout << endl << "Malaiul a valoarat mai multe decat faiana";
        }
        else {
            cout << endl << "Faina a valoarat mai multe decat malaiul";
        }

        f2 = f2 + 10;
        f2 = f2 - 5;
        cout << f2;

        cout << endl << "Factura a fost emisa in luna a " << f2.spune_luna() << "-a";
      /*  string luna = f2.spune_luna();
        int luna_intreg = std::atoi(luna.c_str()); cout << endl << luna_intreg;*/

        //Clasa colectie
        GeestionareFacturi facturi;
        facturi = facturi + f2;
        facturi = facturi + f5;
        facturi = facturi + f6;

        /*Gestiune g;
        g = g + f2;
        g = g + f5;*/


        cout << endl << "--------------------------Afisare Gestionare facturi-------------------------" << endl;
         for (int i = 0; i < facturi.get_Nr(); i++) {
             cout << facturi[i];
             cout << endl;
         }

         cout << endl << "Facturile care depasesc valoarea 100 sunt in numar de ";
         /*int k = facturi(100);
         cout << k;*/

         cout << endl << " ---------------------Scriere si citire din fisier text------------------------------" << endl;
         //scriere in fisier txt
         ofstream fout;
         fout.open("Factura.txt");
         fout << f2;
         fout.close();

         //citire din fisier txt
         ifstream fin;
         Factura f12;
         fin.open("Factura.txt");
         fin >> f12;
         fin.close();
         cout << endl << "-----Obicetul citit din fisier este:------ ";
         cout << f12;
         
         cout << endl << "------------------------------------STL--------------------------------";
         list<Factura> lista_facturi;
         lista_facturi.push_back(f2);
         lista_facturi.push_back(f5);
         lista_facturi.push_back(f6);
    }
   
}

