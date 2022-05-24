//
// Created by Matthias Schedel on 17.05.22.
//

#include "ExpressionTree.h"
#include "Token.h"
#include "string"

Node* ExpressionTree::build_expression_tree(vector<Token *> tokens) {

    map<string, int> operator_precedences {
            {"(", 1},
            {"^", 2},
            {"|", 3},
            {"&", 4},
            {"!", 5}
    };

    vector<Token *> operator_stack;
    vector<Node*> node_stack;

    for(Token* token : tokens)
    {
        if(token->type == agent_type)
        {
            node_stack.push_back(token->data);
        }
        else if(token->type == operator_type || token->type == parenthesis_type)
        {
            if(token->token_text == "(")
            {
                operator_stack.push_back(token);
            }
            else if(token->token_text == ")")
            {
                while(operator_stack.size() != 0 && operator_stack.back()->token_text != "(")
                {
                    Operator* op = dynamic_cast<Operator*>(operator_stack.back()->data);
                    operator_stack.pop_back();

                    op->right = node_stack.back();
                    node_stack.pop_back();
                    op->left = node_stack.back();
                    node_stack.pop_back();

                    node_stack.push_back(op);
                }
                operator_stack.pop_back(); // remove left parenthesis from stack
            }
            else
            {
                while(operator_stack.size() != 0 &&
                operator_precedences[operator_stack.back()->token_text]
                >= operator_precedences[token->token_text])
                {
                    Operator* op = dynamic_cast<Operator*>(operator_stack.back()->data);
                    operator_stack.pop_back();

                    op->right = node_stack.back();
                    node_stack.pop_back();
                    op->left = node_stack.back();
                    node_stack.pop_back();

                    node_stack.push_back(op);
                }
                operator_stack.push_back(token);
            }
        }
    }
    while(node_stack.size() > 1)
    {
        Operator* op = dynamic_cast<Operator*>(operator_stack.back()->data);
        operator_stack.pop_back();

        op->right = node_stack.back();
        node_stack.pop_back();

        op->left = node_stack.back();
        node_stack.pop_back();

        node_stack.push_back(op);
    }
    Node* root = node_stack.back();
    node_stack.pop_back();
    return root;
}

map<string, string> operators=
        {
                {"and", "&"},
                { "or", "|" },
                { "xor", "^" },
                //{ 'negate', '!' },
                {"&", "and"},
                { "|", "or" },
                { "^", "xor" },
        };

map<string, string> parenthesis =
        {
                { "open parenthesis", "(" },
                {"closed parenthesis", ")"},
                { "(" , "open parenthesis" },
                {")","closed parenthesis"}
        };

vector<Token *> ExpressionTree::tokenize(string input_string) {
    vector<string> string_tokens;
    int current_char_pos = 0;

    while(current_char_pos < input_string.size())
    {
        /*string_tokens.push_back(string s(1,input_string[current_char_pos]));*/
        string_tokens.push_back(string(1, input_string[current_char_pos]));

        if(!operators.contains(string(1, input_string[current_char_pos]))
        && !parenthesis.contains(string(1, input_string[current_char_pos])))
        {
            current_char_pos ++;
            while(current_char_pos < input_string.size() &&
            !operators.contains(string(1, input_string[current_char_pos]))
            && !parenthesis.contains(string(1, input_string[current_char_pos])))
            {
                string_tokens.back().push_back(input_string[current_char_pos]);
                current_char_pos ++;
            }
        }
        else
        {
            current_char_pos ++;
        }

    }

    vector<Token*> tokens;
    for(string string_token : string_tokens)
    {
        tokens.push_back(new Token(string_token));
    }

    return tokens;
}

Node *ExpressionTree::expression_tree_from_string(string input_string) {
    vector<Token*> tokens = tokenize(input_string);
    Node * root = build_expression_tree(tokens);
    root->GetAgentDesc();
    return  root;
}


