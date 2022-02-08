/** 
  * Assignment 4 for COSE213 Data Structures
  *
  * Won-Ki Jeong (wkjeong@korea.ac.kr)
  *
  * 2021. 11. 21
  *
  */
  
#include "LinkedBinaryTree.h"
#include "SearchTree.h" 
#include "AVLTree.h"

#include <cstdlib>
#include <iostream>
#include <ctime>
#include <time.h>       /* clock_t, clock, CLOCKS_PER_SEC */

#include <iostream>
 
using namespace std;

void test(int nElem){
    typedef Entry<int, float> EntryType;
    SearchTree<EntryType> bst;
    AVLTree<EntryType>    avl;
    clock_t tm;
    
    printf ("-----------------------------------\n");
    printf ("테스트 - %d\n", nElem);
    printf ("-----------------------------------\n");
    printf ("1. BST\n");
    printf ("-----------------------------------\n");
    printf ("(1). Skewed order\n");
    printf ("-----------------------------------\n");
    int *key_1 = new int[nElem];
    float *val_1 = new float[nElem];
    
    for(int i=0; i<nElem; i++)
    {
        key_1[i] = i;
        val_1[i] = i;
    }
    
    tm = clock();
    for(int i=0; i<nElem; i++)
    {
        bst.insert(key_1[i], val_1[i]);
    }
    tm = clock() - tm;
    printf ("Insert: %f\n",((float)tm)/(float)CLOCKS_PER_SEC);
    
    tm = clock();
    for(int i=0; i<nElem; i++)
    {
        bst.find(key_1[i]);
    }
    tm = clock() - tm;
    printf ("Find: %f\n",((float)tm)/(float)CLOCKS_PER_SEC);
    
    for(int i=0; i<nElem; i++)
    {
        bst.erase(key_1[i]);
    }
    printf ("-----------------------------------\n");
    printf ("(2). Random order\n");
    printf ("-----------------------------------\n");
    
    std::srand(std::time(0));
    
    for(int i=0; i<nElem; i++)
    {
        key_1[i] = std::rand();
        val_1[i] = (float) std::rand()/RAND_MAX * 20000;
    }
    
    tm = clock();
    for(int i=0; i<nElem; i++)
    {
        bst.insert(key_1[i], val_1[i]);
    }
    tm = clock() - tm;
    printf ("Insert: %f\n",((float)tm)/(float)CLOCKS_PER_SEC);
    
    tm = clock();
    for(int i=0; i<nElem; i++)
    {
        bst.find(key_1[i]);
    }
    tm = clock() - tm;
    printf ("Find: %f\n",((float)tm)/(float)CLOCKS_PER_SEC);
    
    printf ("-----------------------------------\n");

    printf ("2. AVL\n");
    printf ("-----------------------------------\n");

    
    printf ("(1). Skewed order\n");
    printf ("-----------------------------------\n");

    
    for(int i=0; i<nElem; i++)
    {
        key_1[i] = i;
        val_1[i] = i;
    }
    
    tm = clock();
    for(int i=0; i<nElem; i++)
    {
        avl.insert(key_1[i], val_1[i]);
    }
    tm = clock() - tm;
    printf ("Insert: %f\n",((float)tm)/(float)CLOCKS_PER_SEC);
    
    tm = clock();
    for(int i=0; i<nElem; i++)
    {
        avl.find(key_1[i]);
    }
    tm = clock() - tm;
    printf ("Find: %f\n",((float)tm)/(float)CLOCKS_PER_SEC);
    
    for(int i=0; i<nElem; i++)
    {
        avl.erase(key_1[i]);
    }
    printf ("-----------------------------------\n");

    printf ("(2). Random order\n");
    printf ("-----------------------------------\n");

    
    std::srand(std::time(0));
    
    for(int i=0; i<nElem; i++)
    {
        key_1[i] = std::rand();
        val_1[i] = (float) std::rand()/RAND_MAX * 20000;
    }
    
    tm = clock();
    for(int i=0; i<nElem; i++)
    {
        avl.insert(key_1[i], val_1[i]);
    }
    tm = clock() - tm;
    printf ("Insert: %f\n",((float)tm)/(float)CLOCKS_PER_SEC);
    
    tm = clock();
    for(int i=0; i<nElem; i++)
    {
        avl.find(key_1[i]);
    }
    tm = clock() - tm;
    printf ("Find: %f\n",((float)tm)/(float)CLOCKS_PER_SEC);
    
}

int main()
{
    int nElem_1 = 100;
    int nElem_2 = 500;
    int nElem_3 = 1000;
    int nElem_4 = 5000;
    int nElem_5 = 10000;
    int nElem_6 = 50000;
    int nElem_7 = 100000;
    int nElem_8 = 200000;
    
    test(nElem_1);
    test(nElem_2);
    test(nElem_3);
    test(nElem_4);
    test(nElem_5);
    test(nElem_6);
    test(nElem_7);
    test(nElem_8);

	return 0;
}
