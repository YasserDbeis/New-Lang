#include "../../include/nodes/inst_nodes.h"
#include "../include/state_mgmt.h"

/* --------------------------------------------
JmpNode implementation
--------------------------------------------- */

JmpNode::JmpNode()
{
}

void JmpNode::inst_print(int num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
    {
        std::cout << "\t";
    }

    std::cout << "[Jmp] // "
              << "Offset : " << this->get_offset() << std::endl;
}

/* --------------------------------------------
CjmpNode implementation
--------------------------------------------- */

CjmpNode::CjmpNode()
{
}

CjmpNode::CjmpNode(Expression expr)
{
    this->expr = expr;
}

/*
    1. Evaluate the expression
    1.5. Throw error if expression doesn't evaluate to a boolean
    2. Set offset to 1 if true
*/
void CjmpNode::execute()
{
    expr.evaluate();

    if (expr.value.type == Type::Bool)
    {
        if (expr.value.token.type == TokenType::TRUE)
        {
            set_offset(1);
        }
    }
    else
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_EXCEPTION, "At expression " + expr.value.token.lexeme, expr.value.token.line_number, INVALID_EVAL);
    }
}

void CjmpNode::inst_print(int num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
    {
        std::cout << "\t";
    }

    std::cout << "[Cjmp] // "
              << "Offset : " << this->get_offset() << std::endl;
    expr.print_expr(num_tabs + 1);
    std::cout << std::endl;
}

/* --------------------------------------------
StoreNode implementation
--------------------------------------------- */

StoreNode::StoreNode()
{
}

StoreNode::StoreNode(Type type, std::string name, Expression expr, int global_count, bool is_param)
{
    this->type = type;
    this->name = name;
    this->expr = expr;
    this->global_count = global_count;
    this->is_param = is_param;
}

void StoreNode::execute()
{
    if (is_param)
    {
        if (StateMgmt::arg_queue.empty())
        {
            std::cout << "BUG! Arg queue is empty" << std::endl;
        }
        Value param_value = StateMgmt::arg_queue.front();
        StateMgmt::arg_queue.pop();

        if (param_value.)
            StateMgmt::store_var_stack_trace(name, param_value);
    }
    else
    {
        expr.evaluate();

        if (StateMgmt::stack_trace.empty()) // GLOBAL - store in global_vars
        {
            if (expr.value.type == type)
            {
                StateMgmt::store_global_var(name, expr.value, global_count);
            }
            else
            {
                ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_EXCEPTION, "At expression " + expr.value.token.lexeme, expr.value.token.line_number, INVALID_EVAL);
            }
        }
        else // FUNCTION - store in stack trace
        {
            if (expr.value.type == Type::Invalid)
            {
                StateMgmt::stack_trace.top().scope_tree.update_var(name, expr.value);
            }
            else
            {
                if (expr.value.type == type)
                {
                    StateMgmt::stack_trace.top().scope_tree.add_var(name, expr.value);
                }
                else
                {
                    ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_EXCEPTION, "At expression " + expr.value.token.lexeme, expr.value.token.line_number, INVALID_EVAL);
                }
            }
        }
    }
}

void StoreNode::inst_print(int num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
    {
        std::cout << "\t";
    }

    std::unordered_map<Type, std::string> type_to_str = {
        {Type::Bool, "Bool"},
        {Type::Dec, "Dec"},
        {Type::Int, "Int"},
        {Type::Invalid, "Invalid"},
        {Type::String, "String"},
        {Type::Void, "Void"}};

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

    std::cout << "[Store] // "
              << "Offset: " << this->get_offset()
              << ", Name: " << this->name
              << ", Gcount: " << this->global_count
              << ", Is Param: " << this->is_param
              << ", Type: " << type_to_str[this->type] << std::endl;
    expr.print_expr(num_tabs + 1);

    std::cout << std::endl;
}

/* --------------------------------------------
ReturnNode implementation
--------------------------------------------- */

ReturnNode::ReturnNode()
{
}

void ReturnNode::set_expr(Expression given_expr)
{
    expr = given_expr;
}

void ReturnNode::execute()
{
    //expr.evaluate();
    /*
        stack_trace.peek().scope_tree.return_value = expr.value;

        // Note, we can put a node value at return_value if we reach nullptr when executing function (not global ll)
    */
}

void ReturnNode::inst_print(int num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
    {
        std::cout << "\t";
    }

    std::cout << "[Return]  "
              << "Offset: " << this->get_offset() << std::endl;
    expr.print_expr(num_tabs + 1);
    std::cout << std::endl;
}

/* --------------------------------------------
ScopeNode implementation
--------------------------------------------- */

ScopeNode::ScopeNode()
{
}

ScopeNode::ScopeNode(bool is_new_scope)
{
    this->is_new_scope = is_new_scope;
}

void ScopeNode::execute()
{
}

void ScopeNode::inst_print(int num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
    {
        std::cout << "\t";
    }
    std::cout << "[Scope] "
              << "Offset: " << this->get_offset() << ", Is New Scope: " << is_new_scope << std::endl;
}
