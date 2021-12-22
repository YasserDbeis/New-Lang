/*
    File: lexer.cpp
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-21-2021
    Description: Defines the functionality of the Lexer class, defined in lexer.h
                The constructor is the entry point of the lexical analysis.
                The public functions: get_token and peek allow the parser of the
                language to access acquired tokens from the input.
*/

#include "lexer.h"
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <stdio.h>

/*
    Constructor
    Input - input : string -> the code to be tokenized, parsed, and compiled

    Initializes the line_number, token_index, and input_index,
    then performs lexical analysis using a helper function
*/
Lexer::Lexer(std::string input)
{
    /* Ensure input is valid and reasonable */
    if (input.empty())
    {
        exit(EXIT_FAILURE); // TODO : custom exit function with appropriate logging for error logs
    }

    line_number = 1; /* Line number starts at 1 */
    token_index = 0; /* Parse from the first stored token! */
    input_index = 0; /* Start the input reading at index 0 */

    lexical_analysis(input);
}

/*
    Destructor
    Performs memory cleanup
*/
Lexer::~Lexer()
{
}

/*
    Lexical analyzer
    Input - input : string -> the code to be lexically analyzed

    Perform lexical analysis
*/
void Lexer::lexical_analysis(std::string input)
{
    Token token;

    int base_index = input_index;

    while (input_index < input.length())
    {
        char curr_symbol = input[input_index];

        if (base_index == input_index)
        {
            if (curr_symbol == '~')
            {
                consume_comment(input);
            }
            else if (isdigit(curr_symbol) && curr_symbol != '0')
            {
                consume_number(input);
            }
            else if (curr_symbol == '\"')
            {
                consume_string(input);
            }
            else if (terminating_symbols.find(curr_symbol) != terminating_symbols.end())
            {
                bool next_symbol_valid = input_index + 1 < input.length();
                char next_symbol = next_symbol_valid ? input[input_index + 1] : '\0';

                switch (curr_symbol)
                {
                case '-':
                {
                    if (next_symbol == '>')
                    {
                        input_index += 2;
                        token.lexeme = "->";
                        token.type = RIGHTARROW;
                        tokens.push_back(token);
                    }
                    else
                    {
                        printf("Invalid - usage");
                        exit(EXIT_FAILURE);
                    }
                }
                case '<':
                {
                    if (next_symbol == '=')
                    {
                        input_index += 2;
                        token.lexeme = "<=";
                        token.type = OPERATOR;
                        tokens.push_back(token);
                        break;
                    }
                }
                case '>':
                {
                    if (next_symbol == '=')
                    {
                        input_index += 2;
                        token.lexeme = ">=";
                        token.type = OPERATOR;
                        tokens.push_back(token);
                        break;
                    }
                }
                case '!':
                {
                    if (next_symbol == '=')
                    {
                        input_index += 2;
                        token.lexeme = "!=";
                        token.type = OPERATOR;
                        tokens.push_back(token);
                        break;
                    }
                }
                default:
                {
                    /* Consume the special case keyword symbol */
                    token.lexeme = curr_symbol;
                    token.type = terminal_to_token_type[std::string(1, *(terminating_symbols.find(curr_symbol)))];
                    tokens.push_back(token);
                    input_index++;
                }
                }
            }

            if (base_index != input_index)
            {
                base_index = input_index;
                continue;
            }
        }

        // STATE: Exploring some lexeme (possibly empty)
        // Guaranteed to be either an ID or Keyword
        // Termination of state: curr_symbol is ANYTHING BUT a alphabetical letter or digit or underscore
        // Initialization of state
        if (isdigit(curr_symbol) || isalpha(curr_symbol) || curr_symbol == '_')
        {
            int len = input_index - base_index + 1;
            std::string curr_lexeme = input.substr(base_index, len);

            token.lexeme = curr_lexeme;

            auto matched_token = terminals.find(curr_lexeme);

            if (matched_token != terminals.end())
            {
                token.type = terminal_to_token_type[*matched_token];
            }
            else
            {
                token.type = ID;
            }

            input_index++;
        }
        else if (terminating_symbols.find(curr_symbol) != terminating_symbols.end() || is_white_space(curr_symbol))
        {
            tokens.push_back(token);

            if (is_white_space(curr_symbol))
            {
                skip_whitespace(input);
            }

            base_index = input_index;
        }
        else
        {
            printf("INVALID TOKEN ERROR");
            exit(EXIT_FAILURE);
        }

        /*
            Keywords -> hashset
            string, ID, integers, decimal values, comments
            string -> "
            integers, decimal values -> have to start with a 1-9
        */
    }
}

/*
    Helper function - Consumes whitespace
    Iterates the input_index to a valid start of a lexeme
*/
void Lexer::skip_whitespace(std::string input)
{
    while (input_index < input.length() && is_white_space(input[input_index]))
    {
        if (input[input_index] == '\n')
            line_number++;

        input_index++;
    }
}

/*
    Builds and returns a string representation of the tokens vector
*/
std::string Lexer::print_tokens()
{
    std::string str = "";

    for (int i = 0; i < tokens.size(); i++)
    {
        Token tok = tokens.at(i);
        str += "{Type: " + token_type_names.at(tok.type) + ", Lexeme: " + tok.lexeme + ", line number: " + std::to_string(tok.line_number) + "}" + "\n";
    }

    return str;
}

/*
    Public function: Consumes and returns the token at token_index

    Stores the current token at token_index in the tokens vector, advances the
    token_index by 1, then returns the stored token
*/
Token Lexer::get_token()
{
    Token tok = peek(0);
    token_index++;
    return tok;
}

/*
    Public function: Returns the token at the token_index + offset value in the
    tokens vector
*/
Token Lexer::peek(int offset)
{
    /* If the requested token is outside the range of the input, return EOF */
    if (token_index + offset >= tokens.size())
    {
        Token tok;
        tok.type = END_OF_FILE;
        tok.lexeme = "";
        tok.line_number = line_number;
        return tok;
    }

    /* Otherwise, return the token at the offset index in the tokens vector */
    return tokens.at(token_index + offset);
}

bool Lexer::is_white_space(char curr_symbol)
{

    return curr_symbol == ' ' || curr_symbol == '\t' || curr_symbol == '\n';
}