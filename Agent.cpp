//
// Created by Matthias Schedel on 09.05.22.
//

#include "Agent.h"

Agent::Agent(string literal, bool negated)
{
    this->literal = literal;
    this->negated = negated;
}

Agent::~Agent()
{
}

vector<Agent*> Agent::GetAgentDesc()
{
    this->agent = vector<Agent*> {this};
    return this->agent;
}

bool Agent::ContainsAgent(Agent* agent, bool ignore_negated)
{
    if (agent->literal == this->literal)
    {
        return true;
    }
    else return false;
}

