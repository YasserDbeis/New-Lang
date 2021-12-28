/*
    File: parser.cpp
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-24-2021
    Description: Implements the functionality of the parser class. Uses the lexer's
    getToken and peek to perform recursive descent parsing.
*/

#include "parser.h"
#include <iostream>

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
        std::cout << "EXPECTED: " << lexer.get_token_name(expected_type) << std::endl;
        std::cout << "RECEIVED: " << lexer.get_token_name(tok.type) << std::endl;
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
    else if (tok.type == TokenType::END_OF_FILE)
    {
        return;
    } 
    else 
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_DEF);
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
        else if (tok_2.type == TokenType::EQUAL)
        {
            parse_var_def();
        } 
        else 
        {
            ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_2.lexeme, tok_2.line_number, INVALID_VAR_DEF);
        }
    }
    else
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_0.lexeme, tok_0.line_number, INVALID_DEF);
    }
}

/*
    var_dec -> type ID SEMICOLON
*/
void Parser::parse_var_decl()
{
    parse_type();
    expect(TokenType::ID);
    expect(TokenType::SEMICOLON);
}

/*
    var_def -> type assign_stmt
*/
void Parser::parse_var_def()
{
    parse_type();
    parse_assign_stmt();
}

/*
    func_def -> FUNC ID LPAREN param_list RPAREN ret_type body
    func_def -> FUNC ID LPAREN RPAREN ret_type body
*/
void Parser::parse_func_def()
{
    expect(TokenType::FUNC);
    expect(TokenType::ID);
    expect(TokenType::LPAREN);
    
    Token tok = lexer.peek();
    if (tok.type == TokenType::INT || tok.type == TokenType::DEC || tok.type == TokenType::STR || tok.type == TokenType::BOOL || tok.type == TokenType::VOID)
    {
        parse_param_list();
    } 
    else if(tok.type != TokenType::RPAREN) 
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_PARAM);
    }
    expect(TokenType::RPAREN);
    parse_ret_type();
    parse_body();
}

/*
    ret_type -> RIGHTARROW type | epsilon
*/
void Parser::parse_ret_type()
{
    Token tok = lexer.peek();

    if (tok.type == TokenType::RIGHTARROW)
    {
        expect(TokenType::RIGHTARROW);
        parse_type();
    }
    else if (tok.type == TokenType::LBRACE)     // follow ret_type is body which always has LBRACE start
    {
        return;
    }
    else 
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_RET_TYPE);
    }
}

/*
    param_list -> param COMMA param_list | param
*/
void Parser::parse_param_list()
{
    parse_param();
    
    Token tok = lexer.peek();
    if (tok.type == TokenType::COMMA)
    {
        expect(TokenType::COMMA);
        parse_param_list();
    }
    else if(tok.type == TokenType::RPAREN)
    {
        return;
    }
    else 
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_PARAM);
    }
}

/*
    param -> type ID
*/
void Parser::parse_param()
{
    parse_type();
    expect(TokenType::ID);
}

/*
    body -> LBRACE stmt_list RBRACE | LBRACE RBRACE
*/
void Parser::parse_body() 
{
    expect(TokenType::LBRACE);
    Token tok = lexer.peek();
    
    if (tok.type == TokenType::INT ||    // var declaration or definition
        tok.type == TokenType::DEC ||
        tok.type == TokenType::STR || 
        tok.type == TokenType::BOOL || 
        tok.type == TokenType::VOID ||
        tok.type == TokenType::ID ||
        tok.type == TokenType::IF ||
        tok.type == TokenType::WHILE ||
        tok.type == TokenType::RETURN
    )
    {
        parse_stmt_list();
    }

    expect(TokenType::RBRACE);
}

/*
    stmt_list -> stmt stmt_list | stmt
*/
void Parser::parse_stmt_list() 
{
    parse_stmt();

    Token tok = lexer.peek();

    if(tok.type == TokenType::INT || 
        tok.type == TokenType::DEC || 
        tok.type == TokenType::STR || 
        tok.type == TokenType::BOOL || 
        tok.type == TokenType::VOID ||
        tok.type == TokenType::ID ||
        tok.type == TokenType::WHILE ||
        tok.type == TokenType::IF ||
        tok.type == TokenType::RETURN)
    {
        parse_stmt_list();
    }
    else if (tok.type == TokenType::RBRACE)
    {
        return;
    }
    else 
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_STMT_LIST);
    }
}

