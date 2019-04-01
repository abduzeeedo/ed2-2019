#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "stdlib.h"
#include "rating.h"
#include "InsertionSort.h"


using namespace std;


void imprimeMenu(){

    ifstream leitor;
    leitor.open("menu.txt");//Le o menu to txt
	string buffer;

    if (leitor.is_open()){
        while(!leitor.eof()){
            getline(leitor, buffer);
            cout << buffer << endl;
        }
        leitor.close();
    }
    else {
        cout << "Erro ao abrir Arquivo!" << endl;
    }

}

int main()
{
    imprimeMenu();
    return 0;
}
