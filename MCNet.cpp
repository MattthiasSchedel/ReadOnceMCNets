//
// Created by Matthias Schedel on 09.05.22.
//

#include "MCNet.h"

// Helper Function stolen from Epic
double factorial_neg(int n)
{
    int n_factorial; // = n!
    if (n == 0)
    {
        n_factorial = 1;
    }

    else if(n <= 0)
    {
        n_factorial = 0;
    }

    else
    {
        // factorial[x]: x!
        auto factorial = new int[n + 1];
        factorial[0] = 1;
        factorial[1] = 1;

        for (int i = 2; i <= n; ++i) {
            factorial[i] = factorial[i - 1] * i;
        }

        n_factorial = factorial[n];
        delete[] factorial;
    }

    return n_factorial;
}

MCNet::MCNet(vector<Agent*> agents, vector<Rule*> rules)
{
    this->agents = agents;
    this->rules = rules;
}


MCNet::~MCNet()
{
}

void print1DVector(vector<int> vec1d)
{
    cout << "[";
    for(auto value : vec1d)
    {
        cout << value << ",";
    }
    cout << "]";
}

void print1DVector(vector<float> vec1d)
{
    cout << "[";
    for(auto value : vec1d)
    {
        cout << value << ",";
    }
    cout << "]" << endl;
}

void print2DVector(vector<vector<int>> vec2d)
{
    cout << "[";
    for (vector<int> vec1d : vec2d)
    {
        print1DVector(vec1d);
    }
    cout << "]" << endl;
}