/*
    stmt -> var_decl | var_def | assign_stmt | while_stmt | if_stmt | func_call SEMICOLON
*/
void Parser::parse_stmt()
{
    Token tok_0 = lexer.peek();
    Token tok_1 = lexer.peek(1);
    Token tok_2 = lexer.peek(2);
    
    if (tok_0.type == TokenType::WHILE)
    {
        parse_while_stmt();
    }
    else if (tok_0.type == TokenType::IF)
    {
        parse_if_stmt();
    }
    else if (tok_0.type == TokenType::RETURN)
    {
        parse_return_stmt();
    }
    else if (tok_0.type == TokenType::ID)       // assign_stmt or func_call
    {
        if (tok_1.type == TokenType::EQUAL)
        {
            parse_assign_stmt();
        }
        else if (tok_1.type == TokenType::LPAREN)
        {
            parse_func_call();
            expect(TokenType::SEMICOLON);
        }
        else 
        {
            ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_1.lexeme, tok_1.line_number, INVALID_STMT);
        }
    }
    else if (tok_0.type == TokenType::INT ||    // var declaration or definition
            tok_0.type == TokenType::DEC ||
            tok_0.type == TokenType::STR || 
            tok_0.type == TokenType::BOOL || 
            tok_0.type == TokenType::VOID)
    {
        if (tok_2.type == TokenType::SEMICOLON)
        {
            parse_var_decl();
        }
        else if (tok_2.type == TokenType::EQUAL)
        {
            parse_var_def();
        }
        else 
        {
            ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_2.lexeme, tok_2.line_number, INVALID_STMT);
        }
    }
    else
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_0.lexeme, tok_0.line_number, INVALID_STMT);
    }
}

/*
    assign_stmt -> ID EQUAL expr SEMICOLON
*/
void Parser::parse_assign_stmt() 
{
    expect(TokenType::ID);
    expect(TokenType::EQUAL);
    parse_expr();
    expect(TokenType::SEMICOLON);
}

/*
    while_stmt -> WHILE LPAREN expr RPAREN body
*/
void Parser::parse_while_stmt() 
{
    expect(TokenType::WHILE);
    expect(TokenType::LPAREN);
    parse_expr();
    expect(TokenType::RPAREN);
    parse_body();
}

/*
    return_stmt -> RETURN expr SEMICOLON | RETURN SEMICOLON
*/
void Parser::parse_return_stmt()
{
    expect(TokenType::RETURN);

    Token tok = lexer.peek();

    if (tok.type == TokenType::LPAREN ||
    tok.type == TokenType::ID ||
    tok.type == TokenType::INT_NUM ||
    tok.type == TokenType::DEC_NUM ||
    tok.type == TokenType::STRING ||
    tok.type == TokenType::TRUE ||
    tok.type == TokenType::FALSE)
    {
        parse_expr();
    }
    expect(TokenType::SEMICOLON);
}

/*
    if_stmt -> if_blk | if_blk else_blk | if_blk elseifs_blks | if_blk elseifs_blks else_blk
*/
void Parser::parse_if_stmt()
{
    parse_if_blk();
    
    Token tok_0 = lexer.peek();
    
    if(tok_0.type == TokenType::ELSE)
    {
        parse_else_blk();
    }
    else if(tok_0.type == TokenType::ELSIF)
    {
        parse_elsif_blks();

        Token tok_1 = lexer.peek();
        if (tok_1.type == TokenType::ELSE)
        {
            parse_else_blk();
        }
        else if (tok_1.type == TokenType::INT ||    // var declaration or definition
                tok_1.type == TokenType::DEC ||
                tok_1.type == TokenType::STR || 
                tok_1.type == TokenType::BOOL || 
                tok_1.type == TokenType::VOID ||
                tok_1.type == TokenType::ID ||
                tok_1.type == TokenType::IF ||
                tok_1.type == TokenType::WHILE ||
                tok_1.type == TokenType::RBRACE ||
                tok_1.type == TokenType::RETURN
        )
        {
            return;
        }
        else 
        {
            ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_1.lexeme, tok_1.line_number, INVALID_ALT_COND);
        }
    }
    else if (tok_0.type == TokenType::INT ||    // var declaration or definition
                tok_0.type == TokenType::DEC ||
                tok_0.type == TokenType::STR || 
                tok_0.type == TokenType::BOOL || 
                tok_0.type == TokenType::VOID ||
                tok_0.type == TokenType::ID ||
                tok_0.type == TokenType::IF ||
                tok_0.type == TokenType::WHILE ||
                tok_0.type == TokenType::RBRACE ||
                tok_0.type == TokenType::RETURN
    )
    {
        return;
    }
    else 
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_0.lexeme, tok_0.line_number, INVALID_CTRL_FLOW);
    }
}

/*
    if_blk -> IF LPAREN expr RPAREN body
*/
void Parser::parse_if_blk()
{
    expect(TokenType::IF);
    expect(TokenType::LPAREN);
    parse_expr();
    expect(TokenType::RPAREN);
    parse_body();    
}


