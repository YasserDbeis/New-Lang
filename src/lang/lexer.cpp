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


/* 
    Constructor
    Input - input : string -> the code to be tokenized, parsed, and compiled

    Initializes the line_number, token_index, and input_index, then performs lexical analysis
    using a helper function
*/
Lexer::Lexer(std::string input)
{
    /* Ensure input is valid and reasonable */
    if (input.empty())
    {
        exit (EXIT_FAILURE);   // TODO : custom exit function with appropriate logging for error logs
    }

    line_number = 1;    /* Line number starts at 1 */
    token_index = 0;    /* Parse from the first stored token! */
    input_index = 0;    /* Start the input reading at index 0 */

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

}


/* 
    Helper function - Consumes whitespace
    Iterates the input_index to a valid start of a lexeme
*/
void Lexer::skip_whitespace()
{

}


/* 
    Builds and returns a string representation of the tokens vector
*/
std::string Lexer::print_tokens()
{
    std::string str = "";

    for (int i = 0; i < tokens.size(); i++)
    {
        str += tokens.at(i).lexeme;
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
    return Token(); //temp
}


/*
    Public function: Returns the token at the token_index + offset value in the 
    tokens vector
*/
Token Lexer::peek(int offset) 
{
    return Token();  // temp    
}