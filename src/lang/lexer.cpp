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
        ErrorHandler::error(ErrorPhase::LEXICAL_ANALYSIS, ErrorType::SYNTAX_ERROR, "Input is empty", 1, MISSING_MAIN);
    }

    line_number = 1; /* Line number starts at 1 */
    token_index = 0; /* Parse from the first stored token! */
    input_index = 0; /* Start the input reading at index 0 */

    skip_whitespace(input); /* skip initial white space before beginning lexical analysis */

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
            else if (isdigit(curr_symbol))
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

                        add_token("->", TokenType::RIGHTARROW);
                        break;
                    }
                }
                case '<':
                {
                    if (next_symbol == '=')
                    {
                        input_index += 2;

                        add_token("<=", TokenType::OPERATOR);

                        break;
                    }
                }
                case '>':
                {
                    if (next_symbol == '=')
                    {
                        input_index += 2;

                        add_token(">=", TokenType::OPERATOR);

                        break;
                    }
                }
                case '!':
                {
                    if (next_symbol == '=')
                    {
                        input_index += 2;

                        add_token("!=", TokenType::OPERATOR);

                        break;
                    }
                }
                default:
                {
                    /* Consume the special case keyword symbol */

                    std::string lexeme = std::string(1, curr_symbol);
                    TokenType type = terminal_to_token_type[std::string(1, *(terminating_symbols.find(curr_symbol)))];

                    add_token(lexeme, type);

                    input_index++;
                }
                }
            }

            if (base_index != input_index)
            {
                skip_whitespace(input);
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
                token.type = TokenType::ID;
            }

            input_index++;
        }
        else if (terminating_symbols.find(curr_symbol) != terminating_symbols.end() || is_white_space(curr_symbol))
        {
            token.line_number = line_number;

            tokens.push_back(token);

            if (is_white_space(curr_symbol))
            {
                skip_whitespace(input);
            }

            base_index = input_index;
        }
        else
        {
            ErrorHandler::error(ErrorPhase::LEXICAL_ANALYSIS, ErrorType::SYNTAX_ERROR, "At token: " + token.lexeme, line_number, INVALID_TOKEN);
        }
    }

    add_token("END_OF_FILE", TokenType::END_OF_FILE);
}

/*
    Helper function - Cooks and pushes tokens to class-scoped storage vector
    Utilizes lexeme, token type, and line number to constructs a
    new token and adds it to the token storage vector.
*/
void Lexer::add_token(std::string lexeme, TokenType type)
{
    Token token;
    token.lexeme = lexeme;
    token.type = type;
    token.line_number = line_number; /* line_number is kept track as an instance var */

    tokens.push_back(token);
}

/*
    Helper function - Consumes whitespace
    Iterates the input_index to a non-empty start of a lexeme
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
    Helper function: Consumes comments

    Triggered by the sighting of a '~' char,
    this function consumes the rest of a line so
    as to treat it like a comment.
*/
void Lexer::consume_comment(std::string input)
{
    input_index++; /* skip ~ that triggers comment */
    while (input_index < input.length() && input[input_index] != '\n')
    {
        input_index++;
    }

    skip_whitespace(input);
}

/*
    Helper function: Consumes and adds INT_NUM or DEC_NUM token

    Initiation by a sighting of a digit, this function
    consumes the rest of a number-based token
    then adds the token to the token storage vector.
    Also validates the number formatting (max one decimal pt.)
*/
void Lexer::consume_number(std::string input)
{
    bool dec_used = false;
    bool token_added = false;

    bool zeroStart = input[input_index] == '0';

    std::string num = "";

    while (input_index < input.length())
    {

        if (dec_used == false && input[input_index] == '.')
        {
            dec_used = true;
            num += input[input_index];
        }
        else if (isdigit(input[input_index]))
        {
            num += input[input_index];
        }
        else if (dec_used && input[input_index] == '.')
        {
            ErrorHandler::error(ErrorPhase::LEXICAL_ANALYSIS, ErrorType::SYNTAX_ERROR, "Multiple decimal points near " + num + input[input_index], line_number, INVALID_NUM);
        }
        else
        {
            TokenType type = dec_used ? TokenType::DEC_NUM : TokenType::INT_NUM;

            if (type == TokenType::INT_NUM && zeroStart && num.length() > 1)
            {
                ErrorHandler::error(ErrorPhase::LEXICAL_ANALYSIS, ErrorType::SYNTAX_ERROR, "Integers may not start with a 0", line_number, INVALID_NUM);
            }

            add_token(num, type);

            token_added = true;

            break;
        }

        input_index++;
    }

    /* if number extends to end of input, add it to token list */
    if (input_index == input.length() && !token_added)
    {
        TokenType type = dec_used ? TokenType::DEC_NUM : TokenType::INT_NUM;

        add_token(num, type);
    }
}

/*
    Helper function: Consumes and adds STRING token

    Triggered by a sighting of an opening quote, this function
    consumes the rest of the STRING token within quotation marks
    then adds the token to the token storage vector.
*/
void Lexer::consume_string(std::string input)
{
    input_index++; /* skip opening quotation mark */

    std::string str = ""; /* build lexeme of STRING token in var called str */

    /* iterate and build STRING lexeme until closing quotation is hit */
    while (input_index < input.length() && input[input_index] != '\"' && input[input_index] != '\n')
    {
        str += input[input_index];
        input_index++;
    }

    if (input[input_index] == '\"') /* if iteration ended with end quotation, add token and move to next input char */
    {
        add_token(str, TokenType::STRING);
        input_index++;
    }
    else /* if end of file is hit before string closes, exit program */
    {
        ErrorHandler::error(ErrorPhase::LEXICAL_ANALYSIS, ErrorType::SYNTAX_ERROR, "Missing ending quote", line_number, INVALID_STRING);
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
        str += token_type_names[tok.type] + ", " + tok.lexeme + ", " + std::to_string(tok.line_number) + "\n";
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
        tok.type = TokenType::END_OF_FILE;
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