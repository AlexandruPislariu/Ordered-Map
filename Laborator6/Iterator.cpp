#include "Iterator.h"
#include "DO.h"
#include <exception>
using namespace std;

void Iterator::deplasare()
{/* Gaseste prima lista nevida incepand cu locatia poz */
	while (pozCurent < dict.m && dict.lista[pozCurent] == NULL)
		pozCurent++;

	if (pozCurent < dict.m)
		curent = dict.lista[pozCurent];
}

Iterator::Iterator(const DO& d) : dict(d) {
	/* de adaugat */
	pozCurent = 0;
	curent = NULL;
	deplasare();
}

void Iterator::prim() {
	/* de adaugat */
	pozCurent = 0;
	curent = NULL;
	deplasare();
}

void Iterator::urmator() {
	if(curent!=NULL)/* parcurg aceeasi linie */
		curent = curent->urmator;
	else
	{/* trec pe urmatoarea linie nevida */
		pozCurent++;
		deplasare();
	}
}

bool Iterator::valid() const {
	/* de adaugat */
	return (curent != NULL && pozCurent < dict.m);
}

TElem Iterator::element() const {
	/* de adaugat */
	if(valid())
		return curent->pair;
	return pair <TCheie, TValoare>(-1, -1);
}

