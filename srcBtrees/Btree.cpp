#include <iostream>
#include "Btree.h"

using namespace std;

Btree::Btree(int _d){

    root = NULL;
    d = _d;

}

Btree::~Btree(){

}

int Btree::get_D(){

    return d;
}

void Btree::traverse(){

    if (root != NULL) 
        root->traverse();
}

BtreeNode* Btree::search(rating* k, int& keysComparisons){
    
    return (root == NULL)? NULL : root->search(k, keysComparisons);
}

void Btree::insert(rating* k, int& keysComparisons){

    // If tree is empty 
    if (root == NULL) 
    { 
        // Allocate memory for root 
        root = new BtreeNode(d, true);
        root->keys[0] = k;  // Insert key 
        root->n = 1;  // Update number of keys in root 
    } 
    else // If tree is not empty 
    { 
        // If root is full, then tree grows in height 
        if (root->n == 2*d-1) 
        { 
            // Allocate memory for new root 
            BtreeNode *s = new BtreeNode(d, false); 
  
            // Make old root as child of new root 
            s->C[0] = root; 
  
            // Split the old root and move 1 key to the new root 
            s->splitChild(0, root); 
            //std::cout << "SPLITOU INSERINDO " << k->userId << " " << k->movieId << std::endl;

            // New root has two children now.  Decide which of the 
            // two children is going to have new key 
            int i = 0; 
            if ((s->keys[0]->userId < k->userId) && ++keysComparisons) 
                i++;
                    else
                        if((s->keys[0]->userId == k->userId) && (s->keys[0]->userId < k->userId) && ++keysComparisons)
                            i++;
                    
            s->C[i]->insertNonFull(k, keysComparisons); 
  
            // Change root 
            root = s; 
        } 
        else // If root is not full, call insertNonFull for root
            root->insertNonFull(k, keysComparisons);
    } 
}

void Btree::printTree(){

    if(root != NULL){

        root->traverse();

    }else
        std::cout << "ARVORE VAZIA ! :(" << std::endl;

}