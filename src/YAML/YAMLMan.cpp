#include "YAML/YAMLMan.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

namespace Talon 
{
    YAMLMan::YAMLMan(const std::string& filename) : m_Filename(filename) {}

    void YAMLMan::ParseYAMLFile(const std::string& filename)
    {
        std::ifstream file(m_Filename);
        if (!file.is_open()) 
        {
            std::cerr << "Error: Could not open file " << m_Filename << std::endl;
            return;
        }

        std::string line;
        std::string currentSection;

        while (std::getline(file, line)) 
        {
            // Skip empty lines and comments
            if (line.empty() || line[0] == '#') 
            {
                continue;
            }

            // Trim leading and trailing whitespaces
            size_t start = line.find_first_not_of(" \t");
            if (start == std::string::npos) 
            {
                continue; // Empty line
            }
            size_t end = line.find_last_not_of(" \t");
            line = line.substr(start, end - start + 1);

            // Check for section headers
            if (line.back() == ':') 
            {
                currentSection = line.substr(0, line.size() - 1);
                continue;
            }

            // Parse based on the current section
            if (currentSection == "Config") 
            {
                ParseConfig(line);
            } 
            else if (currentSection == "Dependencies") 
            {
                ParseDependency(line);
            }
        }

        file.close();
    }
    
    void YAMLMan::ParseConfig(const std::string& line) 
    {
        // Split the line into key and value
        size_t pos = line.find(':');
        if (pos != std::string::npos) 
        {
            std::string key = line.substr(0, pos);
            std::string value = line.substr(pos + 1);
            // Trim leading and trailing whitespaces from key and value
            key.erase(0, key.find_first_not_of(" \t"));
            key.erase(key.find_last_not_of(" \t") + 1);
            value.erase(0, value.find_first_not_of(" \t"));
            value.erase(value.find_last_not_of(" \t") + 1);
            if (key == "DependencyDir") 
            {
                m_DependencyDir = value;
            }
        }
    }

    void YAMLMan::ParseDependency(const std::string& line) 
    {
        // Split the line into name and URL
        size_t pos = line.find(':');
        if (pos != std::string::npos) 
        {
            Dependency dep;
            dep.Name = line.substr(0, pos);
            dep.URL = line.substr(pos + 1);
            // Trim leading and trailing whitespaces from name and URL
            dep.Name.erase(0, dep.Name.find_first_not_of(" \t"));
            dep.Name.erase(dep.Name.find_last_not_of(" \t") + 1);
            dep.URL.erase(0, dep.URL.find_first_not_of(" \t"));
            dep.URL.erase(dep.URL.find_last_not_of(" \t") + 1);
            m_Dependencies.push_back(dep);
        }
    }
}
