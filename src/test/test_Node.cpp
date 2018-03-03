#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<ctime>

#include "include/grammar/grammar.h"

void printRepresentation(INode* inode, std::string name, double x_val){
    std::cout << name+"->toString() = "<< inode->toString() <<"\n";
    std::cout << name+"->evaluate("<<x_val<<") = " << inode->evaluate(x_val) << "\n";
    std::cout << name+"->getChildrenNum() = " << inode->getChildrenNum() << "\n";
    INode** children = inode->getChildren();
    std::cout << "BEGIN CHILDREN LIST\n";
    for(int i=0; i<inode->getChildrenNum(); i++)
        if(children[i] != nullptr)
            std::cout << name+"->children["<<i<<"] = " << children[i]->toString() << "\n";
    std::cout << "END CHILDREN LIST\n";
};

int main(int argc, char const *argv[]){
    std::srand(std::time(nullptr));
    int randseed = std::rand(), randmax = 100.0;
    Node* node = new Node(randmax, randseed);
    std::cout << "TEST NODE\nnode = Node("<<randmax<<", "<<randseed<<");\n\n";

    std::cout << "REPRESENTATION\n";
    printRepresentation(node, "node", 0.0);

    //Node->expandRandom(...)
    for(int i=0; i<5; i++){
        std::cout << "\nOPERATION: node->expandRandom("<<i<<");\n";
        node->expandRandom(i);
        std::cout << "REPRESENTATION\n";
        printRepresentation(node, "node", 0.0);
    }

    printRepresentation(node, "node", 0.0);

    //Node->expandByOne(...)
    std::cout << "\nOPERATION: node->expandByOne(_NODE_SECOND_PROD, EXP);\n";
    node->expandByOne(_NODE_SECOND_PROD, EXP);
    std::cout << "REPRESENTATION\n";
    printRepresentation(node, "node", 0.0);

    std::cout << "\nOPERATION: node->expandByOne(_NODE_THIRD_PROD, PLUS);\n";
    node->expandByOne(_NODE_THIRD_PROD, PLUS);
    std::cout << "REPRESENTATION\n";
    printRepresentation(node, "node", 0.0);

    //Node->setChild(...)
    std::cout << "\nOPERATION: node->setChild(0, Node->Leaf->Var());\n";
    Node* tmpn_1 = new Node(randmax, std::rand());
    tmpn_1->expandByOne(_NODE_FIRST_PROD, 0);
    ((Leaf*)tmpn_1->getChildren()[0])->expandLast(_LEAF_SECOND_PROD, 0.0);
    node->setChild(0, tmpn_1);
    std::cout << "REPRESENTATION\n";
    printRepresentation(node, "node", 0.0);

    std::cout << "\nOPERATION: node->setChild(1, Node->Leaf->1.59));\n";
    Node* tmpn_2 = new Node(randmax, std::rand());
    tmpn_2->expandByOne(_NODE_FIRST_PROD, 0);
    ((Leaf*)tmpn_2->getChildren()[0])->expandLast(_LEAF_FIRST_PROD, 1.59);
    node->setChild(1, tmpn_2);
    std::cout << "REPRESENTATION\n";
    printRepresentation(node, "node", 2.42);

    //Leaf->copyToEnd(...)
    std::cout << "\nOPERATION: node = node->copyToEnd(); delete node;\n";
    INode* node_1 = node->copyToEnd();
    delete node;
    std::cout << "REPRESENTATION\n";
    printRepresentation(node_1, "node_1", 2.42);

    return 0;
}