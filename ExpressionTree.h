//
// Created by Matthias Schedel on 17.05.22.
//

#ifndef READONCE_MCNETS_EXPRESSIONTREE_H
#define READONCE_MCNETS_EXPRESSIONTREE_H
#include "Agent.h"
#include "Token.h"



class ExpressionTree {
private:
    Node* build_expression_tree(vector<Token*> tokens);
    vector<Token *> tokenize(string input_string);

public:
    Node* expression_tree_from_string(string input_string);
};


#endif //READONCE_MCNETS_EXPRESSIONTREE_H
