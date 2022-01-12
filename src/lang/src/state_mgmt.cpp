#include "../include/state_mgmt.h"
#include "../include/error_handler.h"

void StateMgmt::create_new_stack_frame()
{
    StackFrame new_stack_frame;
    stack_trace.push(new_stack_frame);
}

void StateMgmt::delete_curr_stack_frame()
{
    stack_trace.pop();
}

Value StateMgmt::get_func_return_value()
{
    if (stack_trace.empty())
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Stack trace is empty", -1, MISSING_FUNC_RETURN);
    }
    return stack_trace.top().return_value;
}

Value StateMgmt::load_global_var(std::string id)
{
    if (global_vars.count(id) == 1)
    {
        return global_vars[id].first;
    }
    else
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Variable " + id + " has not been declared", -1, VAR_NOT_DEC);
    }
}

void StateMgmt::store_global_var(std::string id, Value value, int global_count)
{
    if (global_vars.count(id) != 0)
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Variable " + id + " has already been declared", -1, VAR_ALREADY_DEC);
    }
    else
    {
        global_vars[id] = std::make_pair(value, global_count);
    }
}

void StateMgmt::store_global_var(std::string id, Value value)
{
    if (global_vars.count(id) == 0)
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Variable " + id + " has not been declared", -1, VAR_NOT_DEC);
    }
    else
    {
        global_vars[id].first = value;
    }
}

void StateMgmt::store_var_stack_trace(std::string name, Value value)
{
    if (stack_trace.empty() == false)
    {
        stack_trace.top().scope_tree.add_var(name, value);
    }
    else
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Cannot store variable " + name + " in empty stack trace", -1, EMPTY_STK_TRACE);
    }
}