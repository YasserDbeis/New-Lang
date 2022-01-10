/*
    File: parser.cpp
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-24-2021
    Description: Implements the functionality of the parser class. Uses the lexer's
    getToken and peek to perform recursive descent parsing.
*/

#include "../include/parser.h"
#include <iostream>

Parser::Parser() : lexer()
{
}

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
        // std::cout << "EXPECTED: " << lexer.get_token_name(expected_type) << std::endl;
        // std::cout << "RECEIVED: " << lexer.get_token_name(tok.type) << std::endl;
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
    if (types.count(tok.type) || tok.type == TokenType::FUNC)
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
    else if (types.count(tok_0.type))
    {
        if (tok_2.type == TokenType::SEMICOLON)
        {
            global_count++;
            parse_var_decl(true);
        }
        else if (tok_2.type == TokenType::EQUAL)
        {
            global_count++;
            parse_var_def(true);
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
void Parser::parse_var_decl(bool is_global)
{
    Type type = parse_type();
    std::string id = expect(TokenType::ID).lexeme;
    expect(TokenType::SEMICOLON);

    // EMPTY "terms" vector of Expression indicates empty expression
    std::vector<ExprNode> empty_term_list;
    Expression empty_expr(empty_term_list);

    StoreNode store_node(type, id, empty_expr, global_count, false);

    if (is_global == true)
    {
        global_instructions.push_back(store_node);
    }
    else
    {
        func_instructions.push_back(store_node);
    }
}

/*
    var_def -> type assign_stmt
*/
void Parser::parse_var_def(bool is_global)
{
    Type type = parse_type();
    parse_assign_stmt(type, is_global);
}

/*
    func_def -> FUNC ID LPAREN param_list RPAREN ret_type body
    func_def -> FUNC ID LPAREN RPAREN ret_type body
*/
void Parser::parse_func_def()
{
    ScopeNode scope_node(true); // Create new scope
    func_instructions.push_back(scope_node);

    expect(TokenType::FUNC);
    std::string id = expect(TokenType::ID).lexeme;
    expect(TokenType::LPAREN);

    Token tok = lexer.peek();
    std::vector<std::pair<Type, std::string>> params;
    if (types.count(tok.type))
    {
        parse_param_list(params);
    }
    else if (tok.type != TokenType::RPAREN)
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_PARAM);
    }
    expect(TokenType::RPAREN);
    Type return_type = parse_ret_type();
    parse_body(true);

    // Add to table, clear
    FuncDefTable::add_entry(id, global_count, params, return_type, func_instructions);
    func_instructions.clear();
}

/*
    ret_type -> RIGHTARROW type | epsilon
*/
Type Parser::parse_ret_type()
{
    Token tok = lexer.peek();

    if (tok.type == TokenType::RIGHTARROW)
    {
        expect(TokenType::RIGHTARROW);
        Type type = parse_type();

        return type;
    }
    else if (tok.type == TokenType::LBRACE) // follow ret_type is body which always has LBRACE start
    {
        return Type::Void;
    }
    else
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_RET_TYPE);
    }
}

