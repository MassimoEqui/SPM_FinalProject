#include "include/genetics/Forest.h"

#include<cstdlib>
#include<cmath>
#include<vector>

#include<algorithm>

Forest::Forest(long treeNum, int depthmax, int randmax){
    if(treeNum < 0 || depthmax < 0) return;

    this->treeNum = treeNum;
    this->depthmax = depthmax;
    this->treePool = new std::pair<Tree*, double>[treeNum];
    this->bestTree.first = nullptr;
    this->bestTree.second = -1;
    this->fitnessUpdate_time = std::chrono::system_clock::duration::zero();
    this->fitnessUpdated = false;
    this->bestTreeUpdated = false;
    for(int i=0; i<treeNum; i++){
        this->treePool[i].first = new Tree(std::rand()%(depthmax+1), randmax);
        this->treePool[i].second = -1.0;
    }
};

Forest::~Forest(){
    for(int i=0; i<this->treeNum; i++)
        delete this->treePool[i].first;
    delete this->treePool;
};

double Forest::fitness(Tree* f, double* x_vals, double* y_vals, int points_no){
    double E = 0.0;
    for(int i=0; i<points_no; i++){
        double delta = y_vals[i] - f->evaluate(x_vals[i]);
        E += delta*delta;
    }

    return std::sqrt(E);
};

void Forest::updatePoolFitness(double* x_vals, double* y_vals, int points_no){
    if(this->fitnessUpdated) return;
    std::chrono::system_clock::time_point start, end;
    start = std::chrono::system_clock::now();

    for(int i=0; i<this->treeNum; i++)
        treePool[i].second =
            this->fitness(treePool[i].first, x_vals, y_vals, points_no);

    end = std::chrono::system_clock::now();
    this->fitnessUpdate_time += end - start;
    this->fitnessUpdated = true;
};

void Forest::updateBestTree(double* x_vals, double* y_vals, int points_no){
    if(this->bestTreeUpdated) return;

    this->updatePoolFitness(x_vals, y_vals, points_no);
    this->bestTree = this->treePool[0];
    for(int i=0; i<this->treeNum; i++){
        double new_E = this->treePool[i].second;
        double curr_E = this->bestTree.second;
        if(!std::isnan(new_E) && !std::isinf(new_E)){
            if(std::isnan(curr_E) || std::isinf(curr_E) || new_E < curr_E)
                this->bestTree = this->treePool[i];
        } 
    }
    this->bestTreeUpdated = true;
};

int* Forest::selectBests(double* x_vals, double* y_vals, int points_no, int threshold){
    if(threshold > this->treeNum) return nullptr;

    this->updatePoolFitness(x_vals, y_vals, points_no);

    int* bestTrees_idx = new int[threshold];
    std::vector<int> indices(this->treeNum);
    std::iota(begin(indices), end(indices), 0);

    std::sort(
        begin(indices), end(indices),
        [&](int i, int j) {
            if(std::isnan(this->treePool[i].second) || std::isinf(this->treePool[i].second))
                return false;
            
            if(std::isnan(this->treePool[j].second) || std::isinf(this->treePool[j].second))
                return true;

            return this->treePool[i].second < this->treePool[j].second; 
        }
    );
    
    for(int i=0; i<threshold; i++)
        bestTrees_idx[i] = indices[i];
    
   return bestTrees_idx;

};

Tree* Forest::crossover(int tree1_id, int tree2_id){
    if(tree1_id < 0 || tree1_id > this->treeNum ||
        tree2_id < 0 || tree2_id > this->treeNum ||
            tree1_id == tree2_id)
        return nullptr;
    
    //Get the trees
    Tree* tree_1 = this->treePool[tree1_id].first->copy();
    Tree* tree_2 = this->treePool[tree2_id].first->copy();
    int t1_depth = tree_1->getDepth();
    int t2_depth = tree_2->getDepth();
    int height = std::rand() % (std::min(t1_depth, t2_depth) + 1);

    //Basic cases
    if(height > t1_depth || height > t2_depth)
        return tree_1;
    
    if(height == t1_depth && height == t2_depth){
        tree_1->setRoot((Node*)tree_2->setRoot((Node*)tree_1->getRoot()));
        return tree_1;
    }

    if(height == t1_depth){
        INode* subTree_2 = tree_2->getRandomSubtree(t2_depth-height-1);
        INode** sT2_children = subTree_2->getChildren();
        int sT2_childrenNum = subTree_2->getChildrenNum();
        int child2_id = 0;
        if(sT2_childrenNum>1)
            child2_id = std::rand() % sT2_childrenNum;
        subTree_2->setChild(child2_id, tree_1->setRoot((Node*)sT2_children[child2_id]));
        return tree_1;
    }

    if(height == t2_depth){
        INode* subTree_1 = tree_1->getRandomSubtree(t1_depth-height-1);
        INode** sT1_children = subTree_1->getChildren();
        int sT1_childrenNum = subTree_1->getChildrenNum();
        int child1_id = 0;
        if(sT1_childrenNum>1)
            child1_id = std::rand() % sT1_childrenNum;
        subTree_1->setChild(child1_id, tree_2->setRoot((Node*)sT1_children[child1_id]));
        return tree_1;
    }
    
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
    return tree_1;
};

Tree* Forest::mutation(int tree_id){
    if(tree_id < 0)
        return nullptr;
    int depth = std::rand() % (this->treePool[tree_id].first->getDepth()+1);
    Tree* newTree = this->treePool[tree_id].first->copy();
    newTree->mutation(depth);
    return newTree;
};

void Forest::newGeneration(std::vector<Tree*>& bestTrees){
    std::pair<Tree*, double>* newTreePool = new std::pair<Tree*, double>[this->treeNum];
    int bestTrees_no = bestTrees.size();
  
    for(int i=0; i<bestTrees_no; i++){
        newTreePool[i].first = bestTrees[i];
        newTreePool[i].second = -1.0;
    }

    for(int i=bestTrees_no; i<this->treeNum; i++){
        newTreePool[i].first = bestTrees[std::rand()%bestTrees_no]->copy();
        newTreePool[i].second = -1.0;
    }

    for(int i=0; i<this->treeNum; i++)
        delete this->treePool[i].first;
    delete this->treePool;

    this->treePool = newTreePool;
    this->fitnessUpdated = false;
    this->bestTreeUpdated = false;
};

std::pair<Tree*, double>* Forest::getTreePool(){
    return this->treePool;
}

Tree* Forest::getBestTree(double* x_vals, double* y_vals, int points_no){
    this->updateBestTree(x_vals, y_vals, points_no);
    return this->bestTree.first;
};

double Forest::getBestFitness(double* x_vals, double* y_vals, int points_no){
    this->updateBestTree(x_vals, y_vals, points_no);
    return this->bestTree.second;
};

Tree* Forest::getTree(int tree_id){
    if(tree_id < 0 || tree_id > this->treeNum) return nullptr;
    return this->treePool[tree_id].first;
};

std::chrono::duration<double> Forest::getFitnessUpdateTime(){
    return this->fitnessUpdate_time;
};

std::chrono::duration<double> Forest::resetFitnessUpdateTime(){
    this->fitnessUpdate_time = std::chrono::system_clock::duration::zero();
};

std::string Forest::toString(){
    std::string s = "";
    for(int i=0; i<this->treeNum; i++)
        s = s+"\n\nTree [ "+std::to_string((long long)i)+" ]\n"+this->treePool[i].first->toString();
    s += "\n\n";
    return s;
};