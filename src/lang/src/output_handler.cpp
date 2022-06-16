#include "../include/output_handler.h"

std::string OutputHandler::get_code_output()
{
    return code_output;
}

void OutputHandler::write_to_output(std::string result)
{
    code_output += result;
}

void OutputHandler::reset_code_output()
{
    code_output = "";
}