/*
    File: lexer.cpp
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-21-2021
    Description: Defines the functionality of the Lexer class, defined in lexer.h
                The constructor is the entry point of the lexical analysis.
                The public functions: get_token and peek allow the parser of the
                language to access acquired tokens from the input.
*/

#include "../include/lexer.h"
#include <stdlib.h>
#include <ctype.h>
#include <iostream>
#include <stdio.h>

Lexer::Lexer()
{
}

Lexer::Lexer(std::string input)
{
    /* Ensure input is valid and reasonable */
    if (input.empty())
    {
        ErrorHandler::error(ErrorPhase::LEXICAL_ANALYSIS, ErrorType::SYNTAX_ERROR, "Input is empty", 1, MISSING_MAIN);
    }

    source = input;
    scan_tokens();
}

void Lexer::scan_tokens()
{
    while (!is_at_end())
    {
        scan_token();
        start_ix = curr_ix;
    }

    add_token(TokenType::END_OF_FILE);
}

bool Lexer::is_at_end()
{
    return curr_ix >= source.length();
}

void Lexer::scan_token()
{
    char c = advance();

    // Add the appropriate token based on the current character, c (the start to the token)
    switch (c) 
    {
        case '(': add_token(TokenType::LPAREN); break;
        case ')': add_token(TokenType::RPAREN); break;
        case '{': add_token(TokenType::LBRACE); break;
        case '}': add_token(TokenType::RBRACE); break;
        case ',': add_token(TokenType::COMMA); break;
        case ';': add_token(TokenType::SEMICOLON); break;
        case '=': add_token(TokenType::EQUAL); break;
        case '*': add_token(TokenType::OPERATOR_MULT); break;
        case '/': add_token(TokenType::OPERATOR_DIV); break;
        case '+': add_token(TokenType::OPERATOR_PLUS); break;
        case '-':
            add_token(match('>') ? TokenType::RIGHTARROW : TokenType::OPERATOR_MINUS);
            break;
        case '>':
            add_token(match('=') ? TokenType::OPERATOR_GEQ : TokenType::OPERATOR_GT);
            break;
        case '<':
            add_token(match('=') ? TokenType::OPERATOR_LEQ : TokenType::OPERATOR_LT);
            break;
        case '!':
            add_token(match('=') ? TokenType::OPERATOR_NEQ : TokenType::OPERATOR_XCL);
            break;
        case '~': consume_comment(); break;
        case '"': consume_string(); break;
        case ' ':   
        case '\t':
        case '\r':
            break; // skip whitespace
        case '\n':
            line_number++;
            break;
        default:
            if (is_alpha(c))
                consume_id();
            else if (is_digit(c))
                consume_number();
            else if (c == '.')
                consume_decimal_points();
            else    
            {
                int len_curr_token = curr_ix - start_ix;
                std::string token_of_error = source.substr(start_ix, len_curr_token);
                ErrorHandler::error(ErrorPhase::LEXICAL_ANALYSIS, ErrorType::SYNTAX_ERROR, "At token: " + token_of_error, line_number, INVALID_TOKEN);
            }
            break;
    }
}

void Lexer::add_token(TokenType type)
{
    int len_of_lexeme = curr_ix - start_ix;

    Token token;
    token.type = type;
    token.line_number = line_number;

    /* The lexeme can be found between the start_ix and curr_ix. We can use the substr method to 
        extract the lexeme */
    
    // Special case: END_OF_FILE. We'll manually set it to END_OF_FILE
    if (type == TokenType::END_OF_FILE)
        token.lexeme = "END_OF_FILE";
    else
        token.lexeme = source.substr(start_ix, len_of_lexeme); 

    tokens.push_back(token);
}

/* Consumes the current character we are scanning in the source string.
   curr_ix is our index pointer, and we increment it so that we advance in our scanning process
*/
char Lexer::advance() 
{
    char curr_char = source[curr_ix];
    curr_ix++;
    return curr_char;
}

char Lexer::peek_char()
{
    if (is_at_end())
        return '\0';
    else
        return source[curr_ix];
}

char Lexer::get_prev_char()
{
    if (curr_ix == 0)
        return '\0';
    else   
        return source[curr_ix - 1];
}

bool Lexer::match(char expected_type)
{
    if (is_at_end())
        return false;
    if (peek_char() != expected_type)
        return false;

    advance();
    return true;
}

void Lexer::consume_comment()
{
    while (!is_at_end() && peek_char() != '\n')
        advance();
}

