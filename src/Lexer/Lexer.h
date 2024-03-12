#pragma once

#include <string>
#include <vector>

namespace Talon
{    
    enum TokenType
    {
        SectionSpecifier,
        Keyword,
        Subkeyword,
        Variable,
        List,
        Reference,
        Punctuation,
        Identifier,
        Number,
        String,
        Unknown,
        EndOfFile    
    };

    struct Token
    {
        TokenType Type;
        std::string Value;
        int Line;
        int Column;
    };

    class Lexer
    {
    public:
        Lexer(const std::string& input);

        std::vector<Token> Tokenize();
    private:
        const std::string m_Input;  // Input TLN string
        int m_Position;             // Current position in input
        int m_Line;                 // Current line number
        int m_Column;
    private:
        void ConsumeWhitespace();
        Token MatchToken(TokenType type);
    };


    
    namespace Utils
    {
        inline std::string TokenTypeToString(TokenType type)
        {
            switch(type)
            {
                case TokenType::SectionSpecifier:
                    return "Section";
                case TokenType::Keyword:
                    return "Keyword";
                case TokenType::Subkeyword:
                    return "Subkeyword";
                case TokenType::Variable:
                    return "Variable";
                case TokenType::List:
                    return "List";
                case TokenType::Reference:
                    return "Reference";
                case TokenType::Punctuation:
                    return "Punctuation";
                case TokenType::Identifier:
                    return "Identifier";
                case TokenType::Number:
                    return "Number";
                case TokenType::String:
                    return "String";
                case TokenType::Unknown:
                    return "UnknownTokenType";
                case TokenType::EndOfFile:
                    return "EndOfFile";
            }
        }
    } // namespace Utils
}
