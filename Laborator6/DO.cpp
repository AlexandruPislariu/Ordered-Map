#include "Iterator.h"
#include "DO.h"
#include <iostream>

#include <exception>
using namespace std;

int hashCode(TCheie c) 
{
	return abs(c);
}

TCheie DO::dispersie(TCheie c) const
{
	return hashCode(c) % m;
}

DO::DO(Relatie r) {
/* COMPLEXITATE theta(m) */
	lungime = 0;
	m = 997;
	rel = r;
	for (int i = 0; i < m; i++)
		lista[i] = NULL;
}

//adauga o pereche (cheie, valoare) in dictionar
//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
//daca nu exista cheia, adauga perechea si returneaza null
TValoare DO::adauga(TCheie c, TValoare v) {
	/* 
	Probabilitatea ca o cheie sa se disperseze intr-una din liste este 1/m
		fie a=n/m, numarul mediu de chei din fiecare lista
	
	adaugare = cautare cu succes +  theta(1)

	Best Case: se disperseaza o cheie intr o locatie noua O(1)
	Worst Case: toate nodurile se disperseaza in aceeasi locatie, c trebuie adaugata la sfarsit O(a)
	Overall: in lista de pe pozitia i cheia poate fi adaugata dupa 1,2,...,a pasi, dar nu se mai trece la alte liste =>
			1/m*(1+2+...+a)/a = (1+a)/m apartine theta(1 + a/m) 

	*/

	lungime++;

/* Creez un nod nou */
	Nod* nou = new Nod;
	nou->pair = pair<TCheie, TValoare>(c, v);
	nou->urmator = NULL;

/* Setez iteratorul pe linia corespunzatoare din tabela */
	Iterator it = iterator();
	it.pozCurent = dispersie(c);
	it.curent = lista[dispersie(c)];

	if (!it.valid())
	{/* Cazul in care nu se afla elemente pe linie (initializare linie) */
		lista[dispersie(c)] = nou;
		lista[dispersie(c)]->urmator = NULL;
		return NULL_TVALOARE;
	}

/* Caut pozitia tinand cont ca dictionarul este ordonat */
	Nod* anterior = NULL;
	while (it.valid() && rel(it.element().first, c) && it.element().first!=c && it.pozCurent==dispersie(c))
	{
		anterior = it.curent;
		it.urmator();
	}

	if (it.element().first == c)
	{/* Nu trebuie adaugata pereche noua (cheia se afla in dictionar) */
		TValoare valVeche = it.element().second;
		it.curent->pair.second = v;

		lungime--;
		return valVeche;
	}

	if (anterior == NULL )
	{/* Adaugare la inceput */
		nou->urmator = it.curent;
		lista[dispersie(c)] = nou;
	}
	else
		if(it.pozCurent!=dispersie(c))
		/* Adaugare la sfarsit*/
			anterior->urmator = nou;
		else 
		{/* Adaugare intre 2 noduri*/
			anterior->urmator = nou;
			nou->urmator = it.curent;
		}

	return NULL_TVALOARE;
}

//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null
TValoare DO::cauta(TCheie c) const {
	/*  
		Probabilitatea ca o cheie sa se disperseze intr-una din liste este 1/m
		fi a=n/m, numarul mediu de chei din fiecare lista
		Cautare fara succes:
			cheia nu se afla in relatie cu capul listei -> O(1)
			in lista de pe pozitia i cheia poate fi gasita dupa 1,2,...,a pasi, se trece la alte liste => 
			1/m*(m*(1+2+...+a)/a) = a*(1+a)/a = 1+a apartine theta(1+a)
		Cautare cu succes:
			in lista de pe pozitia i cheia poate fi gasita dupa 1,2,...,a pasi, dar nu se mai trece la alte liste =>
			1/m*(1+2+...+a)/a = (1+a)/m apartine theta(1 + a/m) 
	*/ 

/* Setez iteratorul pe linia corespunzatoare din tabela*/
	Iterator it = iterator();
	it.pozCurent = dispersie(c);
	it.curent = lista[dispersie(c)];

/* Caut pozitia tinand cont ca dictionarul este ordonat */
	while (it.valid() && rel(it.element().first, c) && it.element().first!=c)
		it.urmator();

/* Exista cheia */
	if (it.valid() && it.element().first == c)
		return it.element().second;

	return NULL_TVALOARE;
}

//sterge o cheie si returneaza valoarea asociata (daca exista) sau null
TValoare DO::sterge(TCheie c) {
	/* 
		Probabilitatea ca o cheie sa se disperseze intr-una din liste este 1/m
		fie a=n/m, numarul mediu de chei din fiecare lista

		stergere = cautare cu succes + theta(1)

		Best Case: se afla la inceputul locatiei de dispersie O(1)
		Worst Case: se afla la sfarsitul locatiei de dispersie O(a)
		Overall: in lista de pe pozitia i cheia poate fi stearsa dupa 1,2,...,a pasi, dar nu se mai trece la alte liste =>
			1/m*(1+2+...+a)/a = (1+a)/m apartine theta(1 + a/m) 
	*/

/* Setez iteratorul pe linia corespunzatoare in tabela*/
	Iterator it = iterator();
	it.pozCurent = dispersie(c);
	it.curent = lista[dispersie(c)];

/* Nu se afla elemente pe linie */
	if (!it.valid())
		return NULL_TVALOARE;

/* Caut cheia tinand cont ca dictionarul este ordonat */
	Nod* anterior = NULL;
	while (it.valid() && rel(it.element().first, c) && it.element().first!=c && it.pozCurent==dispersie(c))
	{
		anterior = it.curent;
		it.urmator();
	}

	if (it.element().first == c)
	{/* Cheie gasita, se sterge*/
		TValoare val = it.element().second;
		if (anterior == NULL)/* se sterge de la inceput */
			lista[dispersie(c)] = it.curent->urmator;
		else
			anterior->urmator = it.curent->urmator;

		lungime--;
		return val;
	}

	return NULL_TVALOARE;
}

//returneaza numarul de perechi (cheie, valoare) din dictionar
int DO::dim() const {
	/* COMPLEXITATE theta(1) */
	return lungime;
}

//verifica daca dictionarul e vid
bool DO::vid() const {
	/* COMPLEXITATE theta(1) */
	if(lungime<=0)
		return true;
	return false;
}

Iterator DO::iterator() const {
	return  Iterator(*this);
}

void DO::goleste()
{/* Complexitate theta(a*m) */
	Iterator it = iterator();
	it.prim();
	while (it.valid())
	{
		Nod* p = it.curent;
		it.urmator();
		p->pair = pair<TCheie,TValoare>(NULL_TVALOARE,NULL_TVALOARE);
		p->urmator = NULL;
	}


	lungime = 0;
}

DO::~DO() {
	/* COMPLEXIATE theta(m*a) */

	for (int i = 0; i < m; i++)/* linie */
	{/* sterg nodurile de pe fiecare linie a tabelei */
		while (lista[i] != nullptr)
		{
			Nod* p = lista[i];
			lista[i] = lista[i]->urmator;
			delete p;
		}
	}
}