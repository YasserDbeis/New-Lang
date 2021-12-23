#pragma once

typedef struct Error
{

    ErrorType type;
    ErrorPhase phase;
    Token token;
    std::string message;

    std::string type_to_str(ErrorType type)
    {
        switch (type)
        {
        case ErrorType::SYNTAX_ERROR:
        {
            return "SYNTAX ERROR";
        }
        case ErrorType::RUNTIME_ERROR:
        {
            return "RUNTIME ERROR";
        }
        case ErrorType::RUNTIME_EXCEPTION:
        {
            return "RUNTIME EXCEPTION";
        }
        default:
        {
            printf("Internal error");
            exit(EXIT_FAILURE);
        }
        }
    }

    std::string phase_to_str(ErrorPhase phase)
    {
        switch (phase)
        {
        case ErrorPhase::LEXICAL_ANALYSIS:
        {
            return "Lexical Analysis";
        }
        case ErrorPhase::PARSING:
        {
            return "Parsing";
        }
        case ErrorPhase::COMPILATION:
        {
            return "Compilation";
        }
        default:
        {
            printf("Internal error");
            exit(EXIT_FAILURE);
        }
        }
    }

    void print()
    {
        std::string type_str = type_to_str(type);
        std::string phase_str = phase_to_str(phase);
        std::string phase_info = "Error occurred in " + phase_str;

        bool token_exists = token == NULL;

        printf("%s\n%s\n", type_str, phase_info);

        if (token_exists)
        {
            printf("%d: %s\n", token.line_number, token.lexeme);
        }
    }

} Error;