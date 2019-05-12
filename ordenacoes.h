#ifndef ORDENACOES_H_INCLUDED
#define ORDENACOES_H_INCLUDED

#include "rating.h"
#include <iostream>
#include <ctime>

class Ordenacoes
{
private:
	long long int numTrocas;//Contador do numero de trocas realizadas
	long long int numCompar;//Contador do numero de comparacoes realizadas
	float tempoGasto; //Contador do tempo gasto na execucao da funcao

public:
	Ordenacoes();//Construtor
	~Ordenacoes();//Destrutor
	long long int getNumTrocas();//Retorna o numero de trocas do objeto
	long long int getNumComparacoes();//Retorna o numero de comparacoes do objeto
	double getTempoGasto();//Retorna o tempo gasto na execucao da ordenacao do objeto
    void limpaDados();//Funcao usada zerar os atributos a fim de preparar para outra ordenacao

	//----------------------- Algoritmo InsertionSort --------------------------------------
	void insertionsort(Rating* vetor[], int inicio, int fim);//Funcao de Ordenacao por InsertionSort em vetores de objetos
    void insertionsortInt(int vetor[], int inicio, int fim);//Funcao de Ordenacao por InsertionSort em vetores de inteiros (userID)
	//--------------------------------------------------------------------------------

	//------------------------- Algoritmo QuickSort --------------------------------------
	void QuickSortInt(int* userId, int inicio, int fim); //QuickSort para vetor de inteiros
	int particiona(Rating* vetor[], int inicio, int fim, int pos); //Funcao que particiona um vetor de ratings utilizando um pivo passado por parametro e realiza as trocas necessarias
	void troca(Rating* &r1, Rating* &r2);//Realiza a troca de posicao entre 2 objetos do tipo rating passados por parametro
	void quicksort(Rating* vetor[], int ini, int fim);//Funcao de ordenacao por QuickSort Recursivo e suas variacoes

	int particionaInt(int vetor[], int inicio, int fim, int pos); //Funcao que particiona um vetor de inteiros (UserIDs) utilizando um pivo passado por parametro e realiza as torcas necessarias
	void quicksortInteiros(int vetor[], int ini, int fim, char tipo);//Funcao de ordenacao por QuickSort Recursivo e suas variacoes (para um vetor de inteiros (UserIDs))
	int medianaInt(int vetor[], int numVal, int inicio, int fim);//Funcao que calcula a mediana entre 3 e 5 valores de userID e retorna a posicao de tal valor
	//---------------------------------------------------------------------------------

	//-------------------------Algoritmo HeapSort--------------------------------------
	void heapsort(int vetor[], int tam); //HeapSort para vetor de inteiros (UserIDs)
    void constroiHeap(int vetor[], int tam, int indice_raiz); //Procedimento para construcao do Heap

    //-------------------------Algoritmo Merge--------------------------------------
    void MergeSort(int* vetor, int indiceEsquerdo, int indiceDireito);//Método que realiza a ordenação via mergesort
    void Merge(int* vetor, int indiceEsquerdo, int meio, int indiceDireito);//Algoritmo auxiliar ao MergeSort, que realiza os "merges'

    //-------------------------Algoritmo ShellSort--------------------------------------
    void shell_sort(int vetor[], int tam);//Método "Meu Sort", escolhido como ordenação via ShellSort

};

#endif // INSERTIONSORT_H_INCLUDED
