#include "YAML/YAMLMan.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace Talon 
{
    YAMLMan::YAMLMan(const std::string& filepath)
    {
        std::ifstream file(filepath);
        if(!file.is_open())
        {
            std::cerr << "Error: Failed to open file " << filepath << std::endl;
            return;
        }
        
        std::string line;
        std::string key, value;

        while(std::getline(file, line))
        {
            if(line.empty() || line[0] == '#') // Skip over empty lines and comments
                continue;

            std::stringstream ss(line);
            if(std::getline(ss, key, ':') && std::getline(ss, value))
            {
                Trim(key);
                Trim(value);

                m_Dependencies.push_back({key, value});
            }
        }
    }

    void YAMLMan::Trim(std::string& str) const
    {
        size_t start = str.find_first_not_of('\t');
        size_t end = str.find_last_not_of('\t');
        if(start == std::string::npos || end == std::string::npos)
        {
            str.clear();
        }
        else 
        {
            str = str.substr(start, end - start + 1);
        }
    }
}
