//
// Created by Matthias Schedel on 09.05.22.
//

#ifndef READONCE_MCNETS_AGENT_H
#define READONCE_MCNETS_AGENT_H

#pragma once
#include <vector>
#include <string>
#include "Node.h"

using namespace std;
class Agent : public Node
{
private:
    vector<Agent*> agent;
public:
    Agent(string literal, bool negated = false);
    ~Agent();
    vector<Agent*> GetAgentDesc();
    bool ContainsAgent(Agent* agent, bool ignore_negated = false);

    bool negated;

    friend bool operator ==(const Agent& a1, const Agent& a2)
    {
        if (a1.description_string == a2.description_string)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

#endif //READONCE_MCNETS_AGENT_H