ABTF MCNet::Sh(Node *rule)
{
    int n = agents.size();
    vector<vector<int>> A(n+1, vector<int>(n));
    vector<vector<int>> B(n+1, vector<int>(n));
    vector<float> T(n + 1, 0);
    vector<float> F(n + 1, 0);

    // Check if Node is an Agent
    Agent* agent = dynamic_cast<Agent*>(rule);
    if (agent != nullptr)
    {
        /*cout << endl << agent->literal;*/
        // Find index of agent in list of agents
        auto it = find_if(this->agents.begin(), this->agents.end(),[&agent](const Agent * f) -> bool
        {return f->literal == agent->literal;});
        int j = 0;
        if (it == this->agents.end())
        {
            // name not in vector
        }
        else
        {
            j = distance(this->agents.begin(), it);
        }

        if (!agent->negated)
        {
            T[1] = 1;
            F[0] = 1;
            A[0][j] = 1;
        }
        else
        {
            T[0] = 1;
            F[1] = 1;
            B[0][j] = 1;
        }
    }
    // If node is an Operator
    Operator* op = dynamic_cast<Operator*>(rule);
    if (op != nullptr)
    {
/*        cout << endl << op->operand;*/
        if (op->operand == "or")
        {
            ABTF abtf_1 = this->Sh(op->left);
            ABTF abtf_2 = this->Sh(op->right);

            for (int k = 0; k <= n; k++)
            {
                float t_sum = 0;
                for (int s = 0; s <= k; s++)
                {
                    t_sum += ((abtf_1.T[s] * abtf_2.T[k - s]) + (abtf_1.F[s] * abtf_2.T[k - s]) + (abtf_1.T[s] * abtf_2.F[k - s]));
                }
                T[k] = t_sum;

                float f_sum = 0;
                for (int s = 0; s <= k; s++)
                {
                    f_sum += abtf_1.F[s] * abtf_2.F[k - s];
                }
                F[k] = f_sum;

                for (int i = 0; i <= n; i++)
                {
                    // If the Agent at position i in agents list is not contained in this rule
                    if (!rule->ContainsAgent(this->agents[i]))
                    {
                        A[k][i] = 0;
                        B[k][i] = 0;
                    }
                    if (op->left->ContainsAgent(this->agents[i]))
                    {
                        int a_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            a_sum += abtf_1.A[s][i] * abtf_2.F[k - s];
                        }
                        A[k][i] = a_sum;

                        int b_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            b_sum += abtf_1.B[s][i] * abtf_2.F[k - s];
                        }
                        B[k][i] = b_sum;
                    }
                    if (op->right->ContainsAgent(this->agents[i]))
                    {
                        int a_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            a_sum += abtf_2.A[s][i] * abtf_1.F[k - s];
                        }
                        A[k][i] = a_sum;

                        int b_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            b_sum += abtf_2.B[s][i] * abtf_1.F[k - s];
                        }
                        B[k][i] = b_sum;
                    }
                }
            }
        }

        if (op->operand == "and")
        {
            ABTF abtf_1 = this->Sh(op->left);
            ABTF abtf_2 = this->Sh(op->right);

            for (int k = 0; k <= n; k++)
            {
                float t_sum = 0;
                for (int s = 0; s <= k; s++)
                {
                    t_sum += abtf_1.T[s] * abtf_2.T[k - s];
                }
                T[k] = t_sum;

                float f_sum = 0;
                for (int s = 0; s <= k; s++)
                {
                    f_sum += ((abtf_1.F[s] * abtf_2.F[k - s]) + (abtf_1.F[s] * abtf_2.T[k - s]) + (abtf_1.T[s] * abtf_2.F[k - s]));
                }
                F[k] = f_sum;

                for (int i = 0; i < n; i++)
                {
                    // If the Agent at position i in agents list is not contained in this rule
                    if (!rule->ContainsAgent(this->agents[i], true))
                    {
                        A[k][i] = 0;
                        B[k][i] = 0;
                    }
                    if (op->left->ContainsAgent(this->agents[i], true))
                    {
                        int a_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            a_sum += abtf_1.A[s][i] * abtf_2.T[k - s];
                        }
                        A[k][i] = a_sum;

                        int b_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            b_sum += abtf_1.B[s][i] * abtf_2.T[k - s];
                        }
                        B[k][i] = b_sum;
                    }
                    if (op->right->ContainsAgent(this->agents[i], true))
                    {
                        int a_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            a_sum += abtf_2.A[s][i] * abtf_1.T[k - s];
                        }
                        A[k][i] = a_sum;

                        int b_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            b_sum += abtf_2.B[s][i] * abtf_1.T[k - s];
                        }
                        B[k][i] = b_sum;
                    }
                }
            }
            /*cout << "A: " << endl;
            print2DVector(A);
            cout << "B: ";
            print2DVector(B);
            cout << "T: ";
            print1DVector(T);
            cout << "F: ";
            print1DVector(F);*/
        }

        if (op->operand == "xor")
        {
            ABTF abtf_1 = this->Sh(op->left);
            ABTF abtf_2 = this->Sh(op->right);

            for (int k = 0; k <= n; k++)
            {
                float t_sum = 0;
                for (int s = 0; s <= k; s++)
                {
                    t_sum += ((abtf_1.T[s] * abtf_2.F[k - s]) + (abtf_1.F[s] * abtf_2.T[k - s]));
                }
                T[k] = t_sum;

                float f_sum = 0;
                for (int s = 0; s <= k; s++)
                {
                    f_sum += ((abtf_1.F[s] * abtf_2.F[k - s]) + (abtf_1.T[s] * abtf_2.T[k - s]));
                }
                F[k] = f_sum;

                for (int i = 0; i <= n; i++)
                {
                    // If the Agent at position i in agents list is not contained in this rule
                    if (!rule->ContainsAgent(this->agents[i]))
                    {
                        A[k][i] = 0;
                        B[k][i] = 0;
                    }
                    if (op->left->ContainsAgent(this->agents[i]))
                    {
                        int a_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            a_sum += ((abtf_1.B[s][i] * abtf_2.T[k - s]) + (abtf_1.A[s][i] * abtf_2.F[k-s]));
                        }
                        A[k][i] = a_sum;

                        int b_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            b_sum += ((abtf_1.B[s][i] * abtf_2.F[k - s]) + (abtf_1.A[s][i] * abtf_2.T[k - s]));
                        }
                        B[k][i] = b_sum;
                    }
                    if (op->right->ContainsAgent(this->agents[i]))
                    {
                        int a_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            a_sum += ((abtf_2.B[s][i] * abtf_1.T[k - s]) + (abtf_2.A[s][i] * abtf_1.F[k - s]));
                        }
                        A[k][i] = a_sum;

                        int b_sum = 0;
                        for (int s = 0; s <= k; s++)
                        {
                            b_sum += ((abtf_2.B[s][i] * abtf_1.F[k - s]) + (abtf_2.A[s][i] * abtf_1.T[k - s]));
                        }
                        B[k][i] = b_sum;
                    }
                }
            }
        }
    }

    return ABTF{ A, B, T, F };
}

vector<float> MCNet::shapley()
{
    int n = agents.size();
    vector<float> t(n, 0);
    double v;

    int rule_counter = 0;
    for (Rule * j : rules)
    {
        ABTF abtf = Sh(j->pattern);

        int agent_counter = 0;

        for (auto& i : agents)
        {
            v = 0.00;
            if (j->pattern->ContainsAgent(i, true))
            {
                if (j->pattern->ContainsAgent(i, false))
                {
                    double sum = 0.00;
                    for (int k = 0; k <= n; k++)
                    {
                        sum += (factorial_neg(k) * factorial_neg(n - k - 1) * abtf.A[k][agent_counter]);
                    }
                    double fac = factorial_neg(n);
                    v = (1.00 / fac) * sum;
                }
                else
                {
                    double sum = 0.00;
                    for (int k = 0; k <= n; k++)
                    {
                        sum += (factorial_neg(k) * factorial_neg(n - k - 1) * abtf.B[k][agent_counter]);
                    }
                    double fac = factorial_neg(n);
                    /*cout << fac;*/
                    v = -(1.00 / fac) * sum;
                }
            }
            else
            {
                v = 0;
            }
            t[agent_counter] += j->value * v;

            agent_counter++;
        }
        rule_counter ++;
    }
    return t;
}