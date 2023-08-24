#include "FileReader.h"

FileReader::FileReader(string naziv_fajla)
{
    this->naziv_fajla = naziv_fajla;
}

void FileReader::readFromFile(vector<Runda> &niz_rundi)
{
    if (naziv_fajla == "") return;
    fstream file;
    file.open(naziv_fajla, ios::in);
    if (file.is_open()) {
        // red koji ucitvamo
        string line;
        int trenutniBrojRunde = 1;
        // u ovaj niz smestamo sve brojeve i sedmi broj
        int *brojevi = new int[7];
        // Moze imati vrednosti od 0 do 5
        int trenutniBroj = 0;
        while (getline(file, line)) {
            brojevi[trenutniBroj++] = stoi(line);
            if (trenutniBroj == 7) {
                // pravimo novu rundu u koju prosledjujemo sve brojeve i broj runde
                Runda r(brojevi, trenutniBrojRunde);
                niz_rundi.push_back(r);
                //resetujemo sve brojeve i trenutni broj
                brojevi = new int[7];
                trenutniBroj = 0;
                trenutniBrojRunde++;
            }
        }
        file.close();
    }
}