/*
    param_list -> param COMMA param_list | param
*/
void Parser::parse_param_list(std::vector<std::pair<Type, std::string>> &param_list)
{
    std::pair<Type, std::string> param = parse_param();
    param_list.push_back(param);

    // EMPTY "terms" vector of Expression indicates empty expression
    std::vector<ExprNode> empty_term_list;
    Expression empty_expr(empty_term_list);

    Type type = param.first;
    std::string name = param.second;

    StoreNode store_node(type, name, empty_expr, global_count, true);

    func_instructions.push_back(store_node);

    Token tok = lexer.peek();
    if (tok.type == TokenType::COMMA)
    {
        expect(TokenType::COMMA);
        parse_param_list(param_list);
    }
    else if (tok.type == TokenType::RPAREN)
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
std::pair<Type, std::string> Parser::parse_param()
{
    Type type = parse_type();
    std::string name = expect(TokenType::ID).lexeme;

    return std::make_pair(type, name);
}

/*
    body -> LBRACE stmt_list RBRACE | LBRACE RBRACE
*/
void Parser::parse_body(bool scope_cooked)
{
    expect(TokenType::LBRACE);
    // Create scope if

    if (scope_cooked == false)
    {
        ScopeNode scope_start_node(true);
        func_instructions.push_back(scope_start_node);
    }

    Token tok = lexer.peek();

    if (first_of_stmt.count(tok.type)) // var declaration or definition
    {
        parse_stmt_list();
    }

    expect(TokenType::RBRACE);
    ScopeNode scope_end_node(false);
    func_instructions.push_back(scope_end_node);
}

/*
    stmt_list -> stmt stmt_list | stmt
*/
void Parser::parse_stmt_list()
{
    parse_stmt();

    Token tok = lexer.peek();

    if (first_of_stmt.count(tok.type))
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
    else if (tok_0.type == TokenType::ID) // assign_stmt or func_call
    {
        if (tok_1.type == TokenType::EQUAL)
        {
            parse_assign_stmt(Type::Invalid);
        }
        else if (tok_1.type == TokenType::LPAREN)
        {
            parse_func_stmt_call();
            expect(TokenType::SEMICOLON);
        }
        else
        {
            ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_1.lexeme, tok_1.line_number, INVALID_STMT);
        }
    }
    else if (types.count(tok_0.type))
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
void Parser::parse_assign_stmt(Type type, bool is_global)
{
    std::string id = expect(TokenType::ID).lexeme;

    expect(TokenType::EQUAL);

    std::vector<ExprNode> expr_list;
    parse_expr(expr_list);

    expect(TokenType::SEMICOLON);

    StoreNode store_node(type, id, expr_list, global_count, false);

    if (is_global)
    {
        global_instructions.push_back(store_node);
    }
    else
    {
        func_instructions.push_back(store_node);
    }
}

/*
    while_stmt -> WHILE LPAREN expr RPAREN body
*/
void Parser::parse_while_stmt()
{
    expect(TokenType::WHILE);
    expect(TokenType::LPAREN);

    std::vector<ExprNode> expr_list;
    parse_expr(expr_list);
    Expression expr(expr_list);

    expect(TokenType::RPAREN);

    CjmpNode cjmp_node;
    int cjmp_index = func_instructions.size();

    func_instructions.push_back(cjmp_node);

    parse_body();

    JmpNode jmp_node;
    jmp_node.target = cjmp_index;

    int jmp_index = func_instructions.size();

    // Trying to cast InstNode to Cjmp
    CjmpNode *cj = (CjmpNode *)&func_instructions[cjmp_index];
    cj->target = jmp_index;

    /*
  Parent parent;
  Child child;

  // upcast - implicit type cast allowed
  Parent *pParent = &child; 

  // downcast - explicit type case required 
  Child *pChild =  (Child *) &parent;

    */

    func_instructions.push_back(jmp_node);
}

/*
    return_stmt -> RETURN expr SEMICOLON | RETURN SEMICOLON
*/
void Parser::parse_return_stmt()
{
    expect(TokenType::RETURN);

    Token tok = lexer.peek();

    ReturnNode return_node;
    if (first_of_expr.count(tok.type))
    {
        std::vector<ExprNode> ret_expr;
        parse_expr(ret_expr);
        Expression expr(ret_expr);
        return_node.set_expr(expr);

        Expression expr(ret_expr);
        return_node.set_expr(expr);
    }
    else
    {
        return_node.set_no_expr();
    }

#if TESTING
    return_node.id = "RETURN NODE";
#endif

    func_instructions.push_back(return_node);

    expect(TokenType::SEMICOLON);
}

/*
    if_stmt -> if_blk | if_blk else_blk | if_blk elseifs_blks | if_blk elseifs_blks else_blk
*/
void Parser::parse_if_stmt()
{
    parse_if_blk();

    Token tok_0 = lexer.peek();

    if (tok_0.type == TokenType::ELSE)
    {
        parse_else_blk();
    }
    else if (tok_0.type == TokenType::ELSIF)
    {
        parse_elsif_blks();

        Token tok_1 = lexer.peek();
        if (tok_1.type == TokenType::ELSE)
        {
            parse_else_blk();
        }
        else if (first_of_stmt.count(tok_0.type) || tok_0.type == TokenType::RBRACE) // var declaration or definition
        {
            return;
        }
    }
    else if (first_of_stmt.count(tok_0.type) || tok_0.type == TokenType::RBRACE) // var declaration or definition
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
    else if (first_of_stmt.count(tok.type) || // any statement + end of body + else
             tok.type == TokenType::RBRACE ||
             tok.type == TokenType::ELSE)
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
    expr -> OPERATOR term | term
*/
void Parser::parse_expr(std::vector<ExprNode> &expr_list)
{
    Token tok = lexer.peek();

    /*
    if (leading_operators.count(tok.type))
    {
        parse_operator(expr_list);
    }
    else if (operators.count(tok.type))
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_OPERATOR);
    }
*/
    parse_term(expr_list);

    while (operators.count(lexer.peek().type))
    {
        parse_operator(expr_list);
        parse_term(expr_list);
    }
}

/*
    term -> factor | factor OPERATOR factor
*/
void Parser::parse_term(std::vector<ExprNode> &expr_list)
{
    parse_factor(expr_list);

    while (operators.count(lexer.peek().type))
    {
        parse_operator(expr_list);
        parse_factor(expr_list);
    }
}

/*
    factor -> ID | INT_NUM | DEC_NUM | STRING | func_call | TRUE | FALSE | LPAREN expr RPAREN
    factor -> leading_op ID | leading_op func_call | leading_op TRUE | leading_op FALSE | leading_op LPAREN expr RPAREN
    factor -> leading_op INT_NUM | leading_op DEC_NUM
*/
void Parser::parse_factor(std::vector<ExprNode> &expr_list)
{
    Token tok_0 = lexer.peek();
    Token tok_1 = lexer.peek(1);
    Token tok_2 = lexer.peek(2);

    std::string type_0 = lexer.get_token_name(tok_0.type);
    std::string type_1 = lexer.get_token_name(tok_1.type);

    if (first_of_expr.count(tok_0.type) && tok_0.type != TokenType::LPAREN)
    {
        if (tok_1.type == TokenType::LPAREN)
        {
            parse_func_expr_call(expr_list);
        }
        else
        {
            expect(tok_0.type);
        }
    }
    else if (tok_0.type == TokenType::LPAREN)
    {
        expect(TokenType::LPAREN);
        ParenNode lParenNode(ExprType::PAREN, true);
        expr_list.push_back(lParenNode);

        parse_expr(expr_list);

        expect(TokenType::RPAREN);
        ParenNode rParenNode(ExprType::PAREN, false);
        expr_list.push_back(rParenNode);
    }
    else if (leading_operators.count(tok_0.type))
    {
        parse_leading_op(expr_list);

        if (first_of_expr.count(tok_1.type) && tok_1.type != TokenType::STRING)
        {
            if (tok_1.type == TokenType::ID && tok_2.type == TokenType::LPAREN)
            {
                parse_func_expr_call(expr_list);
            }
            else if (tok_1.type == TokenType::LPAREN)
            {
                expect(TokenType::LPAREN);
                ParenNode lParenNode(ExprType::PAREN, true);
                expr_list.push_back(lParenNode);

                parse_expr(expr_list);

                expect(TokenType::RPAREN);
                ParenNode rParenNode(ExprType::PAREN, false);
                expr_list.push_back(rParenNode);
            }
            else
            {
                expect(tok_1.type);
            }
        }
        else
        {
            ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_1.lexeme, tok_1.line_number, INVALID_FACTOR);
        }
    }
    else
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_0.lexeme, tok_0.line_number, INVALID_FACTOR);
    }
}

