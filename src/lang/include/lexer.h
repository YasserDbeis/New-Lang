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
#include "error_handler.h"

class Lexer
{
public:
    Lexer();
    Lexer(std::string input); /* Constructs lexer class. Reads input argument and does lexical analysis */

    Token get_token();          /* Parsing purposes: Consumes and returns the next token in the tokens vector */
    Token peek(int offset = 0); /* Parsing purposes: Returns the token at the given offset in the tokens vector */

    std::string get_token_name(TokenType); /* Gets the stringified name of a token type */
    std::string print_tokens();            /* Testing purposes: Returns a string representing tokens in input */

private:
    std::string source;        /* store the source code to perform lexical analysis on in a string */
    std::vector<Token> tokens; /* Vector containing the tokens of the input received in constructor */

    int line_number = 1; /* current line number throughout lexical analysis process */
    int start_ix = 0;    /* starting index in the source string we start a token scan */
    int curr_ix = 0;     /* current index in the source string of which we are scanning */
    int token_index = 0; /* current index in the tokens vector for public api token peeking and getting */

    std::unordered_map<std::string, TokenType> keywords =
        {
            {"bool", TokenType::BOOL},
            {"int", TokenType::INT},
            {"dec", TokenType::DEC},
            {"str", TokenType::STR},
            {"void", TokenType::VOID},
            {"true", TokenType::TRUE},
            {"false", TokenType::FALSE},
            {"is", TokenType::OPERATOR_IS},
            {"and", TokenType::OPERATOR_AND},
            {"or", TokenType::OPERATOR_OR},
            {"not", TokenType::OPERATOR_NOT},
            {"xor", TokenType::OPERATOR_XOR},
            {"while", TokenType::WHILE},
            {"if", TokenType::IF},
            {"elsif", TokenType::ELSIF},
            {"else", TokenType::ELSE},
            {"func", TokenType::FUNC},
            {"return", TokenType::RETURN}};

    void scan_tokens();             /* Scans through the entire source array and adds all found tokens to the tokens vector */
    void scan_token();              /* Add the token starting at start_ix in the source string */
    void add_token(TokenType type); /* Adds the token of the given type to the tokens vector. The lexeme is the substring from start_ix to curr_ix) */
    bool is_at_end();               /* Checks if we are at the end of the source string (used to determine when to stop scanning) */
    char advance();                 /* Returns the character at the curr_ix of the source string and increments curr_ix */
    char peek_char();               /* Peeks at the character found at curr_ix of the source string and returns it */
    char get_prev_char();           /* Peeks at the previous character (curr_ix - 1) */
    bool match(char expected_char); /* Checks if the expected char is located next in the source string. If it is, then we advance and consume the expected char */
    void consume_comment();         /* consume the comment (up to the new line). Do not add any tokens */
    void consume_string();          /* Consume the string from the left and right quotation marks (left is already consumed) */
    void consume_id();              /* Consume the identifier. The id can either be an ID or a keyword */
    void consume_number();          /* Consume a number, either integer or decimal (guaranteed to not start with '.') */
    void consume_decimal_points();  /* Consume a decimal starting with a '.' */

    TokenType get_id_type(std::string); /* Given the lexeme of an identifier. Return its type. (keyword if recognized, else ID) */
    bool is_alpha(char c);
    bool is_digit(char c);
    bool is_alphanumeric(char c);

    // Maps and sets for other non-lexical-analysis reasons
    std::unordered_set<std::string> terminals /* Set containing language key words */
        {";", "->", ",", "=", "bool", "int", "dec", "str", "void", "true", "false", "+", "-", "*", "/", ">", "<",
         ">=", "<=", "is", "and", "or", "not", "xor", "!", "{", "{", "(", ")", "while", "if", "elsif", "else", "func", "return"};

