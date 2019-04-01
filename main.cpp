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
    ifstream leitor("menu.txt"); //Le o menu to txt
	string buffer;

	while(!leitor.eof()){
        getline(leitor, buffer);
        cout << buffer << endl;
	}
}

int main()
{
    imprimeMenu();
    return 0;
}
