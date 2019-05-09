#ifndef FUNCOESGERAIS_CPP_INCLUDED
#define FUNCOESGERAIS_CPP_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rating.h"
#define TAM 100
#include "ordenacoes.h"
#include "funcoesGerais.h"
#include <ctime>
#include <algorithm>

string salvar = "";
string salvarQuickSort = "";
string salvarQuickSortInt = "";
string saidasMenu = "";

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
        cout << "Erro ao abrir Arquivo Menu!" << endl;
    }

}

//Funcao Que salva uma string em um arquivo .txt
//Entrada: String a ser salva e arquivo .txt onde os dados serao salvos.
//Saida: Escrita da string passada por parametro em um arquivo .txt (tambem passado por parametro)
void salvarTxt(string salvar, string file) {
	ofstream arquivo;
	arquivo.open(file);
	arquivo << salvar << endl;
	//arquivo.close();
}

//Funcao randomiza o conteudo de um vetor de ratings
//Entrada: Ponteiro para vetor do tipo Rating, tamanho do vetor origem seed do random
//Saida: O vetor de Ratings com valores entre as posicoes randomizados (desordena)
void randomiza(Rating** vetor, int tam, int seed) {
	srand(seed);
	for (int i = 0; i < tam; i++) {
		swap(vetor[i], vetor[rand() % tam]);
	}
}

//Funcao randomiza o conteudo de um vetor de ratings
//Entrada: Ponteiro para vetor do tipo Rating, tamanho do vetor origem seed do random
//Saida: O vetor de Ratings com valores entre as posicoes randomizados (desordena)
void randomizaInt(int vetor[], int tam, int seed) {
	srand(seed);
	for (int i = 0; i < tam; i++) {
		swap(vetor[i], vetor[rand() % tam]);
	}
}

//Imprime vetor de inteiros de userID
void imprimeVetor(int* userId){
cout<<"teste"<<endl;
    for(int i =0; i < TAM ; i++){
        cout << " |" << userId[i] << " ";
    }
}

//imprime vetor de objetos (todos os dados)
void imprimeObjetos (Rating** vetor, int tam){
    for (int i=0; i < tam; i++){
        vetor[i]->printRating();//imprime os valores dos tam objetos
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
    arquivo.open("ratings_small.csv");

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

    srand(time(NULL));
    ifstream arquivo;
    arquivo.open("ratings_small.csv");

    string buffer;
    int userID;
    int movieID;
    float rating;
    string timeStamp;

    int pos = 0; //posicao do vetor de objetos

    if(arquivo.is_open()){

        ///pula primeira linha
        getline(arquivo, buffer);
        cout << "Inicializando vetor de objetos a partir do arquivo ratings.csv. Tamanho do vetor:" << tam << endl;
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

                //vetor[pos]->addRating(userID, movieID, rating, timeStamp);

                Rating* aux = new Rating(userID, movieID, rating, timeStamp); //cria um objeto auxiliar, colocando os valores lidos do arquivo
                vetor[pos] = aux; //atribui tais valores pra uma posicao do vetor de objetos
                pos++;
        }
        arquivo.close();
        randomiza(vetor, tam, rand()); //Chama funcao que randomiza a posicao dos objetos do vetor

    }
    else
        cout << "Erro ao abrir o arquivo !" << endl;
}

void loteQuickSort (Rating** vetor, int tam) {
    srand(time(NULL));
    random_shuffle(&vetor[0],&vetor[tam]);
    Ordenacoes ordena;
    int valorN [7] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    //for que percorre todos os N valores pedidos no enunciado
    for (int i=0; i < 3; i++){
        //For que realiza ordenacoes com 5 seeds diferentes para cada N
        for (int j=0; j < 6; j++){
            int seed = rand() % valorN[j];
            ordena.quicksort(vetor, 0, valorN[i],'r'); //Chama o Insertion
            cout << "Ordenando vetor via QuickSort para N=" << valorN[i] << " e seed = " << seed << endl;
            salvarQuickSort += "==========================================================================\n";
            salvarQuickSort += "Algoritmo QuickSort para N=" + to_string(valorN[i]) + " e seed = " + to_string(seed) + "\n";
            salvarQuickSort += "Numero de Trocas:" + to_string(ordena.getNumTrocas()) + ". Numero de Comparacoes:" + to_string(ordena.getNumComparacoes()) + ". Tempo Gasto:" + to_string(ordena.getTempoGasto()) + ".\n";
            salvarQuickSort += "==========================================================================\n";
            srand(seed));
            random_shuffle(&vetor[0],&vetor[tam]);
            ordena.limpaDados();
        }
    }
    cout << "Funcao em Lote para QuickSort finalizada com sucesso." << endl;
    salvarTxt(salvarQuickSort, "saidasQuickSort.txt");
}

void loteQuickSortInt (int vetor[], int tam, char tipo) {
    srand(time(NULL));
    random_shuffle(&vetor[0],&vetor[tam]);
    Ordenacoes ordena;
    int valorN [7] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    //for que percorre todos os N valores pedidos no enunciado
    for (int i=0; i < 3; i++){
        //For que realiza ordenacoes com 5 seeds diferentes para cada N
        for (int j=0; j < 6; j++){
            int seed = rand() % valorN[j];
            ordena.QuickSortInt(vetor, 0, valorN[i]); //Chama o Insertion
            cout << "Ordenando vetor via QuickSort de Inteiros para N=" << valorN[i] << " e seed = " << seed << " E do tipo " << tipo << endl;
            salvarQuickSortInt += "==========================================================================\n";
            salvarQuickSortInt += "Algoritmo QuickSort de Inteiros para N=" + to_string(valorN[i]) + " e seed = " + to_string(seed) + " E do tipo " + tipo + "\n";
            salvarQuickSortInt += "Numero de Trocas:" + to_string(ordena.getNumTrocas()) + ". Numero de Comparacoes:" + to_string(ordena.getNumComparacoes()) + ". Tempo Gasto:" + to_string(ordena.getTempoGasto()) + ".\n";
            salvarQuickSortInt += "==========================================================================\n";
            srand(seed);
            random_shuffle(&vetor[0],&vetor[tam]);
            ordena.limpaDados();
        }
    }
    cout << "Funcao em Lote para QuickSort finalizada com sucesso." << endl;
    salvarTxt(salvarQuickSortInt, "saidasQuickSortInt.txt");
}


#endif // FUNCOESGERAIS_CPP_INCLUDED
