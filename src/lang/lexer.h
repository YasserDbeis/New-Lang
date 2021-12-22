/*
    File: lexer.h
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-21-2021
    Description: Declares the Lexer class. The Lexer performs lexical analysis on an input string
                 and stores the input as tokens in a private tokens vector. The parser can then
                 call the public functions: get_token, peek() in order to perform parsing.
*/

#pragma once

#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include "token.h"

class Lexer
{
private:
    std::unordered_set<std::string> terminals /* Set containing language key words */
        {";", "->", ",", "=", "bool", "int", "dec", "str", "void", "true", "false", "+", "-", "*", "/", ">", "<",
         ">=", "<=", "is", "and", "or", "not", "!", "{", "{", "(", ")", "while", "if", "elsif", "else", "func", "return"};

    std::unordered_map<std::string, TokenType> terminal_to_token_type =
        {
            {";", SEMICOLON},
            {"->", RIGHTARROW},
            {",", COMMA},
            {"=", EQUAL},
            {"bool", BOOL},
            {"int", INT},
            {"dec", DEC},
            {"str", STR},
            {"void", VOID},
            {"true", TRUE},
            {"false", FALSE},
            {"+", OPERATOR},
            {"-", OPERATOR},
            {"*", OPERATOR},
            {"/", OPERATOR},
            {">", OPERATOR},
            {"<", OPERATOR},
            {">=", OPERATOR},
            {"<=", OPERATOR},
            {"is", OPERATOR},
            {"and", OPERATOR},
            {"or", OPERATOR},
            {"not", OPERATOR},
            {"!", OPERATOR},
            {"{", LBRACE},
            {"}", RBRACE},
            {"(", LPAREN},
            {")", RPAREN},
            {"while", WHILE},
            {"if", IF},
            {"elsif", ELSIF},
            {"else", ELSE},
            {"func", FUNC},
            {"return", RETURN}};

    std::unordered_set<char> terminating_symbols{';', '(', '{', '-', ',', '=', '>', '<', '!', ')', '}', '+', '-', '/', '*'};

    /* Set up the token type vector according to the Enum defined in token.h */
    std::vector<std::string> token_type_names{"SEMICOLON", "RIGHTARROW", "COMMA", "EQUAL", "BOOL", "INT", "DEC", "STR", "VOID", "TRUE", "FALSE", "INT_NUM",
                                              "DEC_NUM", "STRING", "OPERATOR", "LBRACE", "RBRACE", "LPAREN", "RPAREN", "WHILE", "IF", "ELSIF", "ELSE",
                                              "FUNC", "RETURN", "ID", "END_OF_FILE"};

    std::vector<Token> tokens; /* Vector containing the tokens of the input received in constructor */
    int token_index;           /* Parsing purposes: Keeps track of what token is currently being parsed */
    int input_index;
    int line_number; /* Keep track of current line number for describing the token */

    void lexical_analysis(std::string input); /* Helper function - performs lexical analysis for the constructor */
    void add_token(std::string lexeme, TokenType type);
    void skip_whitespace(std::string input); /* Moves the token_index to the next valid start of a lexeme. Skipping whitespace */
    void consume_comment(std::string);       /* Moves the input_index to the index of the next line */
    void consume_number(std::string);        /* Consumes a number, moves input index onwards, and stores token of the num */
    void consume_string(std::string);        /* Consumes a string terminal, and consquently updates input_index */
    bool is_white_space(char);

public:
    Lexer(std::string input); /* Constructs lexer class. Reads input argument and does lexical analysis */
    ~Lexer();                 /* Destructor */

    std::string print_tokens(); /* Testing purposes: Returns a string representing tokens in input */

    Token get_token();      /* Parsing purposes: Consumes and returns the next token in the tokens vector */
    Token peek(int offset); /* Parsing purposes: Returns the token at the given offset in the tokens vector */
};
