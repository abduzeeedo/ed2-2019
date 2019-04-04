#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include "stdlib.h"
#include "rating.h"
#define TAM 100
#include "ordenacoes.h"
#include <ctime>

string salvar = "";
string saidasMenu = "";
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
        cout << "Erro ao abrir Arquivo MENUUUUUUUUUU!" << endl;
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

//funcaoo para converter um int para String, usada na escrita de dados em arquivo txt
//Entrada: Numero Inteiro -- Saida: Representacao deste numero inteiro em uma String
string toString(double i)
{
	stringstream ss;
	ss << i;
	string retorno = ss.str();
	return retorno;
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
        randomiza(vetor, tam, 1); //Chama funcao que randomiza a posicao dos objetos do vetor

    }
    else
        cout << "Erro ao abrir o arquivo !" << endl;
}

void loteQuickSort (Rating** vetor, int tam) {

    Ordenacoes ordena;
    int valorN [7] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    for (int i=0; i < 7; i++){
        ordena.quicksort(vetor, 0, valorN[i],'r'); //Chama o Insertion
        cout << "Ordenando vetor via QuickSort para N=" << valorN[i] << endl;
        salvar += "==========================================================================\n";
        salvar += "Algoritmo QuickSort para N=" + toString(valorN[i]) + "\n";
        salvar += "Numero de Trocas:" + toString(ordena.getNumTrocas()) + ". Numero de Comparacoes:" + toString(ordena.getNumComparacoes()) + ". Tempo Gasto:" + toString(ordena.getTempoGasto()) + ".\n";
        salvar += "==========================================================================\n";
        randomiza(vetor, tam, 1);
        ordena.limpaDados();
    }
    cout << "Funcao em Lote para QuickSort finalizada com sucesso." << endl;
}

void loteQuickSortInt (Rating** vetor, int tam) {

    Ordenacoes quickInt;
    int* userId = new int[tam];
    for (int i=0; i<tam; i++){
        userId[i] = vetor[i]->getUserID();
    }

    int valorN [7] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    for (int i=0; i < 3; i++){
        quickInt.QuickSortInt(userId, 0, tam);
        cout << "Ordenando vetor via QuickSort para Vetor de Inteiros de tamanho N=" << valorN[i] << endl;
        salvar += "==========================================================================\n";
        salvar += "Algoritmo QuickSort para N=" + toString(valorN[i]) + "\n";
        //salvar += "Numero de Trocas:" + toString(ordena.getNumTrocas()) + ". Numero de Comparacoes:" + toString(ordena.getNumComparacoes()) + ". Tempo Gasto:" + toString(ordena.getTempoGasto()) + ".\n";
        salvar += "==========================================================================\n";
        //ordena.limpaDados();
    }
    cout << "Funcao em Lote para QuickSort de Inteiros finalizada com sucesso." << endl;
}

void loteHeapSort (Rating** vetor, int tam) {

    Ordenacoes heapSort;
    int* userId = new int[tam];
    for (int i=0; i<tam; i++){
        userId[i] = vetor[i]->getUserID();
    }

    int valorN [7] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    for (int i=0; i < 3; i++){
        quickInt.QuickSortInt(userId, 0, tam);
        cout << "Ordenando vetor via QuickSort para Vetor de Inteiros de tamanho N=" << valorN[i] << endl;
        salvar += "==========================================================================\n";
        salvar += "Algoritmo QuickSort para N=" + toString(valorN[i]) + "\n";
        //salvar += "Numero de Trocas:" + toString(ordena.getNumTrocas()) + ". Numero de Comparacoes:" + toString(ordena.getNumComparacoes()) + ". Tempo Gasto:" + toString(ordena.getTempoGasto()) + ".\n";
        salvar += "==========================================================================\n";
        //ordena.limpaDados();
    }
    cout << "Funcao em Lote para QuickSort de Inteiros finalizada com sucesso." << endl;
}

void loteHeapSort (Rating** vetor, int tam) {

    Ordenacoes ordena;
    int valorN [7] = {1000, 5000, 10000, 50000, 100000, 500000, 1000000};

    for (int i=0; i < 7; i++){
        ordena.heapsort(vetor, valorN[i]); //Chama o Insertion
        cout << "Ordenando vetor via HeapSort para N=" << valorN[i] << endl;
        salvar += "==========================================================================\n";
        salvar += "Algoritmo HeapSort para N=" + toString(valorN[i]) + "\n";
        salvar += "Numero de Trocas:" + toString(ordena.getNumTrocas()) + ". Numero de Comparacoes:" + toString(ordena.getNumComparacoes()) + ". Tempo Gasto:" + toString(ordena.getTempoGasto()) + ".\n";
        salvar += "==========================================================================\n";
        randomiza(vetor, tam, 1);
        ordena.limpaDados();
    }
    cout << "Funcao em Lote para HeapSort finalizada com sucesso." << endl;
}


int main()
{
    //**************INSTANCIANDO VETOR DE OBJETOS, INSERINDO INFOS DO ARQUIVO CSV ****************************
    int tam = 2000000; // TAMANHO DO VETOR DE OBJETOS A SER INSTANCIADO E IMPRESSO EM TELA

    Rating** exemplo = new Rating*[tam]; //exemplo de como instanciar um vetor da classe Ratings com tam ratings
    instanciaObjArq(exemplo, tam); //Atribui valores no vetor exemplo com tam valores do arquivo Ratings.csv
    //*******************************************************************************************************************************


    imprimeMenu();

    loteQuickSort(exemplo, tam);
    randomiza(exemplo, tam, 2);
    loteHeapSort(exemplo, tam);

    //loteQuickSort(exemplo, tam);
    /*
    //adicionei isso aqui para testar
    int* userId = new int[TAM];
    int* movieId = new int[TAM];
    float* rating = new float[TAM];
    string* timestamp = new string[TAM];

    leituraArq(userId, movieId, rating, timestamp, TAM);

    Ordenacoes quickInt;

    quickInt.QuickSortInt(userId, 0, TAM);

    cout<<"------------------------------------------------------------------------------------------------"<<endl;
    cout<<"                                  Ordenacao usando Merge Sort                                   "<<endl;
    cout<<"------------------------------------------------------------------------------------------------"<<endl;

   // MergeSort(userId, 0, TAM-1);
    cout<<"testeeee"<<endl;
    imprimeVetor(userId);


    delete [] userId;
    delete [] movieId;
    delete [] rating;
    delete [] timestamp;
    */
    salvarTxt(salvar, "saida.txt");
    //**
    return 0;
}
