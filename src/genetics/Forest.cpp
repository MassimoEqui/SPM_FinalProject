#include "include/genetics/Forest.h"

#include<cstdlib>

Forest::Forest(int treeNum, int depthmax, int threshold, int randmax, int randseed){
    if(treeNum < 0)
        return;
    std::srand(randseed);
    this->treePool = new Tree*[treeNum];
    this->treeNum = treeNum;
    this->threshold = threshold;
    this->depthmax = depthmax;
    for(int i=0; i<treeNum; i++)
        this->treePool[i] = new Tree(std::rand()%(depthmax+1), randmax, std::rand());
};

Forest::~Forest(){
    for(int i=0; i<this->treeNum; i++)
        delete this->treePool[i];
    delete this->treePool;
}

void Forest::crossover(int height, int tree1_id, int tree2_id){
    if(tree1_id < 0 || tree1_id > this->treeNum ||
        tree2_id < 0 || tree2_id > this->treeNum ||
            height < 0)
        return;
    
    //Get the trees
    Tree* tree_1 = this->treePool[tree1_id];
    Tree* tree_2 = this->treePool[tree2_id];
    int t1_depth = tree_1->getDepth();
    int t2_depth = tree_2->getDepth();

    std::cout << "DEBUG: +*-*+*-*+*-*+*-*+*-*+*-*+*-*+*-*+\n";
    std::cout << "tree_1 = " << tree_1->toString() << "\n";
    std::cout << "tree_2 = " << tree_2->toString() << "\n";

    //Basic cases
    if(height > t1_depth || height > t2_depth){
        std::cout << "DEBUG: case0\n";
        return;
    }

    if(height == t1_depth && height == t2_depth){
        std::cout << "DEBUG: case1\n";
        tree_1->setRoot((Node*)tree_2->setRoot((Node*)tree_1->getRoot()));
        return;
    }

    if(height == t1_depth){
        std::cout << "DEBUG: case2\n";
        INode* subTree_2 = tree_2->getRandomSubtree(t2_depth-height-1);
        INode** sT2_children = subTree_2->getChildren();
        int sT2_childrenNum = subTree_2->getChildrenNum();
        int child2_id = 0;
        if(sT2_childrenNum>1)
            child2_id = std::rand() % sT2_childrenNum;
        subTree_2->setChild(child2_id, tree_1->setRoot((Node*)sT2_children[child2_id]));
        return;
    }

    if(height == t2_depth){
        std::cout << "DEBUG: case3\n";
        INode* subTree_1 = tree_1->getRandomSubtree(t1_depth-height-1);
        INode** sT1_children = subTree_1->getChildren();
        int sT1_childrenNum = subTree_1->getChildrenNum();
        int child1_id = 0;
        if(sT1_childrenNum>1)
            child1_id = std::rand() % sT1_childrenNum;
        subTree_1->setChild(child1_id, tree_2->setRoot((Node*)sT1_children[child1_id]));
        return;
    }
    std::cout << "DEBUG: case4\n";
    
    //Get some random subtrees and their children
    INode* subTree_1 = tree_1->getRandomSubtree(t1_depth-height-1);
    INode* subTree_2 = tree_2->getRandomSubtree(t2_depth-height-1);
    INode** sT1_children = subTree_1->getChildren();
    INode** sT2_children = subTree_2->getChildren();
    int sT1_childrenNum = subTree_1->getChildrenNum();
    int sT2_childrenNum = subTree_2->getChildrenNum();
    //If a subtree has more than 1 child, choose one of them randomly
    int child1_id = 0, child2_id = 0;
    if(sT1_childrenNum>1)
        child1_id = std::rand() % sT1_childrenNum;
    if(sT2_childrenNum>1)
        child2_id = std::rand() % sT2_childrenNum;
    //Swap the choosen children
    subTree_2->setChild(child2_id,
        subTree_1->setChild(child1_id, sT2_children[child2_id]));
};

void Forest::mutation(int depth, int tree_id){
    if(tree_id < 0)
        return;

    this->treePool[tree_id]->mutation(depth);
};

std::string Forest::toString(){
    std::string s = "";
    for(int i=0; i<this->treeNum; i++)
        s = s+"\n\nTree [ "+std::to_string(i)+" ]\n"+this->treePool[i]->toString();
    s += "\n\n";
    return s;
}