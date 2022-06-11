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
    parse_program();
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

    // Global instructions are compiled. Append a func call instruction to main for the executioner
    std::vector<Expression> empty_vector;
    FuncCallNode *main_call = new FuncCallNode("main", empty_vector);
    global_instructions.push_back(main_call);
}

/*
    def_list -> def def_list | def
*/
void Parser::parse_def_list()
{
    parse_def();

    Token tok = lexer.peek();
    if (types.count(tok.type) == 1 || tok.type == TokenType::FUNC)
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
    std::vector<ExprNode *> empty_term_list;
    Expression empty_expr(empty_term_list);

    StoreNode *store_node = new StoreNode(type, id, empty_expr, global_count, false);

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
    ScopeNode *scope_node = new ScopeNode(true); // Create new scope
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
    std::vector<ExprNode *> empty_term_list;
    Expression empty_expr(empty_term_list);

    Type type = param.first;
    std::string name = param.second;

    StoreNode *store_node = new StoreNode(type, name, empty_expr, global_count, true);

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
        ScopeNode *scope_start_node = new ScopeNode(true);
        func_instructions.push_back(scope_start_node);
    }

    Token tok = lexer.peek();

    if (first_of_stmt.count(tok.type)) // var declaration or definition
    {
        parse_stmt_list();
    }

    expect(TokenType::RBRACE);
    ScopeNode *scope_end_node = new ScopeNode(false);
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

    if (tok_0.type == TokenType::LBRACE)
    {
        parse_body(false);
    }
    else if (tok_0.type == TokenType::WHILE)
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

    std::vector<ExprNode *> expr_list;
    parse_expr(expr_list);

    expect(TokenType::SEMICOLON);

    StoreNode *store_node = new StoreNode(type, id, expr_list, global_count, false);

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

    std::vector<ExprNode *> expr_list;
    parse_expr(expr_list);
    Expression expr(expr_list);

    expect(TokenType::RPAREN);

    int cjmp_index = func_instructions.size();
    CjmpNode *cjmp_node = new CjmpNode(expr_list);
    func_instructions.push_back(cjmp_node);

    parse_body();

    int jmp_index = func_instructions.size();
    JmpNode *jmp_node = new JmpNode();
    jmp_node->set_offset(cjmp_index - jmp_index);

    func_instructions[cjmp_index]->set_offset(jmp_index - cjmp_index + 1);
    func_instructions.push_back(jmp_node);
}

/*
    return_stmt -> RETURN expr SEMICOLON | RETURN SEMICOLON
*/
void Parser::parse_return_stmt()
{
    expect(TokenType::RETURN);

    Token tok = lexer.peek();

    ReturnNode *return_node = new ReturnNode();
    std::vector<ExprNode *> ret_expr;

    if (first_of_expr.count(tok.type))
    {
        parse_expr(ret_expr);
    }

    Expression expr(ret_expr);
    return_node->set_expr(expr);

    func_instructions.push_back(return_node);

    expect(TokenType::SEMICOLON);
}

/*
    if_stmt -> if_blk | if_blk else_blk | if_blk elseifs_blks | if_blk elseifs_blks else_blk
*/
void Parser::parse_if_stmt()
{
    std::vector<int> jmp_indices;

    parse_if_blk(jmp_indices);

    Token tok_0 = lexer.peek();

    if (tok_0.type == TokenType::ELSE)
    {
        parse_else_blk();
    }
    else if (tok_0.type == TokenType::ELSIF)
    {
        parse_elsif_blks(jmp_indices);

        Token tok_1 = lexer.peek();
        if (tok_1.type == TokenType::ELSE)
        {
            parse_else_blk();
        }

        // else if (first_of_stmt.count(tok_0.type) || tok_0.type == TokenType::RBRACE) // var declaration or definition
        // {
        //     return;
        // }
    }
    else if (first_of_stmt.count(tok_0.type) || tok_0.type == TokenType::RBRACE) // var declaration or definition
    {
        // return;
    }
    else
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok_0.lexeme, tok_0.line_number, INVALID_CTRL_FLOW);
    }

    int ix_of_next_stmt = func_instructions.size();
    for (int i = 0; i < jmp_indices.size(); i++)
    {
        int jmp_ix = jmp_indices[i];
        func_instructions[jmp_ix]->set_offset(ix_of_next_stmt - jmp_ix);
        // std::cout << "OFFSET TO JMP NODE SHOULD BE SET TO " << ix_of_next_stmt - jmp_ix << std::endl;
    }
}

