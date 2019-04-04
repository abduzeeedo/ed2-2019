#include "MergeSort.h"
using namespace std;

MergeSort::MergeSort()
{

}

MergeSort::~MergeSort()
{
    //dtor
}

MergeSort::MergeSort(int* vetor, int indiceEsquerdo, int indiceDireito)
{
    if(indiceEsquerdo < indiceDireito){
        //define o meio
        int meio = indiceEsquerdo + (indiceDireito - indiceEsquerdo)/2;

        //chama passando a primeira metada
        MergeSort(vetor, indiceEsquerdo, meio);

        //chama passando a segunda metade
        MergeSort(vetor, meio+1, indiceDireito);


        //une os dois sub arrays que foram criados
        Merge(vetor, indiceEsquerdo, meio, indiceDireito);
    }

}

//Junta os dois sub arrays criados com o vetor principal
void MergeSort::Merge(int* vetor, int indiceEsquerdo, int meio, int indiceDireito)
{
    int i,j,k; //contadores

    int n = meio - indiceEsquerdo + 1; //tamanho do primeiro vetor auxiliar
    int n2 = indiceDireito - meio;   //tamanho do segundo vetor auxiliar

    int* vetorEsquerdo;
    int* vetorDireito; //vetores temporarios

    //Passa os elementos da primeira metada para o vetor auxiliar
    for( i = 0; i < n; i++){
        vetorEsquerdo[i] = vetor[indiceEsquerdo+1];
    }
    //Passa os elementos da segunda metada para o vetor auxiliar
    for( j = 0; j<n2; j++){
        vetorDireito[j] = vetor[meio + 1 + j];
    }

    //reseta variaveis
    i = 0;
    j = 0;
    k = indiceEsquerdo;

    while(i < n && j < n2){

        //caso o valor na esquerda seja menor, passa o valor para o vetor principal
        if(vetorEsquerdo[i] < vetorDireito[j]){
            vetor[k] = vetorEsquerdo[i];
            //incrementa para passar para a proxima posição
            i++;
        } else {
            vetor[k] = vetorDireito[j];
            //incrementa para passar para a proxima posição
            j++;
        }
        k++;
    }

    //se faltarem elementos, passar para o vetor principal
    while( i < n) {
        vetor[k] = vetorEsquerdo[i];
        i++;
        k++;
    }

     //se faltarem elementos, passar para o vetor principal
    while( j < n2) {
        vetor[k] = vetorDireito[j];
        j++;
        k++;
    }

}
