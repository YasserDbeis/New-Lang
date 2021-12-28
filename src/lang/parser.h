/*
    File: parser.h
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-24-2021
    Description: Header file for the parser object.
*/

#include "lexer.h"

class Parser
{

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
    void parse_func_call();
    void parse_arg_list();
    void parse_arg();
    void parse_type();

    Token expect(TokenType);

public:
    void parse_program();
    Parser(std::string program);
    ~Parser();
};