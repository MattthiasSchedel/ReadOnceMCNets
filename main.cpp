#include "Node.h"
#include "Agent.h"
#include "Operator.h"
#include "Rule.h"
#include "MCNet.h"

#include "iostream"

using namespace std;

int main()
{
    Agent * agent_x1 = new Agent("x1", false);
    Agent * agent_x2 = new Agent("x2", false);
    Agent * agent_x3 = new Agent("x3", false);
    Agent * agent_nx1 = new Agent("x1", true);
    Agent * agent_nx2 = new Agent("x2", true);
    Agent * agent_nx3 = new Agent("x3", true);

    // x1
    Operator * nx2_and_nx3 = new Operator("and");
    nx2_and_nx3->left = agent_nx2;
    nx2_and_nx3->right = agent_nx3;

    Operator * x1_and_nx2_and_nx3 = new Operator("and");
    x1_and_nx2_and_nx3->left = agent_x1;
    x1_and_nx2_and_nx3->right = nx2_and_nx3;

    x1_and_nx2_and_nx3->GetAgentDesc();

    // x2
    Operator * x2_and_nx3 = new Operator("and");
    x2_and_nx3->left = agent_x2;
    x2_and_nx3->right = agent_nx3;

    Operator * nx1_and_x2_and_nx3 = new Operator("and");
    nx1_and_x2_and_nx3->left = agent_nx1;
    nx1_and_x2_and_nx3->right = x2_and_nx3;

    nx1_and_x2_and_nx3->GetAgentDesc();

    // x3
    Operator * nx2_and_x3 = new Operator("and");
    nx2_and_x3->left = agent_nx2;
    nx2_and_x3->right = agent_x3;

    Operator * nx1_and_nx2_and_x3 = new Operator("and");
    nx1_and_nx2_and_x3->left = agent_nx1;
    nx1_and_nx2_and_x3->right = nx2_and_x3;

    nx1_and_nx2_and_x3->GetAgentDesc();

    // x1 and x2
    Operator * x2_and_nx3_2 = new Operator("and");
    x2_and_nx3_2->left = agent_x2;
    x2_and_nx3_2->right = agent_nx3;

    Operator * x1_and_x2_and_nx3 = new Operator("and");
    x1_and_x2_and_nx3->left = agent_x1;
    x1_and_x2_and_nx3->right = x2_and_nx3_2;

    x1_and_x2_and_nx3->GetAgentDesc();

    // x1 and x3
    Operator * nx2_and_x3_2 = new Operator("and");
    nx2_and_x3_2->left = agent_nx2;
    nx2_and_x3_2->right = agent_x3;

    Operator * x1_and_nx2_and_x3 = new Operator("and");
    x1_and_nx2_and_x3->left = agent_x1;
    x1_and_nx2_and_x3->right = nx2_and_x3_2;

    x1_and_nx2_and_x3->GetAgentDesc();

    // x2 and x3
    Operator * x2_and_x3 = new Operator("and");
    x2_and_x3->left = agent_x2;
    x2_and_x3->right = agent_x3;

    Operator * nx1_and_x2_and_x3 = new Operator("and");
    nx1_and_x2_and_x3->left = agent_nx1;
    nx1_and_x2_and_x3->right = x2_and_x3;

    nx1_and_x2_and_x3->GetAgentDesc();

    // x1 and x2 and x3
    Operator * x2_and_x3_2 = new Operator("and");
    x2_and_x3_2->left = agent_x2;
    x2_and_x3_2->right = agent_x3;

    Operator * x1_and_x2_and_x3 = new Operator("and");
    x1_and_x2_and_x3->left = agent_x1;
    x1_and_x2_and_x3->right = x2_and_x3_2;

    x1_and_x2_and_x3->GetAgentDesc();

    vector<Agent*> agents = {agent_x1, agent_x2, agent_x3};

    vector<Rule*> rules = {
            new Rule(x1_and_nx2_and_nx3, 12),
            new Rule(nx1_and_x2_and_nx3, 6),
            new Rule(nx1_and_nx2_and_x3, 9),
            new Rule(x1_and_x2_and_nx3, 24),
            new Rule(x1_and_nx2_and_x3, 27),
            new Rule(nx1_and_x2_and_x3, 15),
            new Rule(x1_and_x2_and_x3, 36)
    };

    MCNet * net = new MCNet(agents, rules);
    vector<float> values = net->shapley();
    for (float value : values)
    {
        cout << "Shapley value ist: " << value << endl;
    }
}