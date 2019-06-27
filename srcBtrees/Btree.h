#ifndef BTREE_H_INCLUDED
#define BTREE_H_INCLUDED

#include "BtreeNode.h"

class Btree{

private:
    
    BtreeNode* root;  ///Ponteiro para raiz
    int d; ///Ordem

public:

    Btree(int _d);
    ~Btree();

    void traverse();///Funcao que percorre a arvore
    void printTree();///Printa a arvore por No

    BtreeNode* search(rating* k, int& keysComparisons);///Funcao que procura um no na arvore

    void insert(rating* k, int& keysComparisons); /// Funcao que insere uma chave na arvore

    int get_D();

};


#endif // BTREE_H_INCLUDED