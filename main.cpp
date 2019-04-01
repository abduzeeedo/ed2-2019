#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "stdlib.h"
#include "rating.h"
#include "InsertionSort.h"


using namespace std;

string analisaLinhas(ifstream& File)
{
	string linhaVerif;

	if (File)
	{
		while (File.good())
		{
			string linhaTemp;
			getline(File, linhaTemp);
			linhaTemp += "\n";

			linhaVerif += linhaTemp;
		}
		return linhaVerif;
	}
	else
	{
		cout << "ERRO AO LER O ARQUIVO DE MENU" << endl;
		return 0;
	}
}

void imprimeMenu()
{
	ifstream leitor("menu.txt"); //Le o menu to txt
	string art = analisaLinhas(leitor);
	cout << art << endl; //Imprime o menu

	leitor.close();
}

int main()
{
    imprimeMenu();
    return 0;
}
