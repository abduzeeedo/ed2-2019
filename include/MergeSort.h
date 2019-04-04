#ifndef MERGESORT_H
#define MERGESORT_H
#include "../rating.h"
#include <string>
#include <stdlib.h>
#include <iostream>


class MergeSort
{
    public:
        MergeSort();
        ~MergeSort();
        MergeSort(int* vetor, int indiceEsquerdo, int indiceDireito);
        void Merge(int* vetor, int indiceEsquerdo, int meio, int indiceDireito);

};
#endif // MERGESORT_H
