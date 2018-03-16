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
    delete children;
};

int main(int argc, char const *argv[]){/*
    std::srand(std::time(nullptr));
    int randmax = 100.0;
    Leaf* leaf = new Leaf(randmax, );
    std::cout << "TEST Leaf\nleaf = new Leaf("<<randmax<<");\n\n";
    std::cout << "REPRESENTATION\n";
    printRepresentation(leaf, "leaf", 0.0);

    //Leaf->expandRandom(...)
    for(int i=0; i<5; i++){
        std::cout << "\nOPERATION: leaf->expandRandom("<<i<<");\n";
        leaf->expandRandom(i);
        std::cout << "REPRESENTATION\n";
        printRepresentation(leaf, "leaf", 0.0);
    }

    //Leaf->setChild(...)
    std::cout << "\nOPERATION: leaf->setChild(0, new Const(5));\n";
    INode* tmpc = new Const(5);
    delete leaf->setChild(0, tmpc);
    std::cout << "REPRESENTATION\n";
    printRepresentation(leaf, "leaf", 0.0);

    //Leaf->copyToEnd(...)
    std::cout << "\nOPERATION: leaf_1 = leaf->copyToEnd(); delete leaf;\n";
    INode* leaf_1 = leaf->copyToEnd();
    delete leaf;
    std::cout << "REPRESENTATION\n";
    printRepresentation(leaf_1, "leaf_1", 0.0);

    std::cout << "\nOPERATION: leaf_1->setChild(0, new Var()[evaluated with 234.567]);\n";
    INode* tmpv = new Var();
    delete leaf_1->setChild(0, tmpv);
    std::cout << "REPRESENTATION\n";
    printRepresentation(leaf_1, "leaf_1", 234.567);
    delete leaf_1;

    //Leaf->expandLast(...)
    leaf = new Leaf(randmax);
    std::cout << "\nOPERATION: leaf = new Leaf("<<randmax<<");\n";
    std::cout << "REPRESENTATION\n";
    printRepresentation(leaf, "leaf", 0.0);

    std::cout << "\nOPERATION: leaf->expandLast(_LEAF_FIRST_PROD, 7.98);\n";
    leaf->expandLast(_LEAF_FIRST_PROD, 7.98);
    std::cout << "REPRESENTATION\n";
    printRepresentation(leaf, "leaf", 0.0);

    std::cout << "\nOPERATION: leaf->expandLast(_LEAF_SECOND_PROD, 0.0);\n";
    leaf->expandLast(_LEAF_SECOND_PROD, 0.0);
    std::cout << "REPRESENTATION\n";
    printRepresentation(leaf, "leaf", 0.0);
    
    delete leaf;
*/
    return 0;
}