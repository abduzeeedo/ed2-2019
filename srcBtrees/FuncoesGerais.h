#include <iostream>
#include <fstream>
#include <ctime>
#include "Btree.h"

extern int numElementos;

void readFile(rating** elements); //Le o arquivo ratings.csv
Btree* createBTree(rating** elements, unsigned int seed, int numIter);
void makeSearches(Btree* btree, rating** elements, unsigned int seed, int numInter);