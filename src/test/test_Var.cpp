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
    Var* var = new Var();
    std::cout << "TEST VAR\nvar = new Var();\n\n";

    std::cout << "REPRESENTATION\n";
    printRepresentation(var, "var", 0.0);

    std::cout << "\nOPERATION: var->evaluate(234.976);\n";
    std::cout << "REPRESENTATION\n";
    printRepresentation(var, "var", 234.976);

    std::cout << "\nOPERATION: var->expandRandom(4);\n";
    var->expandRandom(4);
    std::cout << "REPRESENTATION\n";
    printRepresentation(var, "var", 234.976);

    std::cout << "\nOPERATION: var->setChild(0, new Var());\n";
    INode* tmpc = new Var();
    var->setChild(0, tmpc);
    delete tmpc;
    std::cout << "REPRESENTATION\n";
    printRepresentation(var, "var", 234.976);

    std::cout << "\nOPERATION: var_1 = var->copyToEnd(); delete var;\n";
    INode* var_1 = var->copyToEnd();
    delete var;
    std::cout << "REPRESENTATION\n";
    printRepresentation(var_1, "var_1", 234.976);
    delete var_1;
    return 0;
}