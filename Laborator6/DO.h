#pragma once

typedef int TCheie;
typedef int TValoare;

#define NULL_TVALOARE -1

#include <utility>
typedef std::pair<TCheie, TValoare> TElem;

class Iterator;

typedef bool(*Relatie)(TCheie, TCheie);

struct Nod
{
	TElem pair;
	Nod* urmator;
};

class DO {
	friend class Iterator;
private:
	/* aici e reprezentarea */
	int lungime;
	int m;/*pentru dispersie ( n ~ 3000 => m ~ 3000/3 = 1000, m prim => m = 997, 3 elemente in medie in coliziune )*/
	Relatie rel;
	Nod* lista[998];

	TCheie dispersie(TCheie c) const ;

public:

	// constructorul implicit al dictionarului
	DO(Relatie r);

	//elimina toate elementele din dictionar
	void goleste();

	// adauga o pereche (cheie, valoare) in dictionar
	//daca exista deja cheia in dictionar, inlocuieste valoarea asociata cheii si returneaza vechea valoare
	// daca nu exista cheia, adauga perechea si returneaza null: NULL_TVALOARE
	TValoare adauga(TCheie c, TValoare v);

	//cauta o cheie si returneaza valoarea asociata (daca dictionarul contine cheia) sau null: NULL_TVALOARE
	TValoare cauta(TCheie c) const;


	//sterge o cheie si returneaza valoarea asociata (daca exista) sau null: NULL_TVALOARE
	TValoare sterge(TCheie c);

	//returneaza numarul de perechi (cheie, valoare) din dictionar
	int dim() const;

	//verifica daca dictionarul e vid
	bool vid() const;

	// se returneaza iterator pe dictionar
	// iteratorul va returna perechile in ordine dupa relatia de ordine (pe cheie)
	Iterator iterator() const;


	// destructorul dictionarului
	~DO();

};