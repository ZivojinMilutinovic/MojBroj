

#include<iostream>
#include "Igra.h"
#include "Test.h"
using namespace std;

int main(int argc, char** argv)
{
	Igra igra(argv[1]);
	igra.igraj();
	// test slucajevi sa klasom
	Test test;
	test.computer_pronalazi_resenje();
	test.computer_racuna_izraz();

}


