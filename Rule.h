//
// Created by Matthias Schedel on 09.05.22.
//

#ifndef READONCE_MCNETS_RULE_H
#define READONCE_MCNETS_RULE_H

#pragma once

#include "Node.h"

class Rule
{
public:
    Rule(Node* pattern, float value);
    ~Rule();

    Node* pattern;
    float value;
};


#endif //READONCE_MCNETS_RULE_H
