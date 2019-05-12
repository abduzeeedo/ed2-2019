#include <iostream>
#include <cmath>
#include "hashTableEC.h"

using namespace std;

long long unsigned int hashTableEC::colisoes = 0;
int hashTableEC::numInsercoes = 0;

///Construtor. Recebe o tamanho que sera a tabela e inicializa a tabela.
hashTableEC::hashTableEC(int tam){

    tableSize = tam;

    table = new chaveC*[tableSize];

    for(int i = 0; i < tableSize; i++){
        table[i] = new chaveC();
        table[i]->userId = 0;
        table[i]->movieId = 0;
        table[i]->status = -2;
        table[i]->prox = NULL;
    }

}

hashTableEC::~hashTableEC(){

    for(int i = 0; i < tableSize; i++){

        chaveC* p = table[i];
        delete p;
    }

    delete [] table;

}

///Funcao de hash que pega um numero primo alto, multiplica pelo movieID da chave e soma com seu userId,
///e por fim pega o resto da divisao pelo tamanho da tabela.
int hashTableEC::hashFunction(chaveC k){

    return ((2003*k.movieId + 1003*k.userId) % tableSize);

}


///Recebe a chave que se deseja inserir, e insere utilizando o tratamento de colisoes
///usando encadeamento coalescido sem porao.
void hashTableEC::insereChave(chaveC k){

        int pos = hashFunction(k);

        if(numInsercoes < tableSize){

            if(table[pos]->status == -2){

                table[pos]->userId = k.userId;
                table[pos]->movieId = k.movieId;
                table[pos]->status = -1;

                numInsercoes++;

            }else{

                colisoes++;

                chaveC* aux = table[pos];

                while(aux->prox != NULL){
                    colisoes++;
                    aux = aux->prox;
                }

                int pos2;

                for(int i = 1; i < tableSize;i++){

                    pos2 = (pos + i)%tableSize;

                    if(table[pos2]->status == -2){
                        table[pos2]->userId = k.userId;
                        table[pos2]->movieId = k.movieId;
                        table[pos2]->status = -1;
                        table[pos]->status = pos2;

                        aux->prox = table[pos2];
                        numInsercoes++;
                        break;
                    }else
                        colisoes++;

                }
            }
        }else
            cout << "Tabele cheia ! Impossivel inserir !" << endl;
}

///Imprime a tabela com as chaves.
void hashTableEC::imprimeTable(){

    for(int i = 0; i < tableSize;i++){

        cout << i << " -> ";

        cout << table[i]->userId << "|" << table[i]->movieId;


        cout  << "**" << table[i]->status;

        cout << endl;

    }

}

///Retorna a quantidade de memoria utilizada pela memoria em megaBytes.
float hashTableEC::memoriaUtilizada(){


    int tamanho = (sizeof(int) + sizeof(int) + sizeof(chaveC*) + sizeof(int))*tableSize;

    float mb = pow(2, 20);

    return (tamanho/mb);

}