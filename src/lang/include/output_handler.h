/*
    File: output_handler.h
    Authors: Briggs Richardson, Yasser Dbeis
    Date: 12-22-2021
    Description:
*/

#pragma once

#include <string>

class OutputHandler
{
public:
    static void reset_code_output();

    static void write_to_output(std::string);
    static std::string get_code_output();

private:
    inline static std::string code_output = "";
};
