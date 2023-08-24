#include "Igra.h"
#include "FileReader.h"
#include <stack>
#include <unordered_map>
#include <cstdlib>
#include <queue>
#include <bitset>
#include <algorithm>


void Igra::ucitajRunde()
{
	FileReader fileReader(naziv_fajla);
	fileReader.readFromFile(this->niz_rundi);
}

int Igra::izracunajIzraz(string izraz)
{
	int i;
	stack <int> values;
	stack <char> ops;
	for ( i=0; i < izraz.length(); i++) {
		if (izraz[i] == '(') {
			ops.push(izraz[i]);
		}
		else if (isdigit(izraz[i])) {
			int val = 0;
			while (i < izraz.length() && isdigit(izraz[i])) {
				val = val * 10 + (izraz[i] - '0');
				i++;
			}
			values.push(val);
			i--;
		}
		else if (izraz[i] == ')') {
			while (!ops.empty() && ops.top() != '(') {
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}
			if (!ops.empty())
				ops.pop();
		}
		//operator je stigao
		else {
			while (!ops.empty() && precedence(ops.top())
				>= precedence(izraz[i])) {
				int val2 = values.top();
				values.pop();

				int val1 = values.top();
				values.pop();

				char op = ops.top();
				ops.pop();

				values.push(applyOp(val1, val2, op));
			}
			ops.push(izraz[i]);
		}
	}
	while (!ops.empty()) {
		int val2 = values.top();
		values.pop();

		int val1 = values.top();
		values.pop();

		char op = ops.top();
		ops.pop();

		values.push(applyOp(val1, val2, op));
	}

	return values.top();
}

bool Igra::validanIzraz(string izraz, int* brojevi_runde)
{
	return validniZnaci(izraz) && validneZagrade(izraz) && proveraBrojeva(izraz, brojevi_runde);
}

bool Igra::validneZagrade(string izraz)
{
	int brojac = 0;
	for (int i = 0; i < izraz.length(); i++) {
		if (izraz[i] == '(') {
			brojac++;
		}
		else if (izraz[i] == ')') {
			if (brojac == 0) return false;
			brojac--;
		}
	}
	//cout << "Brojac zagrada" << brojac;
	return brojac == 0;
}

bool Igra::validniZnaci(string izraz)
{
	bool ocekujemoBroj = true;
	int i;
	for (i = 0; i < izraz.length(); i++) {
		if (izraz[i] == '(' || izraz[i] == ')') continue;
		else if (isdigit(izraz[i])) {
			// broj mozda ima vise cifara
			while (i < izraz.length() && isdigit(izraz[i])) i++;
			// zavrsili smo trazenje broja
			ocekujemoBroj = false;
			// vracamo se unazad posto for petlja povecava i
			i--;
		}
		else if (izraz[i] == '+' || izraz[i] == '-' || izraz[i] == '*' || izraz[i] == '/') {
			//ocekujemo broj a dobili smo znak
			if (ocekujemoBroj) {
				return false;
			}
			else {
				//ocekujemo znak sve ok
				ocekujemoBroj = true;
			}
		}
		//nije broj, zagrada ili operator
		else return false;
	}
	return true;
}

// U izrazu mogu da se nadju samo brojevi od ponudjenih brojeva
// broejvi_runde sadrze brojeve ucitane iz fajla
bool Igra::proveraBrojeva(string izraz, int* brojevi_runde)
{
	// koristimo mapu jer moze da se desi da se neki jednocifreni broj javlja 2 puta
	// kljuc u mapi predstavlja broj ,a vrednost je koliko se puta taj broj javio
	unordered_map<int,int> brojevi;
	int i;
	for (i = 0; i < izraz.length(); i++) {
		if (isdigit(izraz[i])) {
			string pom = "";
			// izvlacimo broj iz stringa
			while (i < izraz.length() && isdigit(izraz[i])) {
				pom += izraz[i];
				i++;
			}
			int broj = stoi(pom);
			if (brojevi.find(broj) == brojevi.end()) {
				brojevi[broj] = 1;
			}
			else {
				brojevi[broj] = brojevi[broj] + 1;
			}
		}
	}
	for (i = 0; i < 6; i++) {
		if (brojevi.find(brojevi_runde[i]) == brojevi.end() || brojevi[brojevi_runde[i]]==0) {
			//nismo pronasli kljuc u mapi znaci igrac je uneo nevalidan broj ili nema vise bojeva tu
			return false;
		}
		else {
			brojevi[brojevi_runde[i]] = brojevi[brojevi_runde[i]] - 1;
		}
	}
	return true;
}

string Igra::potraziUnosIgraca(string igrac, int* brojevi_runde)
{
	string unos_igraca;
	cout << "Igrac " << igrac<< " je na potezu, molimo unesite izraz\n";
	cin >> unos_igraca;
	while (!validanIzraz(unos_igraca, brojevi_runde)) {
		cout << "Uneli ste neispravan izraz pokusajte molim va ponovo";
		cin >> unos_igraca;
	}
	return unos_igraca;
}