// Consume the string. The left " is already consumed. Consume up to and including the next found "
void Lexer::consume_string()
{
    while (!is_at_end() && peek_char() != '"' && peek_char() != '\n')
        advance();
    
    if (is_at_end() || peek_char() == '\n')    // EXIT with error code!
        ErrorHandler::error(ErrorPhase::LEXICAL_ANALYSIS, ErrorType::SYNTAX_ERROR, "Missing ending quote", line_number, INVALID_STRING);
 


    advance(); // Consume the right "

    // Instead of calling add_token. We're going to do it here manually. Reason: We don't want to include the quotation marks in the lexeme
    const int num_quotation_marks = 2;
    int len_of_string = curr_ix - start_ix - num_quotation_marks;
    int start_of_str_content = start_ix + 1;
    Token token;
    token.type = TokenType::STRING;
    token.lexeme = source.substr(start_of_str_content, len_of_string);
    token.line_number = line_number;

    tokens.push_back(token);
}

void Lexer::consume_id()
{
    while (!is_at_end() && is_alphanumeric(peek_char()))
        advance();
    
    int len_id = curr_ix - start_ix;
    std::string id_lexeme = source.substr(start_ix, len_id);
    TokenType id_type = get_id_type(id_lexeme);
    
    add_token(id_type);
}

/* The number to be scanned can either be a decimal or integer. 
    If there's a '.' in the number, then it's a decimal. Otherwise it's an integer
*/
void Lexer::consume_number()
{
    bool dot_found = false;
    char first_digit = get_prev_char();  // The previous character is the first digit of the number (since we already advanced from c)

    while (!is_at_end() && is_digit(peek_char()))
        advance();
    
    if (peek_char() == '.')
    {
       dot_found = true;
       advance();
    }
    
    while (!is_at_end() && is_digit(peek_char()))
        advance();
    
    // As numbers are space separated, if there's a '.' next, then we consider it part of this current number we're scanning and 
    // not the beginning of the next number. So, we need to check for it here
    if (peek_char() == '.')
    {
        int len_curr_num = curr_ix - start_ix + 1; // + 1 to include the extra '.'
        std::string num_lexeme = source.substr(start_ix, len_curr_num);
        ErrorHandler::error(ErrorPhase::LEXICAL_ANALYSIS, ErrorType::SYNTAX_ERROR, "Multiple decimal points near " + num_lexeme, line_number, INVALID_NUM);
    }

    if (dot_found)
    {
        add_token(TokenType::DEC_NUM);
    }
    else
    {
        // Special case. Integers may not start with a 0 (except the integer 0 itself)
        int num_digits = curr_ix - start_ix;
        if (first_digit == '0' && num_digits > 1)
            ErrorHandler::error(ErrorPhase::LEXICAL_ANALYSIS, ErrorType::SYNTAX_ERROR, "Integers may not start with a 0", line_number, INVALID_NUM);
        else
            add_token(TokenType::INT_NUM);
    }
}

// Scans a dec that started with a '.' (the '.' already being consumed)
void Lexer::consume_decimal_points()
{
    int num_decimal_points = 0;

    while (!is_at_end() && is_digit(peek_char()))
    {
        advance();
        ++num_decimal_points;
    }

    if (num_decimal_points == 0)
        ErrorHandler::error(ErrorPhase::LEXICAL_ANALYSIS, ErrorType::SYNTAX_ERROR, "'.' is not a valid number", line_number, INVALID_NUM);

    add_token(TokenType::DEC_NUM);
}

bool Lexer::is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') ||
           (c >= 'A' && c <= 'Z') ||
            c == '_';
}

bool Lexer::is_digit(char c)
{
    return c >= '0' && c <= '9';
}

bool Lexer::is_alphanumeric(char c)
{
    return is_alpha(c) || is_digit(c);
}

// Search the keywords map for the id_lexeme string. Return its mapped value if found, otherwise ID
TokenType Lexer::get_id_type(std::string id_lexeme) 
{
    auto search = keywords.find(id_lexeme);
    if (search != keywords.end()) // If we found it in the keywords map
    {
        TokenType mapped_type = search->second; // search->second is the mapped value of the id_lexeme in the map
        return mapped_type;
    } 
    else
    {
        return TokenType::ID;
    }
}

Token Lexer::get_token()
{
    Token token = peek(0);
    token_index++;          // Consume the current token
    return token;
}

Token Lexer::peek(int offset)
{
    /* If the requested token is outside the range of the input, return EOF */
    if (token_index + offset >= tokens.size())
    {
        Token token;
        token.type = TokenType::END_OF_FILE;
        token.lexeme = "";
        token.line_number = line_number;
        return token;
    }

    /* Otherwise, return the token at the offset index in the tokens vector */
    return tokens.at(token_index + offset);
}

std::string Lexer::get_token_name(TokenType type)
{
    return token_type_names[type];
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