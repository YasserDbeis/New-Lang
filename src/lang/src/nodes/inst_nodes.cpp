#include "../../include/nodes/inst_nodes.h"
#include "../../include/state_mgmt.h"

/* --------------------------------------------
JmpNode implementation
--------------------------------------------- */

JmpNode::JmpNode()
{
    inst_type = InstType::JMP;
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
    inst_type = InstType::CJMP;
}

/*
    1. Evaluate the expression
    1.5. Throw error if expression doesn't evaluate to a boolean
    2. Set offset to 1 if true
*/
void CjmpNode::execute()
{
    expr.evaluate();

    if (expr.value.type != Type::Bool)
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_EXCEPTION, "At expression " + expr.value.token.lexeme, expr.value.token.line_number, INVALID_EVAL);
    }
}

int CjmpNode::get_offset()
{
    if (expr.value.type == Type::Bool)
    {
        if (expr.value.token.type == TokenType::TRUE)
        {
            return 1;
        }
        else
        {
            int target = get_target();
            return target;
        }
    }
}

void CjmpNode::inst_print(int num_tabs)
{
    for (int i = 0; i < num_tabs; i++)
    {
        std::cout << "\t";
    }

    std::cout << "[Cjmp] // "
              << "Offset : " << this->get_target() << std::endl;
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
    this->inst_type = InstType::STORE;
}

void StoreNode::assert_valid_type(Value val, Type expected_type)
{
    if (val.type != expected_type)
    {
        std::cout << "I'm in store node!" << std::endl;
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_EXCEPTION, "At expression " + expr.value.token.lexeme, expr.value.token.line_number, INVALID_EVAL);
    }
}

void StoreNode::store_to_curr_context(Value val)
{
    if (StateMgmt::stack_trace.empty()) // GLOBAL - store in global_vars
    {
        StateMgmt::store_global_var(name, val, global_count);
    }
    else // IN FUNCTION - stack trace
    {
        if (type == Type::Invalid) // Assignment statement
        {
            // Add var if the variable hasn't been declared yet.
            if (StateMgmt::is_var_declared(name) == true)
            {
                StateMgmt::stack_trace.top().scope_tree.update_var(name, val);
            }
        }
        else // Definition statement
        {
            StateMgmt::stack_trace.top().scope_tree.add_var(name, val);
        }
    }
}

void StoreNode::execute()
{
    if (is_param == true)
    {
        if (StateMgmt::arg_queue.empty()) // Debugging purposes
        {
            ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "The function called does not supply parameters", -1, ErrorCode::EMPTY_ARGS);
        }

        // Get the paramter value from the arg queue
        Value param_value = StateMgmt::arg_queue.front();
        StateMgmt::arg_queue.pop();

        // Insert it into the current scope tree
        assert_valid_type(param_value, type);
        StateMgmt::store_var_stack_trace(name, param_value);
    }
    else
    {
        if (expr.term_list.empty()) // Variable declaration - do not evaluate the expression
        {
            Value dummy_value; // Send in a dummy value instead
            dummy_value.type = type;
            store_to_curr_context(dummy_value);
        }
        else // Variable assignment - evaluate the expression
        {
            expr.evaluate();

            if (type != Type::Invalid) // Only validate the type if we know it at runtime!
            {
                assert_valid_type(expr.value, type);
            }

            store_to_curr_context(expr.value);
        }
    }

    // Printing for testing purposes
    //StateMgmt::print_stack_trace();
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
    inst_type = InstType::RETURN;
}

void ReturnNode::execute()
{
    Value return_value;
    if (expr.term_list.empty() == false) // Return node contains an expression to evaluate
    {
        expr.evaluate();
        return_value = expr.value;
    }
    else // Return node does not contain an expression. Save a void typed value instead.
    {
        return_value.type = Type::Void;
    }

    // Ensure the return type matches the expected return type of our function
    std::string curr_func_id = StateMgmt::get_curr_func_name();
    Type expected_func_return_type = FuncDefTable::get_return_type(curr_func_id);

    if (expected_func_return_type != return_value.type)
    {
        std::unordered_map<Type, std::string> type_to_str =
            {
                {Type::Void, "void"},
                {Type::Int, "int"},
                {Type::Dec, "dec"},
                {Type::String, "str"},
                {Type::Bool, "bool"},
                {Type::Invalid, "invalid"}};

        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR,
                            "Returned " + type_to_str[return_value.type] + ", but expected " + type_to_str[expected_func_return_type],
                            -1, INVALID_RETURN_VALUE);
    }

    StateMgmt::store_return_val_stack_trace(return_value);
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
    this->inst_type = InstType::SCOPE;
}

void ScopeNode::execute()
{

    if (StateMgmt::stack_trace.empty() == false)
    {
        if (is_new_scope == true)
        {
            StateMgmt::stack_trace.top().scope_tree.push();
        }
        else
        {
            StateMgmt::stack_trace.top().scope_tree.pop();
        }
    }
    else
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_EXCEPTION, "Cannot push new scope when stack trace is empty", -1, EMPTY_STK_TRACE);
    }
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
