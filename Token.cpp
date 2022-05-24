//
// Created by Matthias Schedel on 17.05.22.
//

#include "Token.h"
map<string, string> operators_1=
        {
                {"and", "&"},
                { "or", "|" },
                { "xor", "^" },
                //{ 'negate', '!' },
                {"&", "and"},
                { "|", "or" },
                { "^", "xor" },
        };

map<string, string> parenthesis_1 =
        {
                { "open parenthesis", "(" },
                {"closed parenthesis", ")"},
                { "(" , "open parenthesis" },
                {")","closed parenthesis"}
        };

Token::Token(string token_string) {
    this->token_text = token_string;

    if (operators_1.contains(token_string))
    {
        this->type = operator_type;
        this->data = new Operator(token_string);
    }

    else if(parenthesis_1.contains((token_string)))
    {
        this->type = parenthesis_type;
        this->data = nullptr;
    }

    else
    {
        this->type = agent_type;
        this->data = new Agent(token_string);
    }
}

/*Token & Token::from_string(string token_string) {
    {
        Token *obj = new Token();

        obj->token_text = token_string;

        if (operators.contains(token_string))
        {
            obj->type = operator_type;
            obj->data = new Operator(token_string);
        }

        else if(parenthesis.contains((token_string)))
        {
            obj->type = parenthesis_type;
            obj->data = nullptr;
        }

        else
        {
            obj->type = agent_type;
            obj->data = new Agent(token_string);
        }
        return * obj;
    }
}*/

