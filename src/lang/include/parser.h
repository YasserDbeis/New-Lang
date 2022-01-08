/*
    File: parser.h
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-24-2021
    Description: Header file for the parser object.
*/

#include "lexer.h"
#include <unordered_set>

class Parser
{

public:
    void parse_program();
    Parser(std::string program);
    ~Parser();

private:
    Lexer lexer;

    void parse_def_list();
    void parse_def();
    void parse_var_decl();
    void parse_var_def();
    void parse_func_def();
    void parse_ret_type();
    void parse_param_list();
    void parse_param();
    void parse_body();
    void parse_stmt_list();
    void parse_stmt();
    void parse_assign_stmt();
    void parse_while_stmt();
    void parse_return_stmt();
    void parse_if_stmt();
    void parse_if_blk();
    void parse_elsif_blks();
    void parse_elsif_blk();
    void parse_else_blk();
    void parse_expr();
    void parse_term();
    void parse_factor();
    void parse_func_call();
    void parse_arg_list();
    void parse_arg();
    void parse_type();
    void parse_operator();
    void parse_leading_op();

    Token expect(TokenType);

    std::unordered_set<TokenType> operators /* Set containing language key words */
        {
            TokenType::OPERATOR_PLUS,
            TokenType::OPERATOR_MINUS,
            TokenType::OPERATOR_MULT,
            TokenType::OPERATOR_DIV,
            TokenType::OPERATOR_GT,
            TokenType::OPERATOR_LT,
            TokenType::OPERATOR_GEQ,
            TokenType::OPERATOR_LEQ,
            TokenType::OPERATOR_IS,
            TokenType::OPERATOR_AND,
            TokenType::OPERATOR_OR,
            TokenType::OPERATOR_NOT,
            TokenType::OPERATOR_XCL,
            TokenType::OPERATOR_NEQ,
        };

    std::unordered_set<TokenType> leading_operators{
        TokenType::OPERATOR_PLUS,
        TokenType::OPERATOR_MINUS,
        TokenType::OPERATOR_XCL,
        TokenType::OPERATOR_NOT};

    std::unordered_set<TokenType> types{
        TokenType::INT,
        TokenType::DEC,
        TokenType::STR,
        TokenType::BOOL,
        TokenType::VOID};

    std::unordered_set<TokenType> first_of_stmt{
        TokenType::INT,
        TokenType::DEC,
        TokenType::STR,
        TokenType::BOOL,
        TokenType::VOID,
        TokenType::ID,
        TokenType::IF,
        TokenType::WHILE,
        TokenType::RETURN};

    std::unordered_set<TokenType> first_of_expr{
        TokenType::ID,
        TokenType::LPAREN,
        TokenType::INT_NUM,
        TokenType::DEC_NUM,
        TokenType::STRING,
        TokenType::TRUE,
        TokenType::FALSE};
};