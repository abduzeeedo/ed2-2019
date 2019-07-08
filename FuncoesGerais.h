#include <iostream>
#include <fstream>
#include <ctime>
#include "Btree.h"

extern int numElementos;
extern std::string raiz_dir;

void leArq(rating** elements); //Le o arquivo ratings.csv
Btree* criaBTree(rating** elements, int numIter); ///Cria arvore com os elementos passados por parametro
void fazBuscas(Btree* btree, rating** elements, int numInter); ///Faz as buscas de todos os elementos