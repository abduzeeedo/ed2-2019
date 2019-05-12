#ifndef FUNCOESGERAIS_H_INCLUDED
#define FUNCOESGERAIS_H_INCLUDED
#include <iostream>
#include <fstream>
#include <cstring>
#include <algorithm>
#include <sstream>
#include "hashtableOA.h"
#include "hashtableEE.h"
#include "hashTableEC.h"

using namespace std;

///Funcoes com o proposito de auxiliar as manipulacoes de hash e de arquivos

int achaPrimo(int n);
void leituraArqAvaliacoes(int* userId, int* movieId, float* rating, string* timestamp);

///Funcoes que executam as hashs

void hash_sondagemLinear(int* userId, int* movieId);
void hash_sondagemQuadratica(int* userId, int* movieId);
void hash_reHash(int* userId, int* movieId);
void hash_encadeamentoExterno(int* userId, int* movieId);
void hash_encadeamentoCoalescido(int* userId, int* movieId);

#endif // FUNCOESGERAIS_H_INCLUDED