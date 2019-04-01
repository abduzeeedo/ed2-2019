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

//Funcao de leitura do arq
//entrada:os vetores das chaves
//saida:
void leituraArq(int* userId, int* movieId, float* rating, string* timestamp, int NUM_ELEMENTOS){

    srand (time(NULL));
    int n = 1;
    int val;

    ifstream arquivo;
    arquivo.open("ratings.csv");

    string buffer;
    if(arquivo.is_open()){

        ///pula primeira linha
        getline(arquivo, buffer);
        int cont = 0;

        ///Pega linhas pulando aleatoriamente
        while(!arquivo.eof() && cont < NUM_ELEMENTOS){

            /// Pega um valor aleatorio entre 1 e n
            val = rand()% n+1;

            ///Probabilidade do programa ler a linha (quanto maior o limite, maior a probabilidade).
            ///Se o numero de linhas que quiser pegar  for muito grande, aumentar a probabilidade (limite)
            ///porque, se nao, o arquivo acaba antes de pegar todas as linhas que quiser (para o de 26 milhoes talvez nao tenha esse problema).
            if(val < 100){

                getline(arquivo, buffer, ',');
                userId[cont] = stoi(buffer);

                getline(arquivo, buffer, ',');
                //movieId[cont] = stoi(buffer);

                getline(arquivo, buffer, ',');
                //ratings[cont] = stof(buffer);

                getline(arquivo, buffer, '\n');
                //timestamp[cont] = buffer;

                cont++;
                n++;
            }

            getline(arquivo, buffer);
        }


        ///embaralha o vetor

        int aux;
        int indice;

        for(int i = 0;i < NUM_ELEMENTOS;i++){

            ///Numero aleatorio entre 0 e o ultimo indice
            indice = rand() % (NUM_ELEMENTOS-1);

            aux = userId[i];
            userId[i] = userId[indice];
            userId[indice] = aux;
        }

        arquivo.close();
    }else
        cout << "Erro ao abrir o arquivo !" << endl;
}


int main()
{	
    
    //adicionei isso aqui para testar
    int NUM_ELEMENTOS = 10000;
    int* userId = new int[NUM_ELEMENTOS];
    int* movieId = new int[NUM_ELEMENTOS];
    float* rating = new float[NUM_ELEMENTOS];
    string* timestamp = new string[NUM_ELEMENTOS];

    leituraArq(userId, movieId, rating, timestamp, NUM_ELEMENTOS);
    //**
	
    imprimeMenu();

    Rating** exemplo = new Rating*[5]; //exemplo de como instanciar um vetor da classe Ratings com 5 ratings
    Rating* ra = new Rating(1,1,2.5,"teste"); //criando um rating com os valores por parametro
    exemplo[1] = ra; //inserindo o rating criado na posicao 1 do vetor de ratings
	
    //**
    delete [] userId;
    delete [] movieId;
    delete [] rating;
    delete [] timestamp;
    //**
    return 0;
}
