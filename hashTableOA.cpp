#include <iostream>
#include <cmath>
#include "hashTableOA.h"

using namespace std;

long long unsigned int hashTableOA::colisoes = 0;
int hashTableOA::numInsercoes = 0;

///Construtor. Recebe o tamanho que sera a tabela e inicializa a tabela
hashTableOA::hashTableOA(int tam){

    tableSize = tam;
    table = new chave[tableSize];

    for(int i = 0; i < tableSize;i++){
        table[i].userId = 0;
        table[i].movieId = 0;
        table[i].preenchido = false;
    }

}

hashTableOA::~hashTableOA(){

    delete [] table;

}

///Funcao de hash que pega um numero primo alto, multiplica pelo movieID da chave e soma com seu userId,
///e por fim pega o resto da divisao pelo tamanho da tabela.
int hashTableOA::hashFunction(chave k){

    return ((2003*k.movieId + 1003*k.userId) % tableSize);

}

///Tratamento da colisao por sondagem linear. Recebe a chave e o hashCode dessa chave como parametro.
///Retorna a posicao valida achada pelo tratamento, se houver algum problema , retorna -1.
int hashTableOA::sondagemLinear(chave k, int pos){

    int posicao;

    for(int i = 1; i < tableSize; i++){

        posicao = (pos + i)%tableSize;

        if(table[posicao].preenchido == false){
            numInsercoes++;
            return posicao;
        }

        colisoes++;
    }

    return -1;
}

///Tratamento da colisao por sondagem quadratica. Recebe a chave e o hashCode dessa chave como parametro.
///Retorna a posicao valida achada pelo tratamento, se houver algum problema , retorna -1.
int hashTableOA::sondagemQuadratica(chave k, int pos){

    int posicao;

    for(int i = 1; i < tableSize; i++){
        posicao = (pos + 2*i + 5*i*i)%tableSize;

        if(table[posicao].preenchido == false){
            numInsercoes++;
            return posicao;
        }

        colisoes++;
    }

    return -1;
}

///Tratamento da colisao por reHash. Recebe a chave e o hashCode dessa chave como parametro.
///Retorna a posicao valida achada pelo tratamento, se houver algum problema , retorna -1.
int hashTableOA::reHash(chave k, int pos){

    int posicao;
    int h2;

    h2 = 1 + (2003*k.movieId + k.userId)%(tableSize - 1);

    for(int i = 1; i < tableSize; i++){
        posicao = (pos + i*(h2))%tableSize; // (h(1) + i*h(2))mod M

        if(table[posicao].preenchido == false){
            numInsercoes++;
            return posicao;
        }

        colisoes++;
    }

    return -1;
}

///Imprime a tabela com as chaves.
void hashTableOA::imprimeTable(){

    for(int i = 0; i < tableSize; i++)
        cout << i << " -> " << table[i].userId << " | " << table[i].movieId << endl;

}

///Recebe a chave e qual tipo de tratamento escolhido para resolucao de colisoes.
///'L' para sondagem linear.
///'Q' para sondagem quadratica.
///'R' para reHash.
void hashTableOA::insereChave(chave k, char tratamento){

    ///Verifica se a tabela comporta a insercao
    if(numInsercoes < tableSize){

        int pos = hashFunction(k);
        int pos2;

        ///Se a posicao nao tiver preechida, insere a chave
        if(table[pos].preenchido == false){

            table[pos].userId = k.userId;
            table[pos].movieId = k.movieId;
            table[pos].preenchido = true;
            numInsercoes++;

        ///Se nao, ela colidiu e chama-se o tratamento adequado
        }else{

            colisoes++;

            if(tratamento == 'L')
                pos2 = sondagemLinear(k, pos);
            if(tratamento == 'Q')
                pos2 = sondagemQuadratica(k, pos);
            if(tratamento == 'R')
                pos2 = reHash(k, pos);

            if(pos2 != -1){
                table[pos2].userId = k.userId;
                table[pos2].movieId = k.movieId;
                table[pos2].preenchido = true;
            }else
                cout << "Impossivel inserir chave, algum problema ocorreu !" << endl;
        }
    }else
        cout << "Impossivel inserir chave, tabela cheia !" << endl;
}

///Retorna a quantidade de memoria utilizada pela memoria em megaBytes.
float hashTableOA::memoriaUtilizada(){

    int tamanho = (sizeof(int) + sizeof(int) + sizeof(bool))*tableSize;

    float mb = pow(2, 20);

    return (tamanho/mb);
}
