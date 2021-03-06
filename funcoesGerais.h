#ifndef FUNCOESGERAIS_H_INCLUDED
#define FUNCOESGERAIS_H_INCLUDED
#include <iostream>
#include <fstream>
#include <string>
#include "rating.h"
#include "ordenacoes.h"
#include "funcoesGerais.h"
#include <ctime>

void imprimeMenu();
void salvarTxt(string salvar, string file);
void randomiza(Rating** vetor, int tam, int seed);
void randomizaInt(int vetor [], int tam, int seed);
void imprimeVetor(int* userId);
void imprimeObjetos (Rating** vetor, int tam);
void leituraArq(int* userId, int* movieId, float* rating, string* timestamp, int NUM_ELEMENTOS);
void instanciaObjArq (Rating** vetor, int tam);
void loteQuickSort (Rating** vetor, int tam);
void loteQuickSortInt (int vetor[], int tam, char tipo);
void loteInsertionSort (int vetor[], int tam);
void loteMergeSort (int* vetor, int tam);
void loteShellSort(int* vetor, int tam);

#endif // FUNCOESGERAIS_H_INCLUDED
