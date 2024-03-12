#include "Lexer/Lexer.h"

#include <fstream>
#include <iostream>
#include <iterator>
#include <iomanip>


int main(int argc, char* argv[])
{
	if (argc < 2)
	{
		std::cerr << "Error: Wrong argument. Usage: Talon <filename>.tln";
		return 1;
    }

	std::ifstream inputFile(argv[1]);

	std::string input((std::istreambuf_iterator<char>(inputFile)), std::istreambuf_iterator<char>());

	auto tokens = Talon::Lexer(input).Tokenize();
    std::cout << std::left
        << std::setw(15) << "Token Type"
        << std::setw(30) << "Token Value"
        << std::setw(5)  << "\tLine"
        << std::setw(5)  << "\tColumn"
        << std::endl;

    for (const auto& token : tokens) {
        std::cout << std::setw(15) << Talon::Utils::TokenTypeToString(token.Type)
            << std::setw(30) << token.Value
            << std::setw(5)  << '\t' << token.Line
            << std::setw(5)  << '\t' << token.Column
            << std::endl;
    }
	return 0;
}