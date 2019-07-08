#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include "BtreeNode.h"

class Btree{

private:
    
    BtreeNode* raiz;  ///Ponteiro para raiz
    int d; ///Ordem : a ordem utilizada aqui diz respeito ao numero de filhos minimo,
           ///seguindo a regra (para nao raiz): 
           ///            d <= filhos <= 2d
           ///           d-1  <= numChaves <= 2d-1
           ///se for, raiz :
           ///            2 <= filhos <=2d
           ///            1 <= numChaves <= 2d-1
           ///
           ///Por exemplo, se d = 3, o numero de chaves mininas eh 2 e o maximo eh 5
           ///e o numero de filhos minimos eh 3 e o maximo eh 6.
public:

    Btree(int _d);
    ~Btree();

    void percorreArvore();///Funcao que percorre a arvore

    BtreeNode* busca(rating* k, int& numComparacoesCopias, int& numCopias);///Funcao que procura um no na arvore

    void insere(rating* k, int& numComparacoesCopias, int& numCopias); /// Funcao que insere uma chave na arvore

    int get_D();

};


#endif // BTREE_H_INCLUDED