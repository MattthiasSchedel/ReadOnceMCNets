//
// Created by Matthias Schedel on 09.05.22.
//

#include "Rule.h"

Rule::Rule(Node* pattern, float value)
{
    this->pattern = pattern;
    this->value = value;
}

Rule::~Rule()
{
}