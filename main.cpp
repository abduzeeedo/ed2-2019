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

using namespace std;

int main()
{
    //**************INSTANCIANDO VETOR DE OBJETOS, INSERINDO INFOS DO ARQUIVO CSV ****************************
    int tam = 5000000; // TAMANHO DO VETOR DE OBJETOS A SER INSTANCIADO E IMPRESSO EM TELA

    Rating** objetos = new Rating*[tam]; //exemplo de como instanciar um vetor da classe Ratings com tam ratings
    instanciaObjArq(objetos, tam); //Atribui valores no vetor exemplo com tam valores do arquivo Ratings.csv
    //*******************************************************************************************************************************

    int* vet = new int[5000000];

    for (int i=0; i < tam; i++){
        vet[i] = objetos[i]->getUserID();
    }

    loteInsertionSort(vet, tam);

    /*
    random_shuffle(&vet[0],&vet[tam]);

    for (int i=0; i < 500; i++){
        cout << vet[i] << endl;
    }

    cout << "-----------------------------------------------------------------------------" << endl;

    Ordenacoes ordena;

    ordena.mergesort2(vet, 0, tam);

    for (int i=0; i < 500; i++){
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
    //
    delete [] vet;
    return 0;
}