    std::unordered_map<std::string, TokenType> terminal_to_token_type =
        {
            {";", TokenType::SEMICOLON},
            {"->", TokenType::RIGHTARROW},
            {",", TokenType::COMMA},
            {"=", TokenType::EQUAL},
            {"bool", TokenType::BOOL},
            {"int", TokenType::INT},
            {"dec", TokenType::DEC},
            {"str", TokenType::STR},
            {"void", TokenType::VOID},
            {"true", TokenType::TRUE},
            {"false", TokenType::FALSE},
            {"+", TokenType::OPERATOR_PLUS},
            {"-", TokenType::OPERATOR_MINUS},
            {"*", TokenType::OPERATOR_MULT},
            {"/", TokenType::OPERATOR_DIV},
            {">", TokenType::OPERATOR_GT},
            {"<", TokenType::OPERATOR_LT},
            {">=", TokenType::OPERATOR_GEQ},
            {"<=", TokenType::OPERATOR_LEQ},
            {"is", TokenType::OPERATOR_IS},
            {"and", TokenType::OPERATOR_AND},
            {"or", TokenType::OPERATOR_OR},
            {"not", TokenType::OPERATOR_NOT},
            {"xor", TokenType::OPERATOR_XOR},
            {"!=", TokenType::OPERATOR_NEQ},
            {"!", TokenType::OPERATOR_XCL},
            {"{", TokenType::LBRACE},
            {"}", TokenType::RBRACE},
            {"(", TokenType::LPAREN},
            {")", TokenType::RPAREN},
            {"while", TokenType::WHILE},
            {"if", TokenType::IF},
            {"elsif", TokenType::ELSIF},
            {"else", TokenType::ELSE},
            {"func", TokenType::FUNC},
            {"return", TokenType::RETURN}};

    std::unordered_set<char> terminating_symbols{';', '(', '{', '-', ',', '=', '>', '<', '!', ')', '}', '+', '-', '/', '*'};

    /* Set up the token type map according to the Enum defined in token.h */
    std::unordered_map<TokenType, std::string> token_type_names{{{TokenType::SEMICOLON, "SEMICOLON"},
                                                                 {TokenType::RIGHTARROW, "RIGHTARROW"},
                                                                 {TokenType::COMMA, "COMMA"},
                                                                 {TokenType::EQUAL, "EQUAL"},
                                                                 {TokenType::BOOL, "BOOL"},
                                                                 {TokenType::INT, "INT"},
                                                                 {TokenType::DEC, "DEC"},
                                                                 {TokenType::STR, "STR"},
                                                                 {TokenType::VOID, "VOID"},
                                                                 {TokenType::TRUE, "TRUE"},
                                                                 {TokenType::FALSE, "FALSE"},
                                                                 {TokenType::INT_NUM, "INT_NUM"},
                                                                 {TokenType::DEC_NUM, "DEC_NUM"},
                                                                 {TokenType::STRING, "STRING"},
                                                                 {TokenType::OPERATOR_PLUS, "OPERATOR_PLUS"},
                                                                 {TokenType::OPERATOR_MINUS, "OPERATOR_MINUS"},
                                                                 {TokenType::OPERATOR_MULT, "OPERATOR_MULT"},
                                                                 {TokenType::OPERATOR_DIV, "OPERATOR_DIV"},
                                                                 {TokenType::OPERATOR_GT, "OPERATOR_GT"},
                                                                 {TokenType::OPERATOR_LT, "OPERATOR_LT"},
                                                                 {TokenType::OPERATOR_GEQ, "OPERATOR_GEQ"},
                                                                 {TokenType::OPERATOR_LEQ, "OPERATOR_LEQ"},
                                                                 {TokenType::OPERATOR_IS, "OPERATOR_IS"},
                                                                 {TokenType::OPERATOR_AND, "OPERATOR_AND"},
                                                                 {TokenType::OPERATOR_OR, "OPERATOR_OR"},
                                                                 {TokenType::OPERATOR_NOT, "OPERATOR_NOT"},
                                                                 {TokenType::OPERATOR_XOR, "OPERATOR_XOR"},
                                                                 {TokenType::OPERATOR_XCL, "OPERATOR_XCL"},
                                                                 {TokenType::OPERATOR_NEQ, "OPERATOR_NEQ"},
                                                                 {TokenType::LBRACE, "LBRACE"},
                                                                 {TokenType::RBRACE, "RBRACE"},
                                                                 {TokenType::LPAREN, "LPAREN"},
                                                                 {TokenType::RPAREN, "RPAREN"},
                                                                 {TokenType::WHILE, "WHILE"},
                                                                 {TokenType::IF, "IF"},
                                                                 {TokenType::ELSIF, "ELSIF"},
                                                                 {TokenType::ELSE, "ELSE"},
                                                                 {TokenType::FUNC, "FUNC"},
                                                                 {TokenType::RETURN, "RETURN"},
                                                                 {TokenType::ID, "ID"},
                                                                 {TokenType::END_OF_FILE, "END_OF_FILE"}}};
};