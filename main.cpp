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

//Funcao de leitura do arq e inclusao para um vetor de objetos do tipo Rating
//entrada: o vetor objetos do tipo rating, e o tamanho desse vetor
//saida: o vetor de objetos do tipo rating totalmente preenchido com valores do arquivo ratings.csv
void instanciaObjArq (Rating** vetor, int tam){

    ifstream arquivo;
    arquivo.open("ratings.csv");

    string buffer;
    int userID;
    int movieID;
    float rating;
    string timeStamp;

    int pos = 0; //posicao do vetor de objetos

    if(arquivo.is_open()){

        ///pula primeira linha
        getline(arquivo, buffer);

        ///Pega linhas e vai adicionando em posicoes do vetor de objetos
        while(pos < tam){

                getline(arquivo, buffer, ',');
                userID = stoi(buffer);

                getline(arquivo, buffer, ',');
                movieID = stoi(buffer);

                getline(arquivo, buffer, ',');
                rating = stof(buffer);

                getline(arquivo, buffer, '\n');
                timeStamp = buffer;

                Rating* aux = new Rating(userID, movieID, rating, timeStamp); //cria um objeto auxiliar, colocando os valores lidos do arquivo
                vetor[pos] = aux; //atribui tais valores pra uma posicao do vetor de objetos

                pos++;
        }
        arquivo.close();

        randomiza(vetor, tam, 1); //Chama funcao que randomiza a posicao dos objetos do vetor

    }
    else
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

    //**************INSTANCIANDO VETOR DE OBJETOS, INSERINDO INFOS DO ARQUIVO CSV  E IMPRIMINDO TAL VETOR ****************************
    int tam = 50; // TAMANHO DO VETOR DE OBJETOS A SER INSTANCIADO E IMPRESSO EM TELA

    Rating** exemplo = new Rating*[tam]; //exemplo de como instanciar um vetor da classe Ratings com TAM ratings
    instanciaObjArq(exemplo, tam); //Atribui valores no vetor exemplo com TAM valores do arquivo Ratings.csv

    for (int i=0; i < tam; i++){
        exemplo[i]->printRating();//imprime os valores dos TAM objetos
    }
    //*******************************************************************************************************************************

    imprimeMenu();


    //**
    delete [] userId;
    delete [] movieId;
    delete [] rating;
    delete [] timestamp;
    //**
    return 0;
}
