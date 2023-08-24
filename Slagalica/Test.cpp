#include "Test.h"
#include <iostream>
using namespace std;

void Test::computer_pronalazi_resenje()
{
	vector<int> niz{ 9, 4, 3, 1, 15, 75 };
	int trazeniBroj = 200;
	cout << igra.computer_racuna(niz, trazeniBroj) << "=" << trazeniBroj << endl;

	// Test 2
	vector<int> niz1{ 2, 2, 1, 3, 15, 25 };
	int trazeniBroj1 = 551;
	cout << igra.computer_racuna(niz1, trazeniBroj1) << "=" << trazeniBroj1 << endl;

	vector<int> niz2{ 4, 9, 5, 4, 25, 75 };
	int trazeniBroj2 = 434;
	cout << igra.computer_racuna(niz2, trazeniBroj2) << "=" << trazeniBroj2 << endl;


	vector<int> niz3{ 5, 6, 5, 2, 25, 50 };
	int trazeniBroj3 = 889;
	cout << igra.computer_racuna(niz3, trazeniBroj3) << "=" << trazeniBroj3 << endl;


	vector<int> niz4{ 5, 3, 5, 7, 20, 50 };
	int trazeniBroj4 = 471;
	cout << igra.computer_racuna(niz4, trazeniBroj4) << "=" << trazeniBroj4 << endl;

	vector<int> niz5{ 4, 5, 1, 2, 10, 25 };
	int trazeniBroj5 = 808;
	cout << igra.computer_racuna(niz5, trazeniBroj5) << "=" << trazeniBroj5 << endl;

	// edge case sa jedinicama ne radi kako treba
	vector<int> niz6{ 8, 2, 1, 1, 10, 10 };
	int trazeniBroj6 = 400;
	cout << igra.computer_racuna(niz6, trazeniBroj6) << "=" << trazeniBroj6 << endl;

	// NE MOZE SE PRONACI RESENJE
	vector<int> niz7{ 1, 2, 4, 8, 10, 25 };
	int trazeniBroj7 = 963;
	cout << igra.computer_racuna(niz7, trazeniBroj7) << ":=" << trazeniBroj7 << endl;
	cout << "Ne moze se pronaci tacan broj, prikazan je priblizan broj" << endl;

	vector<int> niz8{ 1, 1, 1, 8, 10, 10 };
	int trazeniBroj8 = 400;
	cout << igra.computer_racuna(niz8, trazeniBroj8) << ":=" << trazeniBroj8 << endl;

}

void Test::computer_racuna_izraz()
{
	cout <<"(((9+4)*3+1)*75)/15=" << igra.izracunajIzraz("(((9+4)*3+1)*75)/15") << endl;
	cout << "(2+2+3+15)*25+1=" << igra.izracunajIzraz("(2+2+3+15)*25+1") << endl;
	cout << "(4*9-25+75)*5+4=" << igra.izracunajIzraz("(4*9-25+75)*5+4") << endl;
	cout << "(25-5-2)*50-6-5=" << igra.izracunajIzraz("(25-5-2)*50-6-5") << endl;
	cout << "((5+5)*20+7-50)*3=" << igra.izracunajIzraz("((5+5)*20+7-50)*3") << endl;
	cout << "((5+1+10)*25+4)*2=" << igra.izracunajIzraz("((5+1+10)*25+4)*2") << endl;
	cout << "((8-2-1-1)*10)*10=" << igra.izracunajIzraz("((8-2-1-1)*10)*10") << endl;
	cout << "((1+25)*4-8)*10+2=" << igra.izracunajIzraz("((1+25)*4-8)*10+2") << endl;
}

Test::Test()
{
}
