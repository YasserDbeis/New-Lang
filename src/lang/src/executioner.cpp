#include "../include/executioner.h"

Executioner::Executioner() : compiler("")
{
}

Executioner::Executioner(std::string input) : compiler(input)
{
}

void Executioner::execute_program()
{
    inline const std::string MAIN = "main";

    FuncDefTable::function_exists(MAIN);

    execute_instructions(compiler.get_global_instructions());
    execute_instructions(FuncDefTable::get_function(MAIN));
}

void Executioner::execute_instructions(std::vector<InstNode *> instructions)
{
    if (instructions.empty() == true) // Debugging purposes
    {
        std::cout << "Empty instruction list" << std::endl;
        exit(EXIT_FAILURE);
    }

    int i = 0;

    int num_instructions = instructions.size();

    while (i < num_instructions)
    {
        InstNode *curr_inst = instructions[i];

        curr_inst->execute();

        i += curr_inst->get_offset();
    }
}