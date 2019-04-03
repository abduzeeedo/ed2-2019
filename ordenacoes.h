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
	void insertionsort(Rating* vetor[], int inicio, int fim);//Funcao de Ordenacao por InsertionSort
	void limpaDados();//Funcao usada zerar os atributos a fim de preparar para outra ordenacao
};

#endif // INSERTIONSORT_H_INCLUDED
