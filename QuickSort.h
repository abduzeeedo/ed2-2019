#include "rating.h"
#include <iostream>
#include <ctime>

class QuickSort
{
private:
	int particiona(Rating* vetor[], int inicio, int fim, int pos); //Funcao que particiona um vetor de ratings utilizando um pivo passado por parametro e realiza as torcas necessarias
	void troca(Rating* &r1, Rating* &r2);//Realiza a troca de posicao entre 2 objetos do tipo rating passados por parametro
	int numTrocas;//Contador do numero de trocas realizadas
	int numCompar;//Contador do numero de comparacoes realizadas
	double tempoGasto;//Contador do tempo gasto na execucao da funcao
public:
	QuickSort();//Construtor
	~QuickSort();//Destrutor
	void limpaDados();//Funcao usada zerar os atributos a fim de preparar para outra ordenacao
	void quicksort(Rating* vetor[], int ini, int fim, char tipo);//Funcao de ordenacao por QuickSort Recursivo e suas variacoes
	int mediana(Rating* vetor[], int numVal, int inicio, int fim);//Funcao que calcula a mediana entre 3 e 5 valores de rating userID e retorna a posicao de tal valor
	int getNumTrocas();//Retorna o numero de trocas do objeto
	int getNumComparacoes();//Retorna o numero de comparacoes do objeto
	double getTempoGasto();//Retorna o tempo gasto na execucao da ordenacao do objeto
};
