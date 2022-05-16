//
// Created by Matthias Schedel on 09.05.22.
//

#ifndef READONCE_MCNETS_MCNET_H
#define READONCE_MCNETS_MCNET_H

#pragma once
#include<vector>
#include<iostream>
using namespace std;

#include "Agent.h"
#include "Rule.h"
#include "Operator.h"

struct ABTF {
    vector<vector<int>> A;
    vector<vector<int>> B;
    vector<float> T;
    vector<float> F;
};

class MCNet
{
private:
    vector<Agent*> agents;
    vector<Rule*> rules;
public:
    MCNet(vector<Agent*> agents, vector<Rule*> rules);
    ~MCNet();

    ABTF Sh(Node *rule);
    vector<float> shapley();
};

#endif //READONCE_MCNETS_MCNET_H
