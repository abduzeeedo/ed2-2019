#include <iostream>
#include "BtreeNode.h"

using namespace std;

BtreeNode::BtreeNode(int _d, bool _leaf){

    d = _d; 
    leaf = _leaf; 
   
    keys = new rating*[2*d-1]; 
    C = new BtreeNode*[2*d]; 
  
    n = 0;

}

BtreeNode::~BtreeNode(){

    delete [] keys;

    for(int i = 0; i < 2*d; i++)
        delete C[i];
    delete [] C;
}

void BtreeNode::traverse(){
 
    int i;
    for (i = 0; i < n; i++) 
    { 
        if (leaf == false){
            cout << "FOI PRO FILHO " << i << endl;
            C[i]->traverse();
        }
        
        cout << " " << keys[i]->userId << ", " << keys[i]->movieId << endl; 
    } 
  
    if (leaf == false){
        cout << "FOI PRO FILHO " << i << endl;
        C[i]->traverse();
    } 
}

BtreeNode* BtreeNode::search(rating* k, int& keysComparisons){

    int i = 0; 

    while (i < n && k->userId > keys[i]->userId && ++keysComparisons) 
        i++; 
    
    if(i < n && (keys[i]->userId == k->userId) && (keys[i]->movieId == k->movieId) && ++keysComparisons)
        return this;
         
    if(leaf == true) 
        return NULL; 
    
    return C[i]->search(k, keysComparisons);

}

void BtreeNode::insertNonFull(rating* k, int& keysComparisons){

    // Initialize index as index of rightmost element 
    int i = n-1; 
  
    // If this is a leaf node 
    if (leaf == true) 
    { 
        // The following loop does two things 
        // a) Finds the location of new key to be inserted 
        // b) Moves all greater keys to one place ahead 
        while (i >= 0 && keys[i]->userId > k->userId && ++keysComparisons) 
        { 
            keys[i+1] = keys[i]; 
            i--;
        }

        int j = i;
        while(j >= 0 && keys[j]->movieId > k->movieId && ++keysComparisons){

            keys[j+1] = keys[j]; 
            j--;
        }

        // Insert the new key at found location 
        keys[j+1] = k; 
        n = n+1; 
    } 
    else // If this node is not leaf 
    { 
        // Find the child which is going to have the new key 
        while (i >= 0 && keys[i]->userId > k->userId && ++keysComparisons) 
            i--; 

        int j = i;

        while(j >= 0 && keys[i]->movieId > k->movieId && ++keysComparisons)
            j--;

        // See if the found child is full 
        if (C[j+1]->n == 2*d-1) 
        { 
            // If the child is full, then split it 
            splitChild(j+1, C[j+1]); 
            //std::cout << "SPLITOU INSERINDO " << k->userId << " " << k->movieId << std::endl;]

            // After split, the middle key of C[i] goes up and 
            // C[i] is splitted into two.  See which of the two 
            // is going to have the new key 
            if (keys[i+1]->userId < k->userId && ++keysComparisons) 
                i++;
                else
                    if(keys[i+1]->userId == k->userId && keys[i+1]->movieId < k->movieId && ++keysComparisons)
                        i++;
        } 
        C[i+1]->insertNonFull(k, keysComparisons); 
        //std::cout << "INSERIU NO FILHO " << i+1 << std::endl;
    } 
} 
  
// A utility function to split the child y of this node 
// Note that y must be full when this function is called 
void BtreeNode::splitChild(int i, BtreeNode *y) 
{   
    // Create a new node which is going to store (d-1) keys 
    // of y 
    BtreeNode *z = new BtreeNode(y->d, y->leaf); 
    z->n = d - 1;  

    // Copy the last (d-1) keys of y to z 
    for (int j = 0; j < d-1; j++) 
        z->keys[j] = y->keys[j+d]; 
  
    // Copy the last t children of y to z 
    if (y->leaf == false) 
    { 
        for (int j = 0; j < d; j++) 
            z->C[j] = y->C[j+d]; 
    } 
  
    // Reduce the number of keys in y 
    y->n = d - 1; 
  
    // Since this node is going to have a new child, 
    // create space of new child 
    for (int j = n; j >= i+1; j--) 
        C[j+1] = C[j]; 
  
    // Link the new child to this node 
    C[i+1] = z; 
  
    // A key of y will move to this node. Find location of 
    // new key and move all greater keys one space ahead 
    for (int j = n-1; j >= i; j--) 
        keys[j+1] = keys[j]; 
  
    // Copy the middle key of y to this node 
    keys[i] = y->keys[d-1]; 
  
    // Increment count of keys in this node 
    n = n + 1; 
}