int Igra::precedence(char op)
{
	if (op == '+' || op == '-')
		return 1;
	if (op == '*' || op == '/')
		return 2;
	return 0;
}

int Igra::applyOp(int a, int b, char op)
{
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	}
}

void Igra::unos(string igrac, int* brojevi_runde, ofstream& output_file, int trazeniBroj)
{
	string unos_igraca = potraziUnosIgraca(igrac, brojevi_runde);
	int rezultat = izracunajIzraz(unos_igraca);
	output_file << "Igrac " << igrac << " je dobio:" << rezultat << endl;
	if (rezultat == trazeniBroj) {
		output_file << "Igrac " << igrac << " je pogodio rezultat" << endl;
		if (igrac == "A") {
			brojPobedaIgracaA++;
			output_file << "Igrac A je osvojio rundu i pogodio broj" << endl;
		}
		else {
			brojPobedaIgracaB++;
			output_file << "Igrac B je osvojio rundu i pogodio broj" << endl;
		} 
	}
	else {
		// ograc koji je prvi igrao nije pogodio broj
		int razlikaPrvog = abs(trazeniBroj - rezultat);
		
		output_file << "Igrac " << igrac << " odstupa od rezultata za:" << razlikaPrvog << endl;
		string igrac2 = igrac == "A" ? "B" : "A";
		string unos_igraca2 = potraziUnosIgraca(igrac2, brojevi_runde);
		int rezultat2 = izracunajIzraz(unos_igraca2);
		output_file << " Drugi igrac " << igrac2 << " je dobio:" << rezultat2 << endl;
		int razlikaDrugog = abs(trazeniBroj - rezultat2);
		output_file << " Drugi igrac " << igrac2 << " odstupa od rezultata" << razlikaDrugog << endl;
		if (razlikaPrvog == razlikaDrugog || razlikaPrvog < razlikaDrugog) {
			igrac == "A" ? ++brojPobedaIgracaA : ++brojPobedaIgracaB;
			output_file << "Blizi je bio i osvojio rundu igrac " << igrac << endl;
		}
		else {
			igrac2 == "A" ? ++brojPobedaIgracaA : ++brojPobedaIgracaB;
			output_file << "Blizi je bio i osvojio rundu igrac " << igrac2 << endl;
		}
	}
	vector<int> brojevi;
	for (int i = 0; i < 6; i++) brojevi.push_back(brojevi_runde[i]);
	output_file << "Kompjuter je dobio izraz: " << computer_racuna(brojevi, trazeniBroj) << endl;
}

void Igra::dfs(vector<int> brojevi, int trazenibroj, int trenutnaVrednost, string trenutniIzraz,  string& resenje, int &najblizaRazlika, bool &nadjen)
{
	if (nadjen) return;
	vector<char> operations = { '+','-','*','/' };
	for (int i = 0; i < brojevi.size(); i++) {
		vector<int> pom_brojevi = brojevi;
		int trenutniBroj = brojevi[i];
		pom_brojevi.erase(pom_brojevi.begin() + i);
		for (char op : operations) {
			
			if (op == '+') {
				int val = trenutnaVrednost;
				val += trenutniBroj;
				string noviIzraz = trenutniIzraz + "+" + to_string(trenutniBroj);
				int trenutnaRazlika = abs(trazenibroj - val);
				if (trenutnaRazlika < najblizaRazlika && !nadjen) {
					najblizaRazlika = trenutnaRazlika;
					resenje = noviIzraz + "X";
				}
				if (val == trazenibroj) {
					resenje = noviIzraz;
					nadjen = true;
					break;
				}
				dfs(pom_brojevi, trazenibroj, val, noviIzraz,  resenje, najblizaRazlika, nadjen);
			}
			else if (op == '-') {
				int val = trenutnaVrednost;
				val -= trenutniBroj;
				if (val < 0) continue;
				string noviIzraz = trenutniIzraz + "-" + to_string(trenutniBroj);
				int trenutnaRazlika = abs(trazenibroj - val);
				if (trenutnaRazlika < najblizaRazlika && !nadjen) {
					najblizaRazlika = trenutnaRazlika;
					resenje = noviIzraz + "X";
				}
				if (val == trazenibroj) {
					resenje = noviIzraz;
					nadjen = true;
					break;
				}
				dfs(pom_brojevi, trazenibroj, val, noviIzraz,  resenje, najblizaRazlika, nadjen);
			}
			else if (op == '*') {
				int val = trenutnaVrednost;
				val *= trenutniBroj;
				string noviIzraz = trenutniIzraz + "*" + to_string(trenutniBroj);
				int trenutnaRazlika = abs(trazenibroj - val);
				if (trenutnaRazlika < najblizaRazlika && !nadjen) {
					najblizaRazlika = trenutnaRazlika;
					resenje = noviIzraz + "X";
				}
				if (val == trazenibroj) {
					resenje =  noviIzraz;
					nadjen = true;
					break;
				}
				dfs(pom_brojevi, trazenibroj, val, noviIzraz,  resenje, najblizaRazlika, nadjen);
			}
			else if (op == '/') {
				int val = trenutnaVrednost;
				// moramo za deljenje da proverimo i inverznu kombinaciju
				// npr ako imamo brojeve 1 1 1 8 10 10->400 8/(1+1)*10*10
				string noviIzraz;
				if (val > 0 && trenutniBroj % val == 0) {
					val = trenutniBroj / val;
					noviIzraz = to_string(trenutniBroj) + "/" + "(" + trenutniIzraz + ")";
				}
				else if (trenutniBroj > 0 && val % trenutniBroj == 0) {
					 val /= trenutniBroj;
					 noviIzraz = trenutniIzraz + "/" + to_string(trenutniBroj);
				}
				else continue;
				int trenutnaRazlika = abs(trazenibroj - val);
				if (trenutnaRazlika < najblizaRazlika && !nadjen) {
					najblizaRazlika = trenutnaRazlika;
					resenje = noviIzraz + "X";
				}
				if (val == trazenibroj) {
					resenje =  noviIzraz;
					nadjen = true;
					break;
				}
				dfs(pom_brojevi, trazenibroj, val, noviIzraz,  resenje, najblizaRazlika, nadjen);
			}
		}
		if (nadjen) break;
	}
}

