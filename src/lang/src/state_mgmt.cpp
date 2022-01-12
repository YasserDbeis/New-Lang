#include "../include/state_mgmt.h"
#include "../include/error_handler.h"
#include <iostream>

void StateMgmt::create_new_stack_frame(std::string func_id)
{
    std::cout << "*** Creating New Stack Frame ***" << std::endl;
    StackFrame new_stack_frame;
    new_stack_frame.func_id = func_id;
    stack_trace.push(new_stack_frame);
    std::cout << "After pushing, stack trace has a size of " << stack_trace.size() << std::endl;
}

void StateMgmt::delete_curr_stack_frame()
{
    std::cout << "*** Deleting Current Stack Frame ***" << std::endl;
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

void StateMgmt::store_return_val_stack_trace(Value value)
{
    if (stack_trace.empty() == false)
    {
        stack_trace.top().return_value = value;
    }
    else
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Cannot store return variable in empty stack trace", -1, EMPTY_STK_TRACE);
    }
}

Value StateMgmt::store_var_stack_trace(std::string name)
{
    if (stack_trace.empty() == false)
    {
        return stack_trace.top().scope_tree.get_var(name);
    }
    else
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Cannot store return variable in empty stack trace", -1, EMPTY_STK_TRACE);
    }
}

Value StateMgmt::load_return_val_stack_trace()
{
    if (stack_trace.empty() == false)
    {
        return stack_trace.top().return_value;
    }
    else
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Cannot load return variable in empty stack trace", -1, EMPTY_STK_TRACE);
    }
}

void StateMgmt::print_stack_trace()
{
    std::cout << "************** STACK TRACE START **************" << std::endl;
    if (stack_trace.empty())
    {
        std::cout << "Stack trace: empty" << std::endl;
        return;
    }

    print_stack_recursively();
    std::cout << "************** STACK TRACE END **************\n\n" << std::endl;
}

void StateMgmt::print_stack_recursively()
{
    if (stack_trace.empty() == true)
    {
        return;
    }

    // Extract top stack frame from stack 
    StackFrame top_stack_frame = stack_trace.top();
    stack_trace.pop();

    // Print contents
    std::cout << "---------- Stack Frame ------------" << std::endl;
    std::cout << "Function: " << top_stack_frame.func_id << std::endl;
    top_stack_frame.scope_tree.print_scope_tree();

    // Continue down the stack
    print_stack_recursively();

    // Return contents to stack in original order
    stack_trace.push(top_stack_frame);
}