/*
    func_call -> ID LPAREN arg_list RPAREN
    func_call -> ID LPAREN RPAREN
*/
void Parser::parse_func_stmt_call()
{
    std::string id = expect(TokenType::ID).lexeme;
    expect(TokenType::LPAREN);

    std::vector<Expression> expression_list;

    Token tok = lexer.peek();
    if (first_of_expr.count(tok.type))
    {
        parse_arg_list(expression_list);
    }

    expect(TokenType::RPAREN);

    FuncCallNode func_node(ExprType::FUNC_CALL, id, expression_list);

    func_instructions.push_back(func_node);
}

/*
    func_call -> ID LPAREN arg_list RPAREN
    func_call -> ID LPAREN RPAREN
*/
void Parser::parse_func_expr_call(std::vector<ExprNode> &expr_list)
{
    std::string id = expect(TokenType::ID).lexeme;
    expect(TokenType::LPAREN);

    std::vector<Expression> expression_list;

    Token tok = lexer.peek();
    if (first_of_expr.count(tok.type))
    {
        parse_arg_list(expression_list);
    }

    expect(TokenType::RPAREN);

    FuncCallNode func_node(ExprType::FUNC_CALL, id, expression_list);

    expr_list.push_back(func_node);
}

/*
    arg_list -> expr COMMA arg_list | expr
*/
void Parser::parse_arg_list(std::vector<Expression> &expression_list)
{
    std::vector<ExprNode> expr_list;
    parse_expr(expr_list);

    Expression expr(expr_list);
    expression_list.push_back(expr);

    Token tok = lexer.peek();
    if (tok.type == TokenType::COMMA)
    {
        expect(TokenType::COMMA);
        parse_arg_list(expression_list);
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
Type Parser::parse_type()
{
    Token tok = lexer.peek();

    if (types.count(tok.type))
    {
        TokenType tt = expect(tok.type).type;
        return token_to_type[tt];
    }
    else
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_TYPE);
    }
}

/*
    operator -> OPERATOR_PLUS |
                OPERATOR_MINUS |
                OPERATOR_MULT |
                OPERATOR_DIV |
                OPERATOR_GT |
                OPERATOR_LT |
                OPERATOR_GEQ |
                OPERATOR_LEQ |
                OPERATOR_IS |
                OPERATOR_AND |
                OPERATOR_OR |
                OPERATOR_NOT |
                OPERATOR_XCL |
                OPERATOR_NEQ |
*/
void Parser::parse_operator(std::vector<ExprNode> &expr_list)
{
    Token tok = lexer.peek();

    if (operators.count(tok.type))
    {
        expect(tok.type);
    }
    else
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_OPERATOR);
    }
}

/*
    operator -> OPERATOR_PLUS |
                OPERATOR_MINUS |
                OPERATOR_NOT |
                OPERATOR_XCL
*/
void Parser::parse_leading_op(std::vector<ExprNode> &expr_list)
{
    Token tok = lexer.peek();

    if (leading_operators.count(tok.type))
    {
        expect(tok.type);
    }
    else
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_OPERATOR);
    }
}

#if TESTING
void Parser::print_func_instructions()
{
    if (func_instructions.empty())
    {
        std::cout << "Empty!" << std::endl;
    }
    for (auto node : func_instructions)
    {
        std::cout << "NODE ID: " << node.id << std::endl;
    }
}
#endif