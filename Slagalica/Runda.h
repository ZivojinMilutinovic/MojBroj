#pragma once
class Runda
{
private:
	// indeksi od 0 do 5 predstavljaju brojeve koje korstimo
	// na ineksu 6 se nalazi trazeni broj
	int *brojevi;
	int brojRunde;
public:
	Runda(int *brojevi, int brojRunde);
	inline int GetTrazeniBroj() { return brojevi[6]; }
	inline int GetBrojRunde() { return brojRunde; }
	inline int* GetBrojevi() { return brojevi; }
};

