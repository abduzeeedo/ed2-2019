#include <iostream>
#include <cmath>
#include "hashTableEE.h"

using namespace std;

int long long unsigned  hashTableEE::colisoes = 0;
int hashTableEE::numInsercoes = 0;

///Construtor. Recebe o tamanho que sera a tabela e inicializa a tabela
hashTableEE::hashTableEE(int tam){

    tableSize = tam;

    table = new chaveL*[tableSize];
    //cout << tableSize << endl;
    for(int i = 0; i < tableSize; i++){
        table[i] = new chaveL();
        table[i]->userId = -1;
        table[i]->movieId = -1;
        table[i]->preenchido = false;
        table[i]->prox = NULL;
    }

}

hashTableEE::~hashTableEE(){

    for(int i = 0; i < tableSize; i++){

        chaveL* p = table[i];

        while(p != NULL){

            chaveL* t = p->prox;
            delete p;
            p = t;
        }
    }

    delete [] table;
}

///Funcao de hash que pega um numero primo alto, multiplica pelo movieID da chave e soma com seu userId,
///e por fim pega o resto da divisao pelo tamanho da tabela.
int hashTableEE::hashFunction(chaveL k){

    return ((2003*k.movieId + 1003*k.userId) % tableSize);

}

///Recebe a chave que se deseja inserir, e insere utilizando o tratamento de colisoes
///usando encadeamento externo.
void hashTableEE::insereChave(chaveL k){
 
        int pos = hashFunction(k);

        if(table[pos]->preenchido == false){

            table[pos]->userId = k.userId;
            table[pos]->movieId = k.movieId;
            table[pos]->preenchido = true;

            numInsercoes++;

        }else{

            colisoes++;

            chaveL* novo = new chaveL();

            novo->userId = k.userId;
            novo->movieId = k.movieId;
            novo->prox = table[pos]->prox;
            table[pos]->prox = novo;


            numInsercoes++;
        }
}


///Imprime a tabela com as chaves.
void hashTableEE::imprimeTable(){


    for(int i = 0; i < tableSize; i++){

        cout << i << " -> ";

        chaveL* p = table[i];

        while(p != NULL){
            cout << p->userId << "|" << p->movieId << ", ";
            p = p->prox;
        }

        cout << endl;
    }

}

///Retorna a quantidade de memoria utilizada pela memoria em megaBytes.
float hashTableEE::memoriaUtilizada(){

    int tamanho = (sizeof(int) + sizeof(int) + sizeof(bool) + sizeof(chaveL*))*tableSize + ((sizeof(int) + sizeof(int) + sizeof(bool) + sizeof(chaveL*))*colisoes);

    float mb = pow(2, 20);

    return (tamanho/mb);
}