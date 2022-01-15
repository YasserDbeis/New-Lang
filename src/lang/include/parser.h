/*
    File: parser.h
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-24-2021
    Description: Header file for the parser object.
*/

#pragma once

#include "../include/lexer.h"
#include "../include/nodes/nodes.h"
#include "../include/func_def_table.h"
#include "../include/value.h"
#include <unordered_set>
#include <vector>
#include <memory>

class Parser
{

public:
    void parse_program();

    Parser();
    Parser(std::string program);
    ~Parser();

    void print_instructions(std::vector<InstNode *> instructions);
    std::vector<InstNode *> get_global_instructions();

private:
    Lexer lexer;

    void parse_def_list();
    void parse_def();
    void parse_var_decl(bool is_global = false);
    void parse_var_def(bool is_global = false);
    void parse_func_def();
    Type parse_ret_type();
    void parse_param_list(std::vector<std::pair<Type, std::string>> &param_list);
    std::pair<Type, std::string> parse_param();
    void parse_body(bool scope_cooked = false);
    void parse_stmt_list();
    void parse_stmt();
    void parse_assign_stmt(Type type, bool is_global = false);
    void parse_while_stmt();
    void parse_return_stmt();
    void parse_if_stmt();
    void parse_if_blk(std::vector<int> &jmp_indices);
    void parse_elsif_blks(std::vector<int> &jmp_indices);
    void parse_elsif_blk(std::vector<int> &jmp_indices);
    void parse_else_blk();
    void parse_expr(std::vector<ExprNode *> &expr_list);
    void parse_term(std::vector<ExprNode *> &expr_list);
    void parse_factor(std::vector<ExprNode *> &expr_list);
    void parse_func_stmt_call();
    void parse_func_expr_call(std::vector<ExprNode *> &expr_list);
    void parse_arg_list(std::vector<Expression> &expression_list);
    Type parse_type();
    void parse_operator(std::vector<ExprNode *> &expr_list);
    Token parse_leading_op(std::vector<ExprNode *> &expr_list);

    std::vector<InstNode *> func_instructions;
    std::vector<InstNode *> global_instructions;

    int global_count = 0;

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
            TokenType::OPERATOR_XOR,
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

    std::unordered_map<TokenType, Type> token_to_type =
        {
            {TokenType::BOOL, Type::Bool},
            {TokenType::TRUE, Type::Bool},
            {TokenType::FALSE, Type::Bool},
            {TokenType::STR, Type::String},
            {TokenType::STRING, Type::String},
            {TokenType::DEC, Type::Dec},
            {TokenType::DEC_NUM, Type::Dec},
            {TokenType::INT, Type::Int},
            {TokenType::INT_NUM, Type::Int},
            {TokenType::VOID, Type::Void}};

    std::unordered_map<TokenType, OperatorType> operator_token_to_type =
        {
            {TokenType::OPERATOR_PLUS, OperatorType::PLUS},
            {TokenType::OPERATOR_MINUS, OperatorType::MINUS},
            {TokenType::OPERATOR_MULT, OperatorType::MULT},
            {TokenType::OPERATOR_DIV, OperatorType::DIV},
            {TokenType::OPERATOR_GT, OperatorType::GT},
            {TokenType::OPERATOR_LT, OperatorType::LT},
            {TokenType::OPERATOR_GEQ, OperatorType::GEQ},
            {TokenType::OPERATOR_LEQ, OperatorType::LEQ},
            {TokenType::OPERATOR_IS, OperatorType::IS},
            {TokenType::OPERATOR_AND, OperatorType::AND},
            {TokenType::OPERATOR_OR, OperatorType::OR},
            {TokenType::OPERATOR_XOR, OperatorType::XOR},
            {TokenType::OPERATOR_NEQ, OperatorType::NEQ}};
};