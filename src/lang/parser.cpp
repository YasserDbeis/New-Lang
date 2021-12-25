/*
    File: parser.cpp
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-24-2021
    Description: Implements the functionality of the parser class. Uses the lexer's
    getToken and peek to perform recursive descent parsing.
*/

#include "parser.h"

Parser::Parser(std::string program) : lexer(program)
{
}

Parser::~Parser()
{
}

Token Parser::expect(TokenType expected_type)
{
    Token tok = lexer.get_token();

    if (tok.type != expected_type)
    {
        std::string lexeme = tok.lexeme;
        int line_number = tok.line_number;
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + lexeme, line_number, INVALID_TOKEN);
    }

    return tok;
}

/*
    program -> def_list
*/
void Parser::parse_program()
{
    parse_def_list();
    expect(TokenType::END_OF_FILE);
}

/*
    def_list -> def def_list | def
*/
void Parser::parse_def_list()
{
    parse_def();

    Token tok = lexer.peek();
    if (tok.type == TokenType::INT || tok.type == TokenType::DEC || tok.type == TokenType::STR || tok.type == TokenType::BOOL || tok.type == TokenType::VOID || tok.type == TokenType::FUNC)
    {
        parse_def_list();
    }
    else
    {
        return;
    }
}

/*
    def -> var_decl | var_def | func_def
*/
void Parser::parse_def()
{
    Token tok_0 = lexer.peek();
    Token tok_2 = lexer.peek(2);

    if (tok_0.type == TokenType::FUNC)
    {
        parse_func_def();
    }
    else if (tok_0.type == TokenType::INT || tok_0.type == TokenType::DEC || tok_0.type == TokenType::STR || tok_0.type == TokenType::BOOL || tok_0.type == TokenType::VOID)
    {
        if (tok_2.type == TokenType::SEMICOLON)
        {
            parse_var_decl();
        }
        else
        {
            parse_var_def();
        }
    }
    else
    {
        return;
    }
}

/*
    def -> var_decl | var_def | func_def
*/