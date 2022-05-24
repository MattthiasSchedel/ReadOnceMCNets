//
// Created by Matthias Schedel on 17.05.22.
//

#ifndef READONCE_MCNETS_TOKEN_H
#define READONCE_MCNETS_TOKEN_H

#pragma once

#include <string>
#include "Node.h"
#include "Operator.h"
#include "Agent.h"

class Token;

using namespace std;

enum TokenType {none = 0, operator_type = 1, agent_type = 2, parenthesis_type = 3};


class Token {
public:
    Token(string token_string);
    Token & from_string(string token_string);

    TokenType type = none;
    Node* data;
    string token_text;
};


#endif //READONCE_MCNETS_TOKEN_H
