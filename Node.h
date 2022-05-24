//
// Created by Matthias Schedel on 09.05.22.
//

#ifndef READONCE_MCNETS_NODE_H
#define READONCE_MCNETS_NODE_H

#pragma once
#include <vector>
#include <string>

class Agent;

using namespace std;


class Node
{
public:
    Node(/* args */);
    ~Node();

    virtual vector<Agent*> GetAgentDesc() = 0;
    virtual bool ContainsAgent(Agent* agent, bool ignore_negated = false) = 0;

    string description_string;
};

#endif //READONCE_MCNETS_NODE_H
