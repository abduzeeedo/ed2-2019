#include "QuickSort.h"
using namespace std;


QuickSort::QuickSort()
{
}

QuickSort::~QuickSort()
{
}

QuickSort::QuickSort(int* userId, int inicio, int fim){

    int esquerda, direita, pivo, meio, aux;

    //limites da esquerda e da direita da região analisada
    esquerda = inicio;
    direita = fim;

    //ajustando auxiliares do centro
    meio = (int)((esquerda + direita)/2);
    pivo = userId[meio];

    while(direita > esquerda) {

      while(userId[esquerda] < pivo) {
        esquerda = esquerda +1;
        }
        while(userId[direita] > pivo) {
            direita = direita - 1;
        }

        if(esquerda <= direita){
            //realiza a troca
            aux = userId[esquerda];
            userId[esquerda] = userId[direita];
            userId[direita] = aux;

            //Faz o limites laterais andarem para o centro
            esquerda = esquerda + 1;
            direita = direita - 1;

        }

    }

    //recursão para continuar comparando
    if(inicio < direita) {
        QuickSort(userId, inicio, direita);
    }

    if(esquerda < fim) {
        QuickSort(userId, esquerda, fim);
    }

}



