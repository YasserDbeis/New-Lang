#include "../include/state_mgmt.h"
#include "../include/error_handler.h"
#include <iostream>

void StateMgmt::reset_state()
{
    std::queue<Value> emptyQueue;
    std::swap(arg_queue, emptyQueue);

    std::stack<StackFrame> emptyStack;
    std::swap(stack_trace, emptyStack);

    std::unordered_map<std::string, std::pair<Value, int>> empty_map;
    std::swap(global_vars, empty_map);
}

void StateMgmt::create_new_stack_frame(std::string func_id)
{
    // std::cout << "*** Creating New Stack Frame ***" << std::endl;
    StackFrame new_stack_frame;
    new_stack_frame.func_id = func_id;
    stack_trace.push(new_stack_frame);
    // std::cout << "After pushing, stack trace has a size of " << stack_trace.size() << std::endl;
}

void StateMgmt::delete_curr_stack_frame()
{
    // std::cout << "*** Deleting Current Stack Frame ***" << std::endl;
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
        /*
             If we're in a function - look at it's max global count. We can only access the global variable
             if it's stored global count is less than or equal to the max global count of the current function
        */
        if (stack_trace.empty() == false)
        {
            std::string curr_func_id = stack_trace.top().func_id;
            int curr_func_max_global = FuncDefTable::get_global_count(curr_func_id);

            int global_var_count = global_vars[id].second;
            if (global_var_count > curr_func_max_global)
            {
                ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Variable " + id + " has not been declared", -1, VAR_NOT_DEC);
            }
        }

        // Otherwise we are clear to return the variable!
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

Value StateMgmt::load_var_stack_trace(std::string name)
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
    std::cout << "************** STACK TRACE END **************\n\n"
              << std::endl;
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

// Returns name of the function on top of the stack trace. Error if stack trace is empty
std::string StateMgmt::get_curr_func_name()
{
    if (stack_trace.empty() == true)
    {
        ErrorHandler::error(ErrorPhase::EXECUTION, ErrorType::RUNTIME_ERROR, "Cannot load function name in empty stack trace", -1, EMPTY_STK_TRACE);
    }
    else
    {
        return stack_trace.top().func_id;
    }
}

bool StateMgmt::is_var_declared(std::string id)
{
    bool var_is_declared;
    if (stack_trace.empty())
    {
        var_is_declared = false;
    }
    else
    {
        var_is_declared = stack_trace.top().scope_tree.is_var_declared(id);
    }

    if (var_is_declared == false)
    {
        var_is_declared = global_vars.count(id) == 1;
    }

    return var_is_declared;
}
