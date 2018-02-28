#include "include/genetics/Forest.h"

#include<cstdlib>

Forest::Forest(int treeNum, int depth, int threshold, int randmax, int randseed){
    if(treeNum < 0)
        return;
    std::srand(randseed);
    this->treePool = new Tree*[treeNum];
    this->treeNum = treeNum;
    this->threshold = threshold;
    for(int i=0; i<treeNum; i++)
        this->treePool[i] = new Tree(depth, randmax,std::rand());
};

void Forest::crossover(int depth, int tree1_id, int tree2_id){
    if(tree1_id < 0 || tree1_id > this->treeNum ||
        tree2_id < 0 || tree2_id > this->treeNum ||
            depth < 1)
        return;

    INode* subTree_1 = this->treePool[tree1_id]->getRandomSubtree(depth-1);
    INode* subTree_2 = this->treePool[tree2_id]->getRandomSubtree(depth-1);
    INode** sT1_children = subTree_1->getChildren();
    INode** sT2_children = subTree_2->getChildren();
    int sT1_childrenNum = subTree_1->getChildrenNum();
    int sT2_childrenNum = subTree_2->getChildrenNum();
    int child1_id = 0, child2_id = 0;
    
    if(sT1_childrenNum>1)
        child1_id = std::rand() % sT1_childrenNum;
    if(sT2_childrenNum>1)
        child2_id = std::rand() % sT2_childrenNum;

    INode* tempChild = sT1_children[child1_id];
    subTree_1->setChild(child1_id, sT2_children[child2_id]);
    subTree_2->setChild(child2_id, tempChild);
};

void Forest::mutation(int depth, int tree_id){
    if(tree_id < 0)
        return;

    this->treePool[tree_id]->mutation(depth);
};