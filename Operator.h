//
// Created by Matthias Schedel on 09.05.22.
//

#ifndef READONCE_MCNETS_OPERATOR_H
#define READONCE_MCNETS_OPERATOR_H


#pragma once
#include <vector>
#include "Agent.h"
#include "Node.h"

class Operator : public Node
{
private:
    vector<Agent*> child_agents;

public:
    Operator(string data);
    ~Operator();

    vector<Agent*> GetAgentDesc();
    bool ContainsAgent(Agent* agent, bool ignore_negated = false);

    string operand;
    Node* left;
    Node* right;


};


#endif //READONCE_MCNETS_OPERATOR_H
