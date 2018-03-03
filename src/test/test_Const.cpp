#include <iostream>
#include <stdio.h>
#include<cstdlib>
#include<ctime>

#include "include/grammar/grammar.h"

void printRepresentation(INode* inode, std::string name){
    std::cout << name+"->toString() = "<< inode->toString() <<"\n";
    std::cout << name+"->evaluate(0.0) = " << inode->evaluate(0.0) << "\n";
    std::cout << name+"->getChildrenNum() = " << inode->getChildrenNum() << "\n";
    INode** children = inode->getChildren();
    std::cout << "BEGIN CHILDREN LIST\n";
    for(int i=0; i<inode->getChildrenNum(); i++)
        if(children[i] != nullptr)
            std::cout << name+"->children["<<i<<"] = " << children[i]->toString() << "\n";
    std::cout << "END CHILDREN LIST\n";
};

int main(int argc, char const *argv[]){
    Const* cnst = new Const(3);
    std::cout << "TEST CONST\ncnst = new Const(3);\n\n";

    std::cout << "REPRESENTATION\n";
    printRepresentation(cnst, "cnst");

    std::cout << "\nOPERATION: cnst->expandRandom(4);\n";
    cnst->expandRandom(4);
    std::cout << "REPRESENTATION\n";
    printRepresentation(cnst, "cnst");

    std::cout << "\nOPERATION: cnst->setChild(0, new Const(5));\n";
    INode* tmpc = new Const(5);
    cnst->setChild(0, tmpc);
    delete tmpc;
    std::cout << "REPRESENTATION\n";
    printRepresentation(cnst, "cnst");

    std::cout << "\nOPERATION: cnst_1 = cnst->copyToEnd(); delete cnst;\n";
    INode* cnst_1 = cnst->copyToEnd();
    delete cnst;
    std::cout << "REPRESENTATION\n";
    printRepresentation(cnst_1, "cnst_1");
    delete cnst_1;
    return 0;
}