/*
    if_blk -> IF LPAREN expr RPAREN body
*/
void Parser::parse_if_blk(std::vector<int> &jmp_indicies)
{
    expect(TokenType::IF);
    expect(TokenType::LPAREN);

    std::vector<ExprNode *> expr_list;
    parse_expr(expr_list);

    int if_cjmp_ix = func_instructions.size();

    Expression expr(expr_list);
    CjmpNode *cjmp_node = new CjmpNode(expr);

    func_instructions.push_back(cjmp_node);

    expect(TokenType::RPAREN);
    parse_body();

    int ix_of_jmp = func_instructions.size();
    jmp_indicies.push_back(ix_of_jmp);

    JmpNode *jmp = new JmpNode();
    func_instructions.push_back(jmp);

    int post_if_ix = func_instructions.size();
    func_instructions[if_cjmp_ix]->set_offset(post_if_ix - if_cjmp_ix);
}

/*
    elsif_blks -> elsif_blk elseif_blks | elsif_blk
*/
void Parser::parse_elsif_blks(std::vector<int> &jmp_indicies)
{
    parse_elsif_blk(jmp_indicies);

    Token tok = lexer.peek();
    if (tok.type == TokenType::ELSIF)
    {
        parse_elsif_blks(jmp_indicies);
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
void Parser::parse_elsif_blk(std::vector<int> &jmp_indicies)
{
    expect(TokenType::ELSIF);
    expect(TokenType::LPAREN);

    std::vector<ExprNode *> expr_list;
    parse_expr(expr_list);

    int elsif_cjmp_ix = func_instructions.size();

    Expression expr(expr_list);
    CjmpNode *cjmp_node = new CjmpNode(expr);

    func_instructions.push_back(cjmp_node);

    expect(TokenType::RPAREN);
    parse_body();

    int ix_of_jmp = func_instructions.size();
    jmp_indicies.push_back(ix_of_jmp);

    JmpNode *jmp = new JmpNode();
    func_instructions.push_back(jmp);

    int post_elsif_ix = func_instructions.size();
    func_instructions[elsif_cjmp_ix]->set_offset(post_elsif_ix - elsif_cjmp_ix);
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
    expr -> term
*/
void Parser::parse_expr(std::vector<ExprNode *> &expr_list)
{
    parse_term(expr_list);

    while (operators.count(lexer.peek().type) && lexer.peek().type != TokenType::OPERATOR_NOT && lexer.peek().type != TokenType::OPERATOR_XCL)
    {
        parse_operator(expr_list);
        parse_term(expr_list);
    }
}

/*
    term -> factor | factor OPERATOR factor
*/
void Parser::parse_term(std::vector<ExprNode *> &expr_list)
{
    parse_factor(expr_list);

    while (operators.count(lexer.peek().type) && lexer.peek().type != TokenType::OPERATOR_NOT && lexer.peek().type != TokenType::OPERATOR_XCL)
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
void Parser::parse_factor(std::vector<ExprNode *> &expr_list)
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
            Token factor = expect(tok_0.type);
            // LoadNode(type: ExprType, name: string, global_count: int, is_constant: bool)

            if (factor.type == TokenType::ID)
            {
                LoadNode *load_node = new LoadNode(ExprType::LOAD, token_to_type[factor.type], factor.lexeme, global_count, false);
                expr_list.push_back(load_node);
            }
            else
            {
                Value value;
                value.token = factor;
                value.type = token_to_type[factor.type];
                LoadNode *load_node = new LoadNode(ExprType::LOAD, value, global_count, true);
                expr_list.push_back(load_node);
            }
        }
    }
    else if (tok_0.type == TokenType::LPAREN)
    {
        expect(TokenType::LPAREN);
        ParenNode *lParenNode = new ParenNode(ExprType::PAREN, true);
        expr_list.push_back(lParenNode);

        parse_expr(expr_list);

        expect(TokenType::RPAREN);
        ParenNode *rParenNode = new ParenNode(ExprType::PAREN, false);
        expr_list.push_back(rParenNode);
    }
    else if (leading_operators.count(tok_0.type))
    {
        TokenType leading_op_type = parse_leading_op(expr_list).type;

        // Simulate terms in the expression to handle leading operator logic
        if (leading_op_type == TokenType::OPERATOR_MINUS)
        {
            // push (0 - [expr])
            ParenNode *paren_left = new ParenNode(ExprType::PAREN, true);
            expr_list.push_back(paren_left);

            Token zero_token;
            zero_token.type = TokenType::INT_NUM;
            zero_token.lexeme = "0";
            zero_token.line_number = tok_0.line_number;

            Value value;
            value.type = Type::Int;
            value.token = zero_token;

            LoadNode *zero_load = new LoadNode(ExprType::LOAD, value, global_count, true);
            expr_list.push_back(zero_load);

            OperatorNode *minus_node = new OperatorNode(ExprType::OPERATOR, OperatorType::MINUS);
            expr_list.push_back(minus_node);
        }
        else if (leading_op_type == TokenType::OPERATOR_NOT || leading_op_type == TokenType::OPERATOR_XCL)
        {
            // push (true xor [expr])
            ParenNode *paren_left = new ParenNode(ExprType::PAREN, true);
            expr_list.push_back(paren_left);

            Token true_token;
            true_token.type = TokenType::TRUE;
            true_token.lexeme = "true";
            true_token.line_number = tok_0.line_number;

            Value value;
            value.type = Type::Bool;
            value.token = true_token;
            LoadNode *true_load = new LoadNode(ExprType::LOAD, value, global_count, true);
            expr_list.push_back(true_load);

            OperatorNode *xor_node = new OperatorNode(ExprType::OPERATOR, OperatorType::XOR);
            expr_list.push_back(xor_node);
        }

        if (first_of_expr.count(tok_1.type) && tok_1.type != TokenType::STRING)
        {
            if (tok_1.type == TokenType::ID && tok_2.type == TokenType::LPAREN)
            {
                parse_func_expr_call(expr_list);
            }
            else if (tok_1.type == TokenType::LPAREN)
            {
                expect(TokenType::LPAREN);
                ParenNode *lParenNode = new ParenNode(ExprType::PAREN, true);
                expr_list.push_back(lParenNode);

                parse_expr(expr_list);

                expect(TokenType::RPAREN);
                ParenNode *rParenNode = new ParenNode(ExprType::PAREN, false);
                expr_list.push_back(rParenNode);
            }
            else
            {
                Token factor = expect(tok_1.type);

                if (factor.type == TokenType::ID)
                {
                    LoadNode *load_node = new LoadNode(ExprType::LOAD, token_to_type[factor.type], factor.lexeme, global_count, false);
                    expr_list.push_back(load_node);
                }
                else
                {
                    Value value;
                    value.token = factor;
                    value.type = token_to_type[factor.type];
                    LoadNode *load_node = new LoadNode(ExprType::LOAD, value, global_count, true);
                    expr_list.push_back(load_node);
                }
            }

            if (leading_op_type == TokenType::OPERATOR_MINUS || leading_op_type == TokenType::OPERATOR_NOT || leading_op_type == TokenType::OPERATOR_XCL)
            {
                ParenNode *paren_right = new ParenNode(ExprType::PAREN, false);
                expr_list.push_back(paren_right);
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

    FuncCallNode *func_node = new FuncCallNode(ExprType::FUNC_CALL, id, expression_list);

    func_instructions.push_back(func_node);
}

/*
    func_call -> ID LPAREN arg_list RPAREN
    func_call -> ID LPAREN RPAREN
*/
void Parser::parse_func_expr_call(std::vector<ExprNode *> &expr_list)
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

    FuncCallNode *func_node = new FuncCallNode(ExprType::FUNC_CALL, id, expression_list);

    expr_list.push_back(func_node);
}

/*
    arg_list -> expr COMMA arg_list | expr
*/
void Parser::parse_arg_list(std::vector<Expression> &expression_list)
{
    std::vector<ExprNode *> expr_list;
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
                OPERATOR_XOR |
                OPERATOR_XCL |
                OPERATOR_NEQ |
*/
void Parser::parse_operator(std::vector<ExprNode *> &expr_list)
{
    Token tok = lexer.peek();

    if (operators.count(tok.type) != 0 && tok.type != TokenType::OPERATOR_NOT && tok.type != TokenType::OPERATOR_XCL)
    {
        Token op_token = expect(tok.type);
        OperatorNode *op_node = new OperatorNode(ExprType::OPERATOR, operator_token_to_type[op_token.type]);
        expr_list.push_back(op_node);
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
Token Parser::parse_leading_op(std::vector<ExprNode *> &expr_list)
{
    Token tok = lexer.peek();

    if (leading_operators.count(tok.type) > 0)
    {
        expect(tok.type);

        return tok;
    }
    else
    {
        ErrorHandler::error(ErrorPhase::PARSING, ErrorType::SYNTAX_ERROR, "At token " + tok.lexeme, tok.line_number, INVALID_OPERATOR);
    }
}

std::vector<InstNode *> Parser::get_global_instructions()
{
    return global_instructions;
}

void Parser::print_instructions(std::vector<InstNode *> instructions)
{
    if (instructions.empty() == true)
    {
        std::cout << "Empty\n";
    }
    else
    {
        for (auto inst_node : instructions)
        {
            inst_node->inst_print();
        }
    }
}