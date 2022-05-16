//
// Created by Matthias Schedel on 09.05.22.
//

#include "Operator.h"

Operator::Operator(string data)
{
    this->operand = data;
}

Operator::~Operator()
{
}

vector<Agent*> Operator::GetAgentDesc()
{
    vector<Agent*> left_child_agents = left->GetAgentDesc();
    child_agents.insert(child_agents.end(), left_child_agents.begin(), left_child_agents.end());
    child_agents.insert(child_agents.end(), left_child_agents.begin(), left_child_agents.end());

    vector<Agent*> right_child_agents = right->GetAgentDesc();
    child_agents.insert(child_agents.end(), right_child_agents.begin(), right_child_agents.end());

    return child_agents;
}

bool Operator::ContainsAgent(Agent* agent, bool ignore_negated)
{
    for (auto a : this->child_agents)
    {
        if (a->literal == agent->literal)
        {
            if (ignore_negated)
            {
                return true;
            }
            else
            {
                if (a->negated == agent->negated)
                {
                    return true;
                }
            }
        }
    }
    return false;
}