/* 
    elsif_blks -> elsif_blk elseif_blks | elsif_blk
*/
void Parser::parse_elsif_blks()
{
    parse_elsif_blk();
    
    Token tok = lexer.peek();
    if (tok.type == TokenType::ELSIF)
    {
        parse_elsif_blks();
    }
    else if (tok.type == TokenType::INT ||    // any statement
                tok.type == TokenType::DEC ||
                tok.type == TokenType::STR || 
                tok.type == TokenType::BOOL || 
                tok.type == TokenType::VOID ||
                tok.type == TokenType::ID ||
                tok.type == TokenType::IF ||
                tok.type == TokenType::WHILE ||
                tok.type == TokenType::RBRACE ||
                tok.type == TokenType::RETURN ||
                tok.type == TokenType::ELSE
        )
    {
        return;
    }
    else 
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_CTRL_FLOW);        
    }
}

/*
    elsif_blk -> ELSIF LPAREN expr RPAREN body
*/
void Parser::parse_elsif_blk()
{
    expect(TokenType::ELSIF);
    expect(TokenType::LPAREN);
    parse_expr();
    expect(TokenType::RPAREN);
    parse_body();  
}

/*
    else_blk -> ELSE body
*/
void Parser::parse_else_blk()
{
    expect(TokenType::ELSE);
    parse_body();  
}

/*
    expr -> term | term OPERATOR expr | LPAREN expr RPAREN
*/
void Parser::parse_expr()
{
    Token tok_0 = lexer.peek();

    if(tok_0.type == TokenType::ID || 
        tok_0.type == TokenType::INT_NUM ||
        tok_0.type == TokenType::DEC_NUM ||
        tok_0.type == TokenType::STRING ||
        tok_0.type == TokenType::TRUE ||
        tok_0.type == TokenType::FALSE)
    {
        parse_term();
        
        Token tok_1 = lexer.peek();

        if (tok_1.type == TokenType::OPERATOR)
        {
            expect(TokenType::OPERATOR);
            parse_expr();
        } 
        else if (tok_1.type == TokenType::RPAREN || tok_1.type == TokenType::SEMICOLON || tok_1.type == TokenType::COMMA)
        {
            return;
        }
        else 
        {
            ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_1.lexeme, tok_1.line_number, INVALID_EXPR);        
        }
    }
    else if(tok_0.type == TokenType::LPAREN)
    {
        expect(TokenType::LPAREN);
        parse_expr();
        expect(TokenType::RPAREN);
    }
    else {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_0.lexeme, tok_0.line_number, INVALID_EXPR);        
    }
}

/* 
    term -> ID | INT_NUM | DEC_NUM | STRING | TRUE | FALSE | func_call
*/
void Parser::parse_term()
{
    Token tok_0 = lexer.peek();
    Token tok_1 = lexer.peek(1);

    if (tok_0.type == TokenType::ID) 
    {
        if(tok_1.type == TokenType::RPAREN || tok_1.type == TokenType::SEMICOLON || tok_1.type == TokenType::COMMA || tok_1.type == TokenType::OPERATOR)
        {
            expect(TokenType::ID);
        }
        else if(tok_1.type == TokenType::LPAREN)
        {
            parse_func_call();
        }
        else 
        {
            ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_1.lexeme, tok_1.line_number, INVALID_TERM);        
        }
    }
    else if (tok_0.type == TokenType::INT_NUM || tok_0.type == TokenType::DEC_NUM || tok_0.type == TokenType::STRING || tok_0.type == TokenType::TRUE || tok_0.type == TokenType::FALSE)
    {
        expect(tok_0.type);
    }
    else 
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_0.lexeme, tok_0.line_number, INVALID_TERM);        
    }
}

/*
    func_call -> ID LPAREN arg_list RPAREN 
    func_call -> ID LPAREN RPAREN 
*/
void Parser::parse_func_call()
{
    expect(TokenType::ID);
    expect(TokenType::LPAREN);

    Token tok = lexer.peek();
    if (tok.type == TokenType::ID ||
    tok.type == TokenType::LPAREN ||
    tok.type == TokenType::INT_NUM ||
    tok.type == TokenType::DEC_NUM ||
    tok.type == TokenType::STRING ||
    tok.type == TokenType::TRUE ||
    tok.type == TokenType::FALSE)
    {
        parse_arg_list();
    }
    expect(TokenType::RPAREN);
}

/*
    arg_list -> arg COMMA arg_list | arg
*/
void Parser::parse_arg_list() 
{
    parse_expr();

    Token tok = lexer.peek();
    if (tok.type == TokenType::COMMA) 
    {
        expect(TokenType::COMMA);
        parse_arg_list();
    }
    else if (tok.type == TokenType::RPAREN)
    {
        return;
    }
    else 
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_ARG_LIST);        
    }
}

/*
    type -> INT | DEC | STR | BOOL | VOID
*/
void Parser::parse_type()
{
    Token tok = lexer.peek();

    if(tok.type == TokenType::INT || tok.type == TokenType::DEC || tok.type == TokenType::BOOL || tok.type == TokenType::VOID || tok.type == TokenType::STR) 
    {
        expect(tok.type);
    }
    else 
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_TYPE);        
    }
}