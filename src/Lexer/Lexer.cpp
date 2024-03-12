#include "Lexer/Lexer.h"
#include <iostream>

namespace Talon 
{
    Lexer::Lexer(const std::string& input) 
        : m_Input(input), m_Line(1), m_Position(0), m_Column(1)
    {}

    std::vector<Token> Lexer::Tokenize()
    {
        std::vector<Token> tokens;

        while(m_Position < m_Input.length())
        {
            ConsumeWhitespace();

            // Match different token types
            if(m_Input[m_Position] == '[')
            {
                tokens.push_back(MatchToken(TokenType::SectionSpecifier));
            }
            else if(m_Input[m_Position] == '-' && m_Input[m_Position + 1] == ' ')
            {
                tokens.push_back(MatchToken(TokenType::Keyword));
            }
            else if(m_Input[m_Position] == '\t' && m_Input[m_Position + 1] == '\t' && m_Input[m_Position + 2] == '-' && m_Input[m_Position + 3] == ' ')
            {
                tokens.push_back(MatchToken(TokenType::Subkeyword));
            }
            else if(std::isalpha(m_Input[m_Position]))
            {
                tokens.push_back(MatchToken(TokenType::Variable));
            }
            else if(m_Input[m_Position] == '{')
            {
                tokens.push_back(MatchToken(TokenType::List));
            }
            else if(m_Input[m_Position] == '"')
            {
                tokens.push_back(MatchToken(TokenType::String));
            }
            else
            {
                std::cerr << "Error: Unrecognized token at line " << m_Line << ", column " << m_Column << std::endl;
                m_Position++;
            }
        }

        return tokens;
    }

    void Lexer::ConsumeWhitespace()
    {
        while(m_Position < m_Input.length() && std::isspace(m_Input[m_Position]))
        {
            if(m_Input[m_Position] == '\n')
            {
                m_Line++;
                m_Column = 1;
            }
            else
            {
                m_Column++;
            }
            m_Position++;
        }
    }

    Token Lexer::MatchToken(TokenType type)
    {
        size_t start = m_Position;
        std::string value;

        switch(type)
        {
            case TokenType::SectionSpecifier:
                while(m_Position < m_Input.length() && m_Input[m_Position] != ']')
                {
                    m_Position++;
                    m_Column++;
                }
                if(m_Position == m_Input.length())
                {
                    // Unmatched '['
                    std::cerr << "Error: Unmatched '[' at line " << m_Line << ", column " << m_Column << std::endl;
                }
                else
                {
                    m_Position++; // Consume ']'
                    m_Column++;
                }
                value = m_Input.substr(start, m_Position - start);
                break;
            case TokenType::Keyword:
                m_Position += 2; // Consume '- '
                m_Column += 2;
                while(m_Position < m_Input.length() && !std::isspace(m_Input[m_Position]))
                {
                    m_Position++;
                    m_Column++;
                }
                value = m_Input.substr(start + 2, m_Position - start - 2);
                break;
            case TokenType::Subkeyword:
                m_Position += 3; // Consume '\t- '
                m_Column += 3;
                while(m_Position < m_Input.length() && !std::isspace(m_Input[m_Position]))
                {
                    m_Position++;
                    m_Column++;
                }
                value = m_Input.substr(start + 3, m_Position - start - 3);
                break;
            case TokenType::Variable:
                while(m_Position < m_Input.length() && std::isalnum(m_Input[m_Position]))
                {
                    m_Position++;
                    m_Column++;
                }
                value = m_Input.substr(start, m_Position - start);
                break;
            case TokenType::List:
                m_Position++; // Consume '{'
                m_Column++;
                while(m_Position < m_Input.length() && m_Input[m_Position] != '}')
                {
                    m_Position++;
                    m_Column++;
                }
                if(m_Position == m_Input.length())
                {
                    // Unmatched '{'
                    std::cerr << "Error: Unmatched '{' at line " << m_Line << ", column " << m_Column << std::endl;
                }
                else
                {
                    m_Position++; // Consume '}'
                    m_Column++;
                }
                value = m_Input.substr(start, m_Position - start);
                break;
            case TokenType::String:
                m_Position++; // Consume '"'
                m_Column++;
                while(m_Position < m_Input.length() && m_Input[m_Position] != '"')
                {
                    m_Position++;
                    m_Column++;
                }
                if(m_Position == m_Input.length())
                {
                    // Unmatched '"'
                    std::cerr << "Error: Unmatched '\"' at line " << m_Line << ", column " << m_Column << std::endl;
                }
                else
                {
                    m_Position++; // Consume '"'
                    m_Column++;
                }
                value = m_Input.substr(start + 1, m_Position - start - 2);
                break;
        }

        return {type, value, static_cast<int>(m_Line), static_cast<int>(m_Column)};
    }
}
