//
// Created by Matthias Schedel on 09.05.22.
//

#include "Agent.h"

Agent::Agent(string literal, bool negated)
{
    // Automatically detect negated literal
    if(literal[0] == '!')
    {
        this->negated = true;
        this->description_string = literal.erase(0, 1);
    }
    else {
        this->description_string = literal;
        this->negated = negated;
    }
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
    if (agent->description_string == this->description_string)
    {
        return true;
    }
    else return false;
}

