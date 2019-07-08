#include <iostream>
#include "Btree.h"

using namespace std;

///Construtor
Btree::Btree(int _d){

    raiz = NULL;
    d = _d;

}

Btree::~Btree(){

}

int Btree::get_D(){

    return d;
}

///Percorre toda a arvore em ordem crescente
void Btree::percorreArvore(){
    
    if (raiz != NULL) 
        raiz->percorre();

    //std::cout << std::endl << "Numero de nos = " << cont << std::endl;
    //std::cout << "Numero de chaves na raiz = " << raiz->n << std::endl;
}

///Busca uma avaliacao na arvore passada por parametro
BtreeNode* Btree::busca(rating* k, int& numComparacoesChaves, int& numCopias){
    
    if(raiz == NULL)
        return NULL;
        else
            return raiz->busca(k, numComparacoesChaves, numCopias);
}


void Btree::insere(rating* k, int& numComparacoesChaves, int& numCopias){
 
    if (raiz == NULL) 
    {  
        raiz = new BtreeNode(d, true);
        raiz->chaves[0] = k;  /// insere chave 
        raiz->n = 1;
        numCopias++;
    } 
    else  
    { 
        /// Se a raiz estiver cheia, tem que splita-la e a arvore aumentara sua altura 
        if (raiz->n == 2*d-1) 
        { 
            ///Sera a nova raiz
            BtreeNode *s = new BtreeNode(d, false); 
  
            ///A raiz antiga vai ser filha da nova raiz s
            s->C[0] = raiz; 
  
            ///Splita a raiz antiga e move uma chave para a nova raiz
            s->splitFilho(0, raiz, numCopias); 

            /// Com a raiz tendo dois filhos, tem que decidir qual dos dois 
            /// sera direcionado a nova chave que deseja-se inserir 
            int i = 0;

            ///Se a nova chave tiver userId maior ou userId igual e movieId maior o filho sera o da direita
            if (++(++(++numComparacoesChaves)) && s->chaves[0]->userId < k->userId || (s->chaves[0]->userId == k->userId && s->chaves[0]->movieId < k->movieId)) 
                i++; 

            ///Insere no filho certo
            s->C[i]->insereNaoCheio(k, numComparacoesChaves, numCopias); 
   
            raiz = s; 
        } 
        else /// Se a raiz nao estiver cheia
            raiz->insereNaoCheio(k, numComparacoesChaves, numCopias);
    } 
}