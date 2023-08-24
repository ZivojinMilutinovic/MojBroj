#pragma once
#include <vector>
#include "Runda.h"
#include <string>
using namespace std;
class Igra
{
private:
	vector<Runda> niz_rundi;
	int brojPobedaIgracaA = 0;
	int brojPobedaIgracaB = 0;
	string naziv_fajla;
	void ucitajRunde();
	bool validanIzraz(string izraz, int* brojevi_runde);
	bool validneZagrade(string izraz);
	bool validniZnaci(string izraz);
	bool proveraBrojeva(string izraz, int* brojevi_runde);
	string potraziUnosIgraca(string igrac, int* brojevi_runde);
	int precedence(char op);
	int applyOp(int a, int b, char op);
	void unos(string igrac, int* brojevi_runde, ofstream &output_file, int trazeniBroj);
	void dfs(vector<int> brojevi, int trazenibroj, int trenutnaVrednost, string trenutniIzraz, string &resenje, int &najblizaRazlika, bool &nadjen);
	bool karakter_je_znak(char ch);
	string postavi_zagrade(string izraz);
public:
	Igra(char* naziv_fajla);
	Igra();
	void igraj();
	string computer_racuna(vector<int> brojevi_runde, int trazeniBroj);
	int izracunajIzraz(string izraz);
};

