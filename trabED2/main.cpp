#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "rating.h"
#define TAM 100
#include "ordenacoes.h"
#include "funcoesGerais.h"
#include <ctime>

using namespace std;

int main()
{
    //**************INSTANCIANDO VETOR DE OBJETOS, INSERINDO INFOS DO ARQUIVO CSV ****************************
    int tam = 20000; // TAMANHO DO VETOR DE OBJETOS A SER INSTANCIADO E IMPRESSO EM TELA

    Rating** exemplo = new Rating*[tam]; //exemplo de como instanciar um vetor da classe Ratings com tam ratings
    instanciaObjArq(exemplo, tam); //Atribui valores no vetor exemplo com tam valores do arquivo Ratings.csv
    //*******************************************************************************************************************************

    int vet[100];

    for (int i=0; i < 100; i++){
        vet[i] = exemplo[i]->getUserID();
        cout << vet[i] << endl;
    }



    Ordenacoes ordena;
    ordena.shell_sort(vet, 100);
    cout << "ORDENADO:" << endl;
    for (int i=0; i < 100; i++){
        cout << vet[i] << endl;
    }

    imprimeMenu();

    //loteQuickSort(exemplo, tam);

    //randomiza(exemplo, tam, 2);
    //loteHeapSort(exemplo, tam);

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
    //**
    return 0;
}