bool Igra::karakter_je_znak(char ch)
{
	return ch == '+' || ch == '-' || ch == '*' || ch == '/';
}

string Igra::postavi_zagrade(string izraz)
{
	string novi_izraz = "";
	int i = 0;
	bool znak_vidjen = false;
	while (i < izraz.length() && (!karakter_je_znak(izraz[i]) || !znak_vidjen)) {
		novi_izraz += izraz[i];
		if (karakter_je_znak(izraz[i])) znak_vidjen = true;
		i++;
	}
	for (; i < izraz.length(); i++) {
		if (izraz[i] == '*' || izraz[i] == '/') novi_izraz = "(" + novi_izraz + ")";
		novi_izraz += izraz[i];
	}
	return novi_izraz;
}

string Igra::computer_racuna(vector<int> brojevi_runde, int trazeniBroj)
{
	string resenje = "X";
	int najblizaRazlika = 100000;
	bool nadjen = false;
	for (int i = 0; i < brojevi_runde.size(); i++) {
		vector<int> pom_brojevi = brojevi_runde;
		int trenutniBroj = brojevi_runde[i];
		pom_brojevi.erase(pom_brojevi.begin() + i);
		dfs(pom_brojevi, trazeniBroj, trenutniBroj, to_string(trenutniBroj), resenje, najblizaRazlika, nadjen);
		if (resenje.back() != 'X') break;
	}
	if (resenje.back() == 'X') resenje.pop_back();
	return postavi_zagrade(resenje);
}

Igra::Igra(char* naziv_fajla)
{
	this->naziv_fajla = naziv_fajla;
}

Igra::Igra()
{
	naziv_fajla = "";
}

void Igra::igraj()
{
	ucitajRunde();
	ofstream output_file;
	output_file.open("Rezultati.txt");
	for (Runda runda : this->niz_rundi) {
		output_file << "-------------- TRENUTNI BROJ RUNDE =" << runda.GetBrojRunde() << "--------------"<<endl;
		int trazeniBroj = runda.GetTrazeniBroj();
		int* brojevi_runde = runda.GetBrojevi();
		output_file << "Brojevi koji su bili na raspolaganju su:";
		for (int i = 0; i < 6; i++) {
			output_file << brojevi_runde[i];
			if (i != 5) output_file << ",";
		}
		output_file << endl;
		output_file << "Trazeni trocifreni broj je:" << trazeniBroj << endl;
		string unos_igraca;
		// neparan igra igrac A, a paran igrac B
		string igrac = trazeniBroj % 2 == 1 ? "A" : "B";
		unos(igrac, brojevi_runde, output_file, trazeniBroj);
	}
	output_file << "------------------------------" << endl;
	output_file << "Igrac A ima broj pobeda:" << brojPobedaIgracaA << endl;
	output_file << "Igrac B ima broj pobeda:" << brojPobedaIgracaB << endl;
	if (brojPobedaIgracaA > brojPobedaIgracaB) output_file << "Pobednik je igrac A!";
	else if (brojPobedaIgracaB > brojPobedaIgracaA) output_file << "Pobednik je igrac B!";
	else output_file << "Nereseno je";
	output_file.close();
}
