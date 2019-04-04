#ifndef ORDENACOES_H_INCLUDED
#define ORDENACOES_H_INCLUDED

#include "rating.h"
#include <iostream>
#include <ctime>

class Ordenacoes
{
private:
	int numTrocas;//Contador do numero de trocas realizadas
	int numCompar;//Contador do numero de comparacoes realizadas
	double tempoGasto; //Contador do tempo gasto na execucao da funcao
public:
	Ordenacoes();//Construtor
	~Ordenacoes();//Destrutor
	int getNumTrocas();//Retorna o numero de trocas do objeto
	int getNumComparacoes();//Retorna o numero de comparacoes do objeto
	double getTempoGasto();//Retorna o tempo gasto na execucao da ordenacao do objeto

	//----------------------- Algoritmo InsertionSort --------------------------------------
	void insertionsort(Rating* vetor[], int inicio, int fim);//Funcao de Ordenacao por InsertionSort
	void limpaDados();//Funcao usada zerar os atributos a fim de preparar para outra ordenacao
	//--------------------------------------------------------------------------------

	//------------------------- Algoritmo QuickSort --------------------------------------
	void QuickSortInt(int* userId, int inicio, int fim); //QuickSort para vetor de inteiros
	int particiona(Rating* vetor[], int inicio, int fim, int pos); //Funcao que particiona um vetor de ratings utilizando um pivo passado por parametro e realiza as torcas necessarias
	void troca(Rating* &r1, Rating* &r2);//Realiza a troca de posicao entre 2 objetos do tipo rating passados por parametro
	void quicksort(Rating* vetor[], int ini, int fim, char tipo);//Funcao de ordenacao por QuickSort Recursivo e suas variacoes
	int mediana(Rating* vetor[], int numVal, int inicio, int fim);//Funcao que calcula a mediana entre 3 e 5 valores de rating userID e retorna a posicao de tal valor
	//---------------------------------------------------------------------------------
	
	//-------------------------Algoritmo HeapSort--------------------------------------
	void heapsort(Rating* vetor[], int tam); //HeapSort para vetor de objetos
        void constroiHeap(Rating* vetor[], int tam, int indice_raiz); //Procedimento para construcao do Heap


};

#endif // INSERTIONSORT_H_INCLUDED
