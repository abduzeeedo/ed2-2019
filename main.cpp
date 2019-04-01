#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "stdlib.h"
#include "rating.h"
#include "InsertionSort.h"


using namespace std;

//Funcao de Impressao de Menu
//Entrada: Arquivo .txt do menu a ser impresso em tela
//Saida: Impressao em tela do Menu de opcoes
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

//Funcao randomiza o conteudo de um vetor de ratings
//Entrada: Ponteiro para vetor do tipo Rating, tamanho do vetor origem seed do random
//Saida: O vetor de Ratings com valores entre as posicoes randomizados (desordena)
void randomiza(Rating** vetor, int tam, int seed) {
	srand(seed);
	for (int i = 0; i < tam; i++) {
		swap(vetor[rand() % tam], vetor[rand() % tam]);
	}
}

int main()
{
    imprimeMenu();

    Rating** exemplo = new Rating*[5]; //exemplo de como instanciar um vetor da classe Ratings com 5 ratings
    Rating* ra = new Rating(1,1,2.5,"teste"); //criando um rating com os valores por parametro
    exemplo[1] = ra; //inserindo o rating criado na posicao 1 do vetor de ratings

    return 0;